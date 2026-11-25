from pathlib import Path
from tempfile import TemporaryDirectory
import unittest

from PIL import Image

from main import (
    crop_to_aspect,
    export_lvgl_argb8888,
    lvgl_asset_paths_for,
    make_monochrome,
    process_image,
    resize_down_to_fit,
)


class ImageProcessingTests(unittest.TestCase):
    def test_crop_to_aspect_center_crops_wide_image(self) -> None:
        image = Image.new("RGB", (8, 4))

        cropped = crop_to_aspect(image, 1, 1)

        self.assertEqual(cropped.size, (4, 4))

    def test_crop_to_aspect_center_crops_tall_image(self) -> None:
        image = Image.new("RGB", (4, 8))

        cropped = crop_to_aspect(image, 1, 1)

        self.assertEqual(cropped.size, (4, 4))

    def test_monochrome_maps_hsv_value_to_only_black_or_white(self) -> None:
        image = Image.new("RGB", (3, 1))
        image.putdata([(127, 80, 20), (128, 0, 0), (255, 255, 255)])

        result = make_monochrome(image)

        self.assertEqual(
            [result.getpixel((x, 0)) for x in range(3)],
            [(0, 0, 0), (255, 255, 255), (255, 255, 255)],
        )

    def test_monochrome_invert_swaps_black_and_white(self) -> None:
        image = Image.new("RGB", (2, 1))
        image.putdata([(0, 0, 0), (255, 255, 255)])

        result = make_monochrome(image, invert=True)

        self.assertEqual(
            [result.getpixel((x, 0)) for x in range(2)],
            [(255, 255, 255), (0, 0, 0)],
        )

    def test_monochrome_threshold_is_adjustable_and_preserves_alpha(self) -> None:
        image = Image.new("RGBA", (1, 1), (120, 30, 100, 64))

        result = make_monochrome(image, threshold=121)

        red, green, blue, alpha = result.getpixel((0, 0))
        self.assertEqual((red, green, blue), (0, 0, 0))
        self.assertEqual(alpha, 64)

    def test_monochrome_rejects_out_of_range_threshold(self) -> None:
        with self.assertRaises(ValueError):
            make_monochrome(Image.new("RGB", (1, 1)), threshold=256)

    def test_crop_rejects_non_positive_ratio(self) -> None:
        with self.assertRaises(ValueError):
            crop_to_aspect(Image.new("RGB", (4, 4)), 0, 1)

    def test_resize_down_to_fit_uses_target_bounds_and_preserves_aspect(self) -> None:
        image = Image.new("RGB", (400, 200))

        resized = resize_down_to_fit(image, 128, 64)

        self.assertEqual(resized.size, (128, 64))

    def test_resize_down_to_fit_preserves_aspect_when_one_bound_is_unused(self) -> None:
        image = Image.new("RGB", (400, 100))

        resized = resize_down_to_fit(image, 128, 64)

        self.assertEqual(resized.size, (128, 32))

    def test_resize_down_to_fit_does_not_upscale_small_images(self) -> None:
        image = Image.new("RGB", (32, 16))

        resized = resize_down_to_fit(image, 128, 64)

        self.assertEqual(resized.size, (32, 16))

    def test_resize_down_to_fit_rejects_non_positive_dimensions(self) -> None:
        with self.assertRaises(ValueError):
            resize_down_to_fit(Image.new("RGB", (4, 4)), 0, 4)

    def test_process_image_saves_cropped_monochrome_copy(self) -> None:
        with TemporaryDirectory() as directory:
            image_path = Path(directory) / "source.png"
            Image.new("RGB", (8, 4), (255, 0, 0)).save(image_path)

            output_path = process_image(image_path, 1, 1, 4, 4)

            self.assertEqual(output_path.name, "source_monochrome_1x1_4x4.png")
            with Image.open(output_path) as result:
                self.assertEqual(result.size, (4, 4))
                self.assertEqual(result.getpixel((0, 0)), (255, 255, 255))

    def test_lvgl_export_writes_argb8888_source_and_header(self) -> None:
        image = Image.new("RGB", (2, 1))
        image.putdata([(0, 0, 0), (255, 255, 255)])

        with TemporaryDirectory() as directory:
            c_path, header_path, symbol = lvgl_asset_paths_for(
                Path(directory) / "Nazuna.png", 16, 9, 128, 64
            )
            saved_path = export_lvgl_argb8888(image, c_path, symbol)
            source = saved_path.read_text(encoding="utf-8")
            header = header_path.read_text(encoding="utf-8")

            self.assertEqual(saved_path.suffix, ".c")
            self.assertIn("LV_COLOR_FORMAT_ARGB8888", source)
            self.assertIn(f"const lv_image_dsc_t {symbol}", source)
            self.assertIn(".header.w = 2", source)
            self.assertIn(".header.h = 1", source)
            self.assertIn(f"LV_IMAGE_DECLARE({symbol});", header)
            self.assertIn(
                "0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff",
                source,
            )

    def test_process_image_can_export_lvgl_asset(self) -> None:
        with TemporaryDirectory() as directory:
            image_path = Path(directory) / "source.png"
            Image.new("RGB", (4, 2), (255, 255, 255)).save(image_path)

            output_path = process_image(
                image_path, 2, 1, 4, 2, invert=True, export_lvgl=True
            )

            self.assertEqual(output_path.suffix, ".c")
            self.assertTrue(output_path.with_suffix(".h").exists())
            source = output_path.read_text(encoding="utf-8")
            self.assertIn("LV_COLOR_FORMAT_ARGB8888", source)
            self.assertIn("0x00, 0x00, 0x00, 0xff", source)


if __name__ == "__main__":
    unittest.main()
