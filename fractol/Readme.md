# ReadMe

## How To run the file

./fractol mandelbrot
./fractol julia
./fractol burningship

## Important

How to draw pixels into the image?
The pixel data is initialized to 0, meaning every pixel will be black without alpha.

The pixel data is a single array of width * height * 4 bytes. 
For a 500x500 image, we would need 1’000’000 bytes or about 0.953 MB. [500*500*4 = 1,000,000]

The way I like to iterate this array when pixel_bits == 32 is:
y is the Y coordinate in the image.
y == 0 is the first (top) pixel within the image.
y * line_bytes lets us move up/down in pixel coordinates.

x is the X coordinate in the image.
x == 0 is the first (left) pixel.
x lets us move left/right in pixel coordinates.

Remember that one pixel on screen requires 4 bytes in memory.
Remember that buffer is a char *.

When you increment the pointer by one by one, you’re moving forward one byte in memory, so the final offset should be multiplied by 4.
(y * line_bytes) + (x * 4) is the beginning of the data for that screen pixel.

Manual:
1. Check how many bits per pixel
2. Convert your color with mlx_get_color_value
3. Check whether little or big endian
4. write color value byte by byte into pixel array according to endian

### Notes

1. We can add in the parameters for the window size which will be the same as image size. 

### Reference

> https://github.com/GlThibault/Fractol/?source=post_page-----6664b6b045b5--------------------------------
