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

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include "stb_image.h"
#include "stb_image_write.h"

/**
 * @brief The class saves the data of multiple images.
 * It has different getters and setters that can be used
 * to access or set the data of the volume.
 */
class Volume {
public:

    /**
     * @brief Creates a volume with a defined width, height, number of
     * channels and number of images. It does not preallocate the memory.
     * @param width Number of pixels in the x-direction.
     * @param height Number of pixels in the y-direction.
     * @param channels Number of channels.
     * @param num_images Number of images.
     */
    Volume(int width, int height, int channels, int num_images);

    /**
     * @brief It loads all the images in the specified directory.
     * @param path Path to the directory that should be used.
     * @param fromIdx The z-coordiante from which the data should be used.
     * @param toIdx The z-coordiante up to which the data should be used.
     * @param removeDebug Whether the loading bar should be displayed.
     */
    Volume(const char* path, int fromIdx, int toIdx, bool removeDebug=false);

    ~Volume();

    /**
     * @brief Returns the data. The data can not be changed.
     * @return The data of the volume which is stored in an 1D-Array.
     */
    const unsigned char* constDataGetter() const;

    /**
     * @brief Returns the data.
     * @return The data of the volume which is stored in an 1D-Array.
     */
    unsigned char* varDataGetter();

    /**
     * @brief Returns one data point in the volume given x, y, c and z.
     * @return The data of the volume which is stored in an 1D-Array.
     * @param x x-coordinate of the data point.
     * @param y y-coordinate of the data point.
     * @param c c-coordinate of the data point.
     * @param z z-coordinate of the data point.
     */
    unsigned char constGetValueFromData(int x, int y, int c, int z) const;

    /**
     * @brief Returns the width of the Volume.
     * @return Width of the Volume.
     */
    int widthGetter() const;

    /**
     * @brief Returns the height of the Volume.
     * @return Height of the Volume.
     */
    int heightGetter() const;

    /**
     * @brief Returns the number of cahnnels of the Volume.
     * @return Number of channels of the Volume.
     */
    int channelsGetter() const;

    /**
     * @brief Returns the number of images of the Volume.
     * @return Number of images of the image.
     */
    int numImagesGetter() const;

    /**
     * @brief Replaces the data with different data.
     * @param data The data that should be used to replace the old data.
     * The new data should be stored in an 1D-Array.
     */
    void setData(unsigned char* data);

private:
    int width, height, channels, num_images;
    unsigned char* data;
    const char* path;
};
