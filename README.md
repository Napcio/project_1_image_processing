# Extra Credit Documentation

I did the 4 suggestions of Additional Manipulation Algorithm and the Image Mosaic.

## Additional Manipulation Algorithm
- `invert` - Inverts the color of the image.
  **Algorithm**: For each pixel, all channels are set to 255 - x, where x is the channel.
- `grayscale` - Apply a grayscale filter to the image.
  **Algorithm**: For each pixel, average the color of every channel and set all channels to that average.
- `sepia` - Apply a sepia tone filter to the image.
  **Algorithm**: For each pixel, set the channels according to the following algorithm:
```C++
// Stole the following formulas from here:  
// https://medium.com/@rupertontheloose/functional-shaders-a-colorful-intro-part5-tinting-with-sepia-tone-cd6c2b49806  
red = clamp((red * 0.393) + (green * 0.769) + (blue * 0.189) + .5);  
green = clamp((red * 0.349) + (green * 0.686) + (blue * 0.168) + .5);  
blue = clamp((red * 0.272) + (green * 0.534) + (blue * 0.131) + .5);
```

**NOTE**: *The following algorithms involve convolving, an operation which, for each pixel, takes a matrix (referred to as a kernel) and multiplies the surrounding pixels (assuming that the center value of the kernel is the pixel currently being operated on) by the corresponding value in the kernel. These new values are then summed and the current pixel is set to that value. It requires a copy of the original pixel to be held in memory so that previous edits do not pollute the needed values of subsequent edits.* 

- `sharpen <intensity>` - Highlights parts of the image with rapid changes in color intensity, with a strength proportional to the given `<intensity>` value (floating point)
  **Algorithm**: Copy the original image and convolve it with a Laplacian kernel. Due to being stored in a TgaContainer (unsigned channels), negative values will be lost. Invert the values of the kernel and repeat the first step once more to capture the negative values. Multiply both copies by the intensity factor. Add the first copy to the original and subtract the second copy.
```
Laplacian Kernel:
-1  -1  -1
-1   8  -1
-1  -1  -1
```
- `blur` - Applies a mild blur to the image
  **Algorithm**: Generate a kernel of Gaussian weights according to the formula
  (1 / (2\*pi\*s^2))  \* e^(-(x^2 + y^2) / 2\*s^2) 
  In this implementation, the kernel set to 5x5 using a standard deviation of 2. 
  Convolve the image with the generated kernel.
	- x, y = distance from center pixel
	- s = standard deviation (determines how blurry the image becomes)

*I didn't realize that the title said algorithm (singular tense) so I ended up implementing all 4 suggestions.*
### MakeFile Tests:
Call `make extra` to run, will populate `./output/` with resulting images
- Run `invert` on `car.tga`, output is `inverted_car.tga`
- Run `grayscale` on `car.tga`, output is `grayscale_car.tga`
- Run `sepia` on `car.tga`, output is `sepia_car.tga`
- Run `sharpen 1` on `car.tga`, output is `sharpened_car.tga`
- Run `blur` on `car.tga`, output is `blurred_car.tga`

Call `make collage` to test `mosaic`, runs the following command:
`./output/collage_test.tga ./input/car.tga ./input/circles.tga ./input/layer1.tga ./input/pattern2.tga mosaic 2 2`