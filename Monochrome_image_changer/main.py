"""Center-crop an image to an aspect ratio and threshold its HSV value."""

from __future__ import annotations

from pathlib import Path
import re
import tkinter as tk
from tkinter import filedialog, messagebox

from PIL import Image, ImageOps, ImageTk


def crop_to_aspect(
    image: Image.Image, horizontal: int, vertical: int
) -> Image.Image:
    """Return a centered crop matching the requested horizontal:vertical ratio."""
    if horizontal <= 0 or vertical <= 0:
        raise ValueError("Ratio components must be positive integers.")

    width, height = image.size
    requested_ratio_numerator = horizontal
    requested_ratio_denominator = vertical

    if width * requested_ratio_denominator > height * requested_ratio_numerator:
        crop_width = max(
            1,
            (2 * height * requested_ratio_numerator + requested_ratio_denominator)
            // (2 * requested_ratio_denominator),
        )
        left = (width - crop_width) // 2
        bounds = (left, 0, left + crop_width, height)
    else:
        crop_height = max(
            1,
            (2 * width * requested_ratio_denominator + requested_ratio_numerator)
            // (2 * requested_ratio_numerator),
        )
        top = (height - crop_height) // 2
        bounds = (0, top, width, top + crop_height)

    return image.crop(bounds)


def resize_down_to_fit(
    image: Image.Image, target_width: int, target_height: int
) -> Image.Image:
    """Downscale an image to fit within a box without changing its aspect ratio."""
    if target_width <= 0 or target_height <= 0:
        raise ValueError("Target dimensions must be positive integers.")
    if image.width <= target_width and image.height <= target_height:
        return image.copy()
    return ImageOps.contain(
        image,
        (target_width, target_height),
        method=Image.Resampling.LANCZOS,
    )


def make_monochrome(
    image: Image.Image, threshold: int = 128, invert: bool = False
) -> Image.Image:
    """Map HSV values below the threshold to black and the rest to white."""
    if not 0 <= threshold <= 255:
        raise ValueError("Threshold must be between 0 and 255.")

    has_alpha = "A" in image.getbands()
    alpha = image.getchannel("A") if has_alpha else None
    value = image.convert("RGB").convert("HSV").getchannel("V")
    binary = value.point(lambda pixel: 255 if pixel >= threshold else 0)
    if invert:
        binary = ImageOps.invert(binary)
    result = Image.merge("RGB", (binary, binary, binary))

    if alpha is not None:
        result.putalpha(alpha)
    return result


def preview_size(
    image_size: tuple[int, int], viewport_size: tuple[int, int]
) -> tuple[int, int] | None:
    """Scale an image to fit a preview viewport while preserving its aspect."""
    image_width, image_height = image_size
    viewport_width, viewport_height = viewport_size
    if min(image_width, image_height, viewport_width, viewport_height) <= 0:
        return None

    scale = min(viewport_width / image_width, viewport_height / image_height)
    return max(1, round(image_width * scale)), max(1, round(image_height * scale))


def prompt_for_positive_integer(prompt: str) -> int:
    while True:
        value = input(prompt).strip()
        try:
            number = int(value)
        except ValueError:
            print("Enter a whole number greater than zero.")
            continue
        if number > 0:
            return number
        print("Enter a whole number greater than zero.")


def choose_image() -> Path | None:
    root = tk.Tk()
    root.withdraw()
    try:
        selected = filedialog.askopenfilename(
            title="Select an image",
            filetypes=[
                ("Image files", "*.png *.jpg *.jpeg *.bmp *.gif *.tif *.tiff *.webp"),
                ("All files", "*.*"),
            ],
        )
    finally:
        root.destroy()
    return Path(selected) if selected else None


def output_path_for(
    image_path: Path,
    horizontal: int,
    vertical: int,
    target_width: int,
    target_height: int,
) -> Path:
    return image_path.with_name(
        f"{image_path.stem}_monochrome_{horizontal}x{vertical}_"
        f"{target_width}x{target_height}{image_path.suffix}"
    )


def lvgl_asset_paths_for(
    image_path: Path,
    horizontal: int,
    vertical: int,
    target_width: int,
    target_height: int,
) -> tuple[Path, Path, str]:
    """Return C source/header paths and a safe LVGL symbol name."""
    identifier = re.sub(r"\W", "_", image_path.stem, flags=re.ASCII).strip("_")
    if not identifier:
        identifier = "image"
    symbol = (
        f"img_{identifier}_{horizontal}x{vertical}_"
        f"{target_width}x{target_height}"
    )
    base = image_path.with_name(f"{symbol}_lvgl")
    return base.with_suffix(".c"), base.with_suffix(".h"), symbol


def export_lvgl_i1(image: Image.Image, c_path: Path, symbol: str) -> Path:
    """Write an LVGL I1 C image and its matching descriptor header."""
    monochrome = image.convert("L")
    width, height = monochrome.size
    stride = (width + 7) // 8
    c_path = c_path.with_suffix(".c")
    header_path = c_path.with_suffix(".h")
    attribute = f"LV_ATTRIBUTE_IMAGE_{symbol.upper()}"

    pixel_bytes = bytearray()
    for y in range(height):
        for byte_x in range(stride):
            packed = 0
            for bit in range(8):
                x = byte_x * 8 + bit
                if x < width and monochrome.getpixel((x, y)) >= 128:
                    packed |= 1 << (7 - bit)
            pixel_bytes.append(packed)

    lines = [
        '#ifdef __has_include',
        '    #if __has_include("lvgl.h")',
        '        #ifndef LV_LVGL_H_INCLUDE_SIMPLE',
        '            #define LV_LVGL_H_INCLUDE_SIMPLE',
        '        #endif',
        '    #endif',
        '#endif',
        '',
        '#if defined(LV_LVGL_H_INCLUDE_SIMPLE)',
        '    #include "lvgl.h"',
        '#else',
        '    #include "lvgl/lvgl.h"',
        '#endif',
        '',
        '',
        '#ifndef LV_ATTRIBUTE_MEM_ALIGN',
        '#define LV_ATTRIBUTE_MEM_ALIGN',
        '#endif',
        '',
        f'#ifndef {attribute}',
        f'#define {attribute}',
        '#endif',
        '',
        f'const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST {attribute} '
        f'uint8_t {symbol}_map[] = {{',
        '  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,',
    ]

    for offset in range(0, len(pixel_bytes), 16):
        chunk = pixel_bytes[offset : offset + 16]
        lines.append('  ' + ', '.join(f'0x{value:02x}' for value in chunk) + ',')
    lines.extend(
        [
            '};',
            '',
            f'const lv_image_dsc_t {symbol} = {{',
            '  .header.cf = LV_COLOR_FORMAT_I1,',
            '  .header.magic = LV_IMAGE_HEADER_MAGIC,',
            f'  .header.stride = {stride},',
            f'  .header.w = {width},',
            f'  .header.h = {height},',
            f'  .data_size = sizeof({symbol}_map),',
            f'  .data = {symbol}_map,',
            '};',
            '',
        ]
    )
    c_path.write_text("\n".join(lines), encoding="utf-8", newline="\n")
    header_path.write_text(
        f'#pragma once\n\n#include "Global.h"\n\nLV_IMAGE_DECLARE({symbol});\n',
        encoding="utf-8",
        newline="\n",
    )
    return c_path


def process_image(
    image_path: Path,
    horizontal: int,
    vertical: int,
    target_width: int,
    target_height: int,
    threshold: int = 128,
    invert: bool = False,
    export_lvgl: bool = False,
) -> Path:
    """Load, transform, then save an image or export an LVGL asset."""
    with Image.open(image_path) as source:
        oriented = ImageOps.exif_transpose(source)
        cropped = crop_to_aspect(oriented, horizontal, vertical)
        resized = resize_down_to_fit(cropped, target_width, target_height)
        result = make_monochrome(resized, threshold, invert)
        image_format = source.format

    if export_lvgl:
        c_path, _header_path, symbol = lvgl_asset_paths_for(
            image_path, horizontal, vertical, target_width, target_height
        )
        return export_lvgl_i1(result, c_path, symbol)

    output_path = output_path_for(
        image_path, horizontal, vertical, target_width, target_height
    )
    if image_format is None:
        result.save(output_path)
    else:
        result.save(output_path, format=image_format)
    return output_path


def edit_threshold(
    image_path: Path,
    horizontal: int,
    vertical: int,
    target_width: int,
    target_height: int,
) -> Path | None:
    """Show a live threshold preview and save when the user confirms."""
    with Image.open(image_path) as source:
        cropped = crop_to_aspect(ImageOps.exif_transpose(source), horizontal, vertical)
        resized = resize_down_to_fit(
            cropped, target_width, target_height
        )

    root = tk.Tk()
    root.title("Black-and-white threshold")
    root.geometry("900x700")
    root.minsize(360, 320)

    preview_canvas = tk.Canvas(root, background="#303030", highlightthickness=0)
    preview_canvas.pack(fill=tk.BOTH, expand=True, padx=12, pady=(12, 4))

    threshold = tk.IntVar(value=128)
    invert = tk.BooleanVar(value=False)
    export_lvgl = tk.BooleanVar(value=False)
    saved_path: Path | None = None
    preview_image: Image.Image | None = None

    def render_preview(_event: tk.Event | None = None) -> None:
        if preview_image is None:
            return
        canvas_width = preview_canvas.winfo_width()
        canvas_height = preview_canvas.winfo_height()
        dimensions = preview_size(
            preview_image.size, (canvas_width, canvas_height)
        )
        if dimensions is None:
            return

        display_image = preview_image.resize(dimensions, Image.Resampling.NEAREST)
        photo = ImageTk.PhotoImage(display_image)
        preview_canvas.delete("preview")
        preview_canvas.create_image(
            canvas_width // 2,
            canvas_height // 2,
            image=photo,
            anchor=tk.CENTER,
            tags="preview",
        )
        preview_canvas.image = photo

    def update_preview(_value: str | None = None) -> None:
        nonlocal preview_image
        preview_image = make_monochrome(resized, threshold.get(), invert.get())
        render_preview()

    def update_save_button() -> None:
        save_button.configure(
            text="Export LVGL I1" if export_lvgl.get() else "Save image"
        )

    tk.Scale(
        root,
        label="Threshold (HSV value)",
        from_=0,
        to=255,
        orient=tk.HORIZONTAL,
        variable=threshold,
        command=update_preview,
        length=420,
    ).pack(fill=tk.X, padx=12)

    tk.Checkbutton(
        root,
        text="Invert the monochrome image (black/white)",
        variable=invert,
        command=update_preview,
    ).pack(anchor=tk.W, padx=12)
    tk.Checkbutton(
        root,
        text="Download as LVGL I1",
        variable=export_lvgl,
        command=update_save_button,
    ).pack(anchor=tk.W, padx=12)

    def save_image() -> None:
        nonlocal saved_path
        try:
            saved_path = process_image(
                image_path,
                horizontal,
                vertical,
                target_width,
                target_height,
                threshold.get(),
                invert.get(),
                export_lvgl.get(),
            )
        except (OSError, ValueError) as error:
            messagebox.showerror("Could not save image", str(error), parent=root)
            return
        message = f"Saved output:\n{saved_path}"
        if export_lvgl.get():
            message += f"\n{saved_path.with_suffix('.h')}"
        messagebox.showinfo(
            "Image saved", message, parent=root
        )
        root.destroy()

    save_button = tk.Button(root, text="Save image", command=save_image)
    save_button.pack(pady=(4, 12))
    root.protocol("WM_DELETE_WINDOW", root.destroy)
    preview_canvas.bind("<Configure>", render_preview)
    update_preview()
    root.mainloop()
    return saved_path


def main() -> None:
    print("Monochrome Image Changer")
    try:
        image_path = choose_image()
    except tk.TclError as error:
        raise RuntimeError(f"Could not open the image picker: {error}") from error

    if image_path is None:
        print("No image selected. Exiting.")
        return

    horizontal = prompt_for_positive_integer("Horizontal ratio component: ")
    vertical = prompt_for_positive_integer("Vertical ratio component: ")
    target_width = prompt_for_positive_integer("Maximum output width (pixels): ")
    target_height = prompt_for_positive_integer("Maximum output height (pixels): ")

    try:
        output_path = edit_threshold(
            image_path, horizontal, vertical, target_width, target_height
        )
    except tk.TclError as error:
        raise RuntimeError(f"Could not open the threshold editor: {error}") from error
    except (OSError, ValueError) as error:
        raise RuntimeError(f"Could not process '{image_path}': {error}") from error

    if output_path is None:
        print("No image saved.")
    else:
        print(f"Saved output: {output_path}")


if __name__ == "__main__":
    main()
