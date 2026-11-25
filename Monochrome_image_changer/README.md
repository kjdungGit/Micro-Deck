# Monochrome Image Changer

A small console-driven image utility. It opens a file picker, asks for the
desired aspect ratio as horizontal and vertical integer components (for example,
`16` and `9`), and a maximum output width and height in pixels. It center-crops
as needed to match the ratio, then downsizes to fit inside the requested
dimensions while preserving aspect ratio. Smaller images are not upscaled. A
GUI preview provides a threshold slider before saving a copy next to the source
image.

The output uses only pure black and white. The slider thresholds the HSV value
channel: values below the selected threshold become black, and values at or
above it become white. The default threshold is `128`. Transparency is retained
where the source format supports it. The threshold window also has an invert
checkbox and an option to export the result as an LVGL I1 C asset with a
black-and-white palette and packed 1-bit pixels. LVGL export writes a `.c` image
descriptor and a matching `.h` declaration beside the selected image. With
LVGL export unchecked, the program saves a regular image using the selected
source format. The preview resizes to fit the editor window as it is resized,
preserving the image aspect ratio.

## Requirements

- Python 3.10 or newer
- Pillow
- A desktop session for the image picker and threshold preview

## Run

From this directory:

```powershell
python -m pip install -r requirements.txt
python main.py
```

The output name includes both the ratio and maximum dimensions, for example
`photo_monochrome_16x9_128x64.jpg`.

## Test

```powershell
python -m unittest discover -s tests
```
