# How to use the software
We have 3 executable files (We only have students with macbooks. That is why we can only upload the mac executable):
- `./main` &rarr; The main programm to apply filters, projections, ... <br>
```
g++-12 src/main.cpp src/UserInterface.cpp src/Image.cpp src/Filter.cpp src/Volume.cpp src/Slice.cpp src/Util.cpp src/Projection.cpp -o main
```

- `./test` &rarr; Tests the functions of the main programm. <br>
```
g++-12 src/test.cpp src/Image.cpp src/Filter.cpp src/Volume.cpp src/Slice.cpp src/Testing.cpp src/Util.cpp src/Projection.cpp -o test
```

- `./time` &rarr; Times the functions of the main programm. <br>
```
g++-12 src/time.cpp src/Image.cpp src/Filter.cpp src/Volume.cpp src/Slice.cpp src/Util.cpp src/Projection.cpp -o time
```

<br>
<br>

## Main
When the users starts the programme, the user is asked for input data in the console. There are two possibilities. On the one hand, a path to an image can be specified. Then the data type is recognised as a 2D image. If a path to a folder is specified, it is assumed that this is a volume. The path should be inside the root directory so that the programm has access to the file/directory.
<br>

```
Please input the path to the input data.
- For 2D images specify a path to an image (for example 'Images/gracehopper.png').
- For 3D volumes specify a path to a folder (for example 'Scans/confuciusornis').

> 
```

### 2D Image
If a path to an image is specified, a selection of all possible filters is displayed. If the user wants to select a filter, the user must enter the number in front of the respective filter.
<br>

```
Please input the number of the 2D filter you want to apply.
[0] Apply selected filter

[1] greyscale
[2] brightness
[3] median-blur
[4] gaussian-blur
[5] sobel
[6] prewitt

Selected filters: []
> 1
```

After pressing enter the selcted Filter will be displayed under "Selected filters".
<br>

```
Please input the number of the 2D filter you want to apply.
[0] Apply selected filter

[1] greyscale
[2] brightness
[3] median-blur
[4] gaussian-blur
[5] sobel
[6] prewitt

Selected filters: [greyscale]
>
```

If the user wants to add another Filter, that will be applied after the first filter, he can enter another number. He can specify as many filters as he wants.
<br>

```
Please input the number of the 2D filter you want to apply.
[0] Apply selected filter

[1] greyscale
[2] brightness
[3] median-blur
[4] gaussian-blur
[5] sobel
[6] prewitt

Selected filters: [greyscale -> prewitt]
>
```

After the user has selected all filters that he wants to apply on the original image he has to press "0". Now the first filter will be applied to the originial image. Then the second filter is applied to the output of the previous filter and so on. If the filter requires additional input from the user like the kernel size, another query will appear on the screen that will ask the user for more input. The final Image will be stored in the output directory. The programm will create a new directory inside this directory if it does not already exists. The name of this directory is the name of the original image. Inside of this folder, the final image will be stored. The name of this image represents all the filters that were applied to the image.


### Volume
If a volume is specified, the user is first asked whether all images in the specified folder are to be used.
<br>

```
Do you want to use all the images in that folder?

[1] Yes
[2] No

>
```

If the user selects "No", only a thin slab of the whole volume is used. To save time, the remaining part is not read in at all into memory. To define the range, the z coordinate must be specified at which the volume should start to be read in. For example, a z-coordinate of 10 corresponds to the tenth image.
<br>

```
Please input the first z-value:
10
```

Then the second coordinate must be entered up to which the volume is to be read in.
<br>

```
Please input the second z-value:
100
```

After the volume has been read in, various options are suggested which can be applied to the volume.
<br>

```
Please input a number between 1 and 3!:

[1] Slice
[2] Projection
[3] 3D-Filter & Projection

>
```

#### Slicing
If "Slicing" is selected, the user can slice the volume in a different plane. There are two choices. By typing the number in front of the options, they can be selected.
<br>

```
Please input the number of the plane:

[1] x-z plane
[2] y-z plane

> 
```

After that the user must specify the constant value. If the user selected the "x-z plane" option, he needs to input a y value. If the user selected the "y-z plane" he has to input a x value.
<br>

```
Please input the constant y-value:
> 
```

The output will be saved like with 2D-Images. However the filename of the resulting image is different. It will be for example: "x-z plane_20.png".

#### Projection
When the user selects "Projection", there are 4 different projections to choose from. By entering the number in front of the respective projection and pressing enter, it can be selected.
<br>

```
Please input the Projection you want to apply:

[1] Maximum intensity projection (MIP)
[2] Minimum intensity projection (MinIP)
[3] Mean - Average intensity projection (AIP)
[4] Median - Average intensity projection (AIP)

> 
```

The output will be saved similar to the 2D-Images or Slicing but with a different name. For example: "Maximum intensity projection (MIP).png"

#### 3D-Filter & Projection
When the user selects "3D-Filter & Projection", the system first asks for the 3D-filter which should be applied. The filter can be selected by typing in the number in front of the corresponding option.
<br>

```
Please input the 3D Filter you want to apply:

[1] 3D Gaussian
[2] 3D Median

> 
```

Then the user will be asked for the projection which should be applied (see previous point). After selecting the projection, the user will also be asked for the kernel size for the selected 3d filter. The output will be saved similar to the 2D-Images, Slicing or Projection but with a different name.

<br>
<br>

## Test

By executing `./test` you get an overview of all tests whether they were successful or not. They are also sorted thematically. The tests do not take much time to run because only small amounts of data are used.

<br>
<br>

## Timing

By executing `./time`, you get the average time that the programme/function needs when repeated several times. Since the execution can take a little longer, we have listed the output here, which was obtained on one of our laptops.

=============================

### Timings of 2D-Filters:

- Timings for image 'Images/gracehopper.png':<br>
Avg. timing of greyscale: **5ms**<br>
Avg. timing of brightness: **5ms**<br>
Avg. timing of medianblur (5x5): **1142ms**<br>
Avg. timing of medianblur (7x7): **2583ms**<br>
Avg. timing of gaussianblur (5x5): **268ms**<br>
Avg. timing of gaussianblur (7x7): **588ms**<br>
Avg. timing of sobel: **15ms**<br>
Avg. timing of prewitt: **104ms**<br>
<br>

- Timings for image 'Images/tienshan.png':<br>
Avg. timing of greyscale: **55ms**<br>
Avg. timing of brightness: **60ms**<br>
Avg. timing of medianblur (5x5): **12030ms**<br>
Avg. timing of medianblur (7x7): **27280ms**<br>
Avg. timing of gaussianblur (5x5): **2737ms**<br>
Avg. timing of gaussianblur (7x7): **6001ms**<br>
Avg. timing of sobel: **162ms**<br>
Avg. timing of prewitt: **1051ms**<br>

=============================

### Timings of Slicing:

<br>

- Timings for volume 'Scans/confuciusornis with num images: 20:<br>
Avg. timing of XZ Slicing: **0ms**<br>
Avg. timing of YZ Slicing: **0ms**<br>
<br>

- Timings for volume 'Scans/fracture with num images: 20:<br>
Avg. timing of XZ Slicing: **0ms**<br>
Avg. timing of YZ Slicing: **0ms**<br>
<br>

- Timings for volume 'Scans/confuciusornis with num images: 200:<br>
Avg. timing of XZ Slicing: **1ms**<br>
Avg. timing of YZ Slicing: **15ms**<br>
<br>

- Timings for volume 'Scans/fracture with num images: 200:<br>
Avg. timing of XZ Slicing: **1ms**<br>
Avg. timing of YZ Slicing: **2ms**<br>

=============================

### Timings of 3D-Projections:

- Timings for volume 'Scans/confuciusornis with num images: 20:<br>
Avg. timing of maximum intensity projection: **239ms**<br>
Avg. timing of minimum intensity projection: **224ms**<br>
Avg. timing of mean intensity projection: **177ms**<br>
Avg. timing of median intensity projection: **2208ms**<br>
<br>

- Timings for volume 'Scans/fracture with num images: 20:<br>
Avg. timing of maximum intensity projection: **44ms**<br>
Avg. timing of minimum intensity projection: **44ms**<br>
Avg. timing of mean intensity projection: **29ms**<br>
Avg. timing of median intensity projection: **392ms**<br>
<br>

- Timings for volume 'Scans/confuciusornis with num images: 200:<br>
Avg. timing of maximum intensity projection: **6839ms**<br>
Avg. timing of minimum intensity projection: **6666ms**<br>
Avg. timing of mean intensity projection: **6957ms**<br>
Avg. timing of median intensity projection: **26237ms**<br>
<br>

- Timings for volume 'Scans/fracture with num images: 200:<br>
Avg. timing of maximum intensity projection: **466ms**<br>
Avg. timing of minimum intensity projection: **485m**<br>
Avg. timing of mean intensity projection: **435ms**<br>
Avg. timing of median intensity projection: **3052ms**<br>
<br>

=============================

### Timings of 3D-Filters:

- Timings for volume 'Scans/confuciusornis with num images: 20:<br>
Avg. timing (projected) of the median 3d filter (5x5): **266s**<br>
Avg. timing (projected) of the gaussian 3d filter (5x5): **38s**<br>
<br>

- Timings for volume 'Scans/fracture with num images: 20:<br>
Avg. timing (projected) of the median 3d filter (5x5): **36s**<br>
Avg. timing (projected) of the gaussian 3d filter (5x5): **6s**<br>
<br>

- Timings for volume 'Scans/confuciusornis with num images: 200:<br>
Avg. timing (projected) of the median 3d filter (5x5): **2660s**<br>
Avg. timing (projected) of the gaussian 3d filter (5x5): **380s**<br>
<br>

- Timings for volume 'Scans/fracture with num images: 200:<br>
Avg. timing (projected) of the median 3d filter (5x5): **360s**<br>
Avg. timing (projected) of the gaussian 3d filter (5x5): **60s**<br>