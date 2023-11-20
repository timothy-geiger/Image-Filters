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
#pragma once

#include "Volume.h"
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"

/**
 * @brief Class with static methods to apply filters.
 * The Class contains 2D and 3D Filters.
 */
class Filter {
public:
    // We created Methods inside the Filter class. We did not
    // create new Classes for Each Filter type because the
    // filters do not really have something in common. So
    // we couldn't justify inheritance.
    //
    // Every function has a second parameter call input even if the
    // filter does not has an additional input like kernel size. We did this
    // because we need functions with identical parameters in order
    // to store them in a map.


    /**
     * @brief Applies greyscale filter on an image, change the
     * image color to grey.
     * 
     * @param image the reference of the image that should be used
     * for the filter.
     * 
     * @param input Because the greyscale filter does not has an
     * additional input, it should be always -1.
     */
    static void applyGreyscaleFilter(Image& image, int input=-1);

    /**
     * @brief Applies the Brightness algorithm on an image
     * to get brighter or darker one.
     *
     * @param image the reference of the image that should be used
     * for the filter.
     * @param value the user give the value that will be added to all pixels, 
     * positive value for a brighter image and 
     * negative value for a darker image
     */
    static void Brightness(Image& image, int value);

    /**
     * @brief Applies the median blur filter algorithm
     * on an image.
     *
     * @param image the reference of the image that should be used
     * for the filter.
     * @param input kernel size, eg:3x3(input=3), 5x5(input=5), 7x7(input=7), etc.
     */
    static void applyMedianBlurFilter(Image& image, int input=-1);

    /**
     * @brief Applies the gaussian blur filter algorithm
     * on an image.
     *
     * @param image the reference of the image that should be used
     * for the filter.
     * @param input kernel size, eg: 5x5(input=5) or 7x7(input=7)
     */
    static void applyGaussianBlurFilter(Image& image, int kernel_size=-1);
    
    /**
     * @brief Applies the sobel filter
     *
     * @param image the reference of the image that should be used
     * for the filter.
     * @param input parameter used to comply with user interface. Does not affect the algorithm. 
     */
    static void sobel(Image& image, int input=-1);

    /**
     * @brief Applies the prewitt edge detection algorithm
     * on an image.
     *
     * @param image the reference of the image that should be used
     * for the filter.
     * @param input Because the prewitt filter does not has an
     * additional input, it should be always -1.
     */
    static void prewitt(Image& image, int input=-1);


    // 3D Filters
    static void gaussian3D(Volume& volume, int input=-1);
    /**
     * @brief Applies the 3D median blur filter algorithm
     * on an image.
     *
     * @param volume the reference of the volume that should be used
     * for the filter.
     * @param input kernel size, eg:3x3x3(input=3), 5x5x5(input=5), 7x7x7(input=7), etc.
     */
    static void median3D(Volume& volume, int input=-1);

private:
    static int cal_median(std::vector<int>& input_vec, int input_num);
    static void quick_sort(std::vector<int>& input_vec, int low, int high);
};
