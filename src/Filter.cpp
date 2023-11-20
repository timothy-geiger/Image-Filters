/*
Group name: Ziggurat
Members name      |Github Username
--------------------------------------
Dayou Chen        |acse-dc421
Ruijia Yu         |acse-ry122
Jinsong Dong      |edsml-jd622
Timothy Geiger    |acse-tfg22
Yue Peng          |edsml-yp22
Christopher Saad  |edsml-cs1622
*/

#include <cmath>
#include <memory>
#include <iostream>
#include <cstring>
#include "Filter.h"
#include <iostream>

void Filter::applyGreyscaleFilter(Image& image, int input)
{   
    // get the wight, height and channel of the images
    int width = image.widthGetter();
    int height = image.heightGetter();
    int channels = image.channelGetter();
    if (channels < 3)
        std::cout << "Grayscale does not support the current image, as the channel number is less than 3" << std::endl;
    else
    {
        // use varDataGetter() function to change the image data
        unsigned char* data = image.varDataGetter();
        // use two for loop to transfer the image data
        // thus change the colour to grey
        for(int c=0; c<((channels==4) ? 3 : channels); c++) {
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                // channel times columns than the gray scale image
                int index = (y * width + x) * channels;
                // use equation to change the RGB to grey colour
                int grey = static_cast<int>(0.299 * data[index] + 0.587 * data[index + 1] + 0.114 * data[index + 2]);
                data[index] = static_cast<unsigned char>(grey);
                data[index + 1] = static_cast<unsigned char>(grey);
                data[index + 2] = static_cast<unsigned char>(grey);
                }
            }
    }
}
}


// Colour correction filter, brightness
void Filter::Brightness(Image& image, int value){
    int width = image.widthGetter();
    int height = image.heightGetter();
    int channels = image.channelGetter();
    unsigned char* data = image.varDataGetter();

    for (int y = 0; y < height; ++y){
        for (int x = 0; x < width; ++x){
            // data images have 3 or 4 channels
            for(int c = 0; c < channels; ++c){
                // the image pixels and then add values
                int temp = (y * width + x) * channels + c;
                int current = data[temp] + value;

                // make values between 0, 255
                current = std::min(std::max(current, 0), 255);

                // give values to all pixels
                data[temp] = static_cast<unsigned char>(current);
            }
        }
    }
}

void Filter::quick_sort(std::vector<int>& input_vec, int low, int high){
    // this function is the quick sort algorithm to sort a vector
    // low is the left side of the vector, and high is the right side of the vector
    int temp;
    if(low>=high){
        return; //the index of low should be smaller than high
    }

    int i = low, j = high, base = input_vec[low]; // set a base to compare the values between the two sides
    while(i < j){
        //sweep the vector from the right to the left, if we meet the element that is smaller than base, assign its value to the input_vec[i]
        while(input_vec[j]>=base && i<j){j--;}
        input_vec[i] = input_vec[j];
        //sweep the vector from the left to the right, if we meet the element that is bigger than base, assign its value to the input_vec[j]
        while(input_vec[i]<=base && i<j){i++;}
        input_vec[j] = input_vec[i];
    }
    //set the assign base value to the current element, then we implemented the value swap
    input_vec[i] = base;
    //incursion of the function
    quick_sort(input_vec, low, j-1);
    quick_sort(input_vec, j+1, high);
}

int Filter::cal_median(std::vector<int>& input_vec, int input_num){
    // this function is to calculate the median for a kernel
    // input_num is the useful element number of the kernel, as some element in the kernel that exceeds the image boundary is useless.
    int median;
    // sort the input vector with the quick sort algorithm, useless element value is bigger than 300, and will be moved to the tail of the vector
    quick_sort(input_vec, 0, input_vec.size()-1);
    if(input_num%2==0){
        //if the useful element number is even number, the average of the middle two values will be the median
        median = (input_vec[input_num/2] + input_vec[input_num/2-1])/2;
    }else{
        //if the useful element number is odd number, the middle one value will be the median
        median = input_vec[input_num/2];
    }
    return median;
}


void Filter::applyMedianBlurFilter(Image& image, int input)
{   
    //specify kernel size, eg:3*3, 5*5, 7*7, etc..
    int kernel_size = input;
    if(kernel_size<0){
        //If the kernel size is negative, quit the function.
        std::cout << "The kernel_size should be bigger than 0!" << std::endl;
        return;
    }
    int kernel_half = input/2; //this is the half length of the kernel size, which is the number we iterate.
    int median;
    std::vector<int> median_kernel(kernel_size*kernel_size, 300); //initialize the vector of kernel for calculating median with 300(bigger than 255, which is useless in picture).
    int use_ele_num = kernel_size * kernel_size; // useful element number in kernel, if the pixel of the kernel is out of the boundary of image, minus 1

    //Get width, height and number of channels of the image
    int width = image.widthGetter();
    int height = image.heightGetter();
    if(kernel_size > std::min(width, height)){
        //If the kernel_size is too big, quit the function.
        std::cout << "The kernel_size is too big!" << std::endl;
        return;
    }
    int channels = image.channelGetter();

    //Get the data and make a copy for calculating median of the kernel, because original data will be modified during iterating.
    unsigned char* data = image.varDataGetter();
    unsigned char* data_copy = new unsigned char[width*height*channels];
    std::copy(data, data + width * height * channels, data_copy);
    
    for(int c=0; c<channels; c++){//iterating over the channel
        if(channels==4 && c==3){ //ignore the transparency channel
            continue;
        }else{
            for(int y=0; y<height; y++){//iterating over the height, only considering the pixels in the mid (kernel do not exceed picture boundaries)
                for(int x=0; x<width; x++){//iterating over the width, only considering the pixels in the mid (kernel do not exceed picture boundaries)
                    median = 0;
                    use_ele_num = kernel_size * kernel_size;
                    int current_index = y*width*channels + x*channels + c; //this is the flat index of the current pixel
                    //std::cout << "x: " << x << "  y: " << y << std::endl;
                    for(int h=-kernel_half; h<kernel_half+1; h++){
                        //iterating over the kernel, h is for the kernel height and k is for the kernel width
                        for(int k=-kernel_half; k<kernel_half+1; k++){
                            if(y+h<0 || x+k<0 || y+h>=height || x+k>=width){
                                //if the kernel pixel exceeds the edge of the picture, ignore this pixel
                                use_ele_num -= 1;
                                median_kernel[(h+kernel_half)*kernel_size + (k+kernel_half)] = 300;

                            }
                            else{
                                //if the kernel pixel is within the picture, add its value to median for calculating.
                                median_kernel[(h+kernel_half)*kernel_size + (k+kernel_half)] = static_cast<int>(data_copy[(y+h)*width*channels + (x+k)*channels + c]);
                            }
                        }
                    }
                    median = cal_median(median_kernel, use_ele_num);
                    data[current_index] = static_cast<unsigned char>(median); //get the median of of the kernel
                }
            }
        }
    }

    delete[] data_copy;
}

void Filter::prewitt(Image& image, int input) {
    // Get width and height of the image
    int width = image.widthGetter();
    int height = image.heightGetter();

    // Get number of chanels
    int channels = image.channelGetter();

    // Get the data
    unsigned char* data = image.varDataGetter();

    // Create two buffers
    std::unique_ptr<unsigned char[]> buffer1(new unsigned char[width]);
    std::unique_ptr<unsigned char[]> buffer2(new unsigned char[width]);

    // Define Prewitt kernels
    const int g_x[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    const int g_y[9] = {1, 1, 1, 0, 0, 0, -1, -1, -1};

    int sum_x, sum_y, res, idx;

    // Iterating over the chanels, height and width.
    for(int c=0; c<((channels==4) ? 3 : channels); c++) {
        for (int y=0; y<height; y++) {
            for (int x=0; x<width; x++) {
                sum_x = sum_y = 0;

                // Iterating over the filter
                for(int g=0; g<9; g++) {

                    // using the absolute value. This is because I don't
                    // want to cut of the edges of the image. If the filter
                    // is over the edge of the image at the beginning
                    // (eg. x=-1 or y=-1), it should use (x=1 or y=1)
                    int x_index = x + (g % 3) - 1;
                    int y_index = y + (g / 3) - 1;

                    if(x_index < 0 || y_index < 0) {
                        x_index = abs(x_index);
                        y_index = abs(y_index);
                    }

                    // checking if the filter is over the edge at the end of the image
                    // (x=width+1 or y=height+1). It sould then use (x=width-1 or y=height-1)
                    if(x_index >= width || y_index >= height) {
                        int minus_x = 2;
                        int minus_y = 2;

                        // Checking if width and height are only one deep. If this is the
                        // case, we can not substract by 2.
                        if(width == 1) {
                            minus_x = 1;
                        }

                        if(height == 1) {
                            minus_y = 1;
                        }

                        idx = (((y_index < height) ? y_index : height-minus_y)*width+((x_index < width) ? x_index : width-minus_x))*channels+c;

                    } else {
                        idx = (y_index*width+x_index)*channels+c;
                    }

                    sum_x += g_x[g] * data[idx];
                    sum_y += g_y[g] * data[idx];
                }

                
                // Combining the vertical and horizontal filter
                res = sqrt(pow(sum_x, 2) + pow(sum_y, 2));

                // Checking if the result is over the maximum number
                // and update the buffer
                buffer1[x] = (res > 255) ? 255 : res;
            }

            // fill original image at the row that is not used
            // anymore for any calculations
            if(y > 0) {
                for(int i=0; i<width; i++) {
                    data[((y-1)*width+i)*channels+c] = buffer2[i];
                }
            }

            // swap buffers
            buffer1.swap(buffer2);
        }

        // at the end use the last data in the buffer
        for(int i=0; i<width; i++) {
            data[((height-1)*width+i)*channels+c] = buffer2[i];
        }
    }
}

void Filter::sobel(Image& image, int input)
{
    // Apply grayscale filter first
    // applyGreyscaleFilter(image);

    int width = image.widthGetter();
    int height = image.heightGetter();
    int channels = image.channelGetter();

    // Get a pointer to the image data
    unsigned char* data = image.varDataGetter();

    // Sobel operator kernels for horizontal and vertical detection
    // https://en.wikipedia.org/wiki/Sobel_operator
    int Gx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1},
                    { 0,  0,  0},
                    { 1,  2,  1}};

    // Create a copy of the original data to use for the Sobel calculations
    unsigned char* dataCopy = new unsigned char[width * height * channels];
    std::memcpy(dataCopy, data, width * height * channels);

    // Loop through each pixel in the image
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Calculate the index of the current pixel in the data array
            int index = (y * width + x) * channels;

            // set gradients to 0
            int gx = 0;
            int gy = 0;

            // Apply the Sobel kernels to the neighboring pixels
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    // Calculate the index of the neighboring pixel in the originalData array
                    int neighborIndex = ((y + i) * width + (x + j)) * channels;

                    // Get the grayscale value of the neighboring pixel
                    int grayValue;
                    if (y + i < 0 || y + i >= height || x + j < 0 || x + j >= width) {
                        // If the neighbor is outside the image, use the current pixel's value
                        grayValue = dataCopy[index];
                    } else {
                        grayValue = dataCopy[neighborIndex];
                    }

                    // update the gradients
                    gx += grayValue * Gx[i + 1][j + 1];
                    gy += grayValue * Gy[i + 1][j + 1];
                }
            }

            int magnitude = static_cast<int>(sqrt(gx * gx + gy * gy));
            magnitude = std::min(magnitude, 255); // Clip to the range [0, 255]

            // store the gradients in the data array
            data[index] = static_cast<unsigned char>(magnitude);
            data[index + 1] = static_cast<unsigned char>(magnitude);
            data[index + 2] = static_cast<unsigned char>(magnitude);
        }
    }

    delete[] dataCopy;
}

void Filter::applyGaussianBlurFilter(Image& image, int kernel_size) {
    const float sigma = 2.0;

    // Ensure the kernel size is either 5 or 7
    if (kernel_size != 5) {
        kernel_size = 7;
    }

    // Compute the Gaussian kernel
    float** kernel_values = new float* [kernel_size];
    for (int i = 0; i < kernel_size; ++i)
        kernel_values[i] = new float[kernel_size];
    
    float kernel_sum = 0;
    int radius = kernel_size / 2;
    for (int j = -radius; j <= radius; j++) {
        for (int i = -radius; i <= radius; i++) {
            float kernel_value = std::exp(-(i * i + j * j) / (2 * sigma * sigma));
            kernel_values[j + radius][i + radius] = kernel_value;
            kernel_sum += kernel_value;
        }
    }
    for (int i = 0; i < kernel_size; i++) {
        for (int j = 0; j < kernel_size; j++) {
            kernel_values[i][j] /= kernel_sum;
        }
    }

    // Apply the filter
    int width = image.widthGetter();
    int height = image.heightGetter();
    int channels = image.channelGetter();
    unsigned char* data = image.varDataGetter();
    unsigned char* temp_data = new unsigned char[width * height * channels];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channels; c++) {
                float sum = 0;
                for (int j = -radius; j <= radius; j++) {
                    for (int i = -radius; i <= radius; i++) {
                        int px = std::min(std::max(x + i, 0), width - 1);
                        int py = std::min(std::max(y + j, 0), height - 1);
                        float kernel_value = kernel_values[j + radius][i + radius];
                        sum += data[(py * width + px) * channels + c] * kernel_value;
                    }
                }
                temp_data[(y * width + x) * channels + c] = (unsigned char)std::round(sum);
            }
        }
    }

    // Copy the filtered data back to the image
    std::memcpy(data, temp_data, width * height * channels);
    delete[] temp_data;
    delete[] kernel_values;
}


void Filter::gaussian3D(Volume& volume, int kernel_size) {
    const float sigma = 2.0;
    std::cout << "\n3D gaussian start...\n";

    // Ensure the kernel size is either 5 or 7
    if (kernel_size != 5) {
        kernel_size = 7;
    }

    // Compute the Gaussian kernel
    float*** kernel_values = new float** [kernel_size];
    for (int i = 0; i < kernel_size; ++i) {
        kernel_values[i] = new float* [kernel_size];
        for (int j = 0; j < kernel_size; ++j)
            kernel_values[i][j] = new float[kernel_size];
    }

    float kernel_sum = 0;
    int radius = kernel_size / 2;
    for (int k = -radius; k <= radius; k++) {
        for (int j = -radius; j <= radius; j++) {
            for (int i = -radius; i <= radius; i++) {
                float kernel_value = std::exp(-(i * i + j * j + k * k) / (2 * sigma * sigma));
                kernel_values[k + radius][j + radius][i + radius] = kernel_value;
                kernel_sum += kernel_value;
            }
        }
    }
    for (int i = 0; i < kernel_size; i++) {
        for (int j = 0; j < kernel_size; j++) {
            for (int k = 0; k < kernel_size; k++) {
                kernel_values[i][j][k] /= kernel_sum;
            }
        }
    }

    // Apply the filter
    int width = volume.widthGetter();
    int height = volume.heightGetter();
    int depth = volume.numImagesGetter();
    int channels = volume.channelsGetter();
    int temp_idx;
    unsigned char* data = volume.varDataGetter();
    unsigned char* temp_data = new unsigned char[width * height * depth * channels];
    for (int z = 0; z < depth; z++) {
        std::cout << "\nprocessing image " << z << "/" << depth;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                for (int c = 0; c < channels; c++) {
                    float sum = 0;
                    for (int k = -radius; k <= radius; k++) {
                        for (int j = -radius; j <= radius; j++) {
                            for (int i = -radius; i <= radius; i++) {
                                int px = std::min(std::max(x + i, 0), width - 1);
                                int py = std::min(std::max(y + j, 0), height - 1);
                                int pz = std::min(std::max(z + k, 0), depth - 1);
                                float kernel_value = kernel_values[j + radius][i + radius][k + radius];
                                sum += data[((pz*height + py) * width + px) * channels + c] * kernel_value;
                            }
                        }
                    }
                    temp_idx = (z * width * height * channels) + (y * width * channels) + (x * channels) + c;
                    temp_data[temp_idx] = (unsigned char)std::round(sum);
                }
            }
        }
    }
    
    // Copy the filtered data back to the image
    std::memcpy(data, temp_data, width * height * channels * depth);
    delete[] temp_data;
    delete[] kernel_values;
    
}


void Filter::median3D(Volume& volume, int input) {
    //specify kernel size, eg:3*3, 5*5, 7*7, etc..
    int kernel_size = input;
    if(kernel_size<0){
        //If the kernel size is negative, quit the function.
        std::cout << "The kernel_size should be bigger than 0!" << std::endl;
        return;
    }
    int kernel_half = input/2; //this is the half length of the kernel size, which is the number we iterate.
    //initializing the median of the kernel and divider, if the target pixel is not at edge, divider will be the number of the kernel
    int median;
    std::vector<int> median_kernel(kernel_size*kernel_size*kernel_size,300);
    int use_ele_num = kernel_size * kernel_size * kernel_size;

    //Get width, height, number of Images and number of channels of the image
    int width = volume.widthGetter();
    int height = volume.heightGetter();
    int number = volume.numImagesGetter();
    if(kernel_size > std::min(std::min(width, height), number)){
        std::cout << "The kernel_size is too big!" << std::endl;
        //If the kernel_size is too big, quit the function.
        return;
    }
    int channels = volume.channelsGetter();

    //Get the data and make a copy for calculating median of the kernel, because original data will be modified during iterating.
    unsigned char* data = volume.varDataGetter();
    unsigned char* data_copy = new unsigned char[width*height*number*channels];
    std::copy(data, data + width * height * number * channels, data_copy);
    
    for(int c=0; c<channels; c++){//iterating over the channel
        if(channels==4 && c==3){ //ignore the transparency channel
            continue;
        }else{
            for(int z=0; z<number; z++){
                if((z+1)%10==0 || z==number-1)
                {
                    std::cout << "Iterating on the image: " << z+1 << "/" << number << std::endl;
                }
                for(int y=0; y<height; y++){//iterating over the height, only considering the pixels in the mid (kernel do not exceed picture boundaries)
                    for(int x=0; x<width; x++){//iterating over the width, only considering the pixels in the mid (kernel do not exceed picture boundaries)
                        median = 0;
                        use_ele_num = kernel_size * kernel_size * kernel_size;
                        int current_index = z*height*width*channels + y*width*channels + x*channels + c; //this is the flat index of the current pixel
                        for(int l=-kernel_half; l<kernel_half+1; l++){
                            for(int h=-kernel_half; h<kernel_half+1; h++){
                                //iterating over the kernel, h is for the kernel height and k is for the kernel width and l is for the kernel z dimension
                                for(int k=-kernel_half; k<kernel_half+1; k++){
                                    if(z+l<0 || y+h<0 || x+k<0 || z+l>=number || y+h>=height || x+k>=width){
                                        //if the kernel pixel exceeds the edge of the picture, ignore this pixel
                                        use_ele_num -= 1;
                                        median_kernel[(l+kernel_half)*kernel_size*kernel_size + (h+kernel_half)*kernel_size + (k+kernel_half)] = 300;
                                    }
                                    else{
                                        //if the kernel pixel is within the picture, add its value to median for calculating.
                                        median_kernel[(l+kernel_half)*kernel_size*kernel_size + (h+kernel_half)*kernel_size + (k+kernel_half)] = static_cast<int>(data_copy[(z+l)*height*width*channels + (y+h)*width*channels + (x+k)*channels + c]);
                                    }
                                }
                            }
                        }
                        median = cal_median(median_kernel, use_ele_num);
                        data[current_index] = static_cast<unsigned char>(median); //get the median of of the kernel
                    }
                }
            }
        }
    }

    delete[] data_copy;
}
