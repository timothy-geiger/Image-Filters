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

#include <string>
#include "stb_image.h"
#include "stb_image_write.h"

/**
 * @brief The class saves the data of one image. It has different getters
 * and setters that can be used to access or set the data of the image.
 */
class Image {
public:

    /**
     * @brief Creates an image with a defined width, height and number of
     * channels. It does not preallocate the memory.
     * @param width Number of pixels in the x-direction.
     * @param height Number of pixels in the y-direction.
     * @param channels Number of channels.
     */
    Image(int width, int height, int channels);

    /**
     * @brief It loads one image and saves the data in an 1D-Array.
     * @param filename Path to the image that should be used.
     */
    Image(const char* filename);

    ~Image();

    /**
     * @brief Returns the data. The data can not be changed.
     * @return The data of the image which is stored in an 1D-Array.
     */
    const unsigned char* constDataGetter() const;

    /**
     * @brief Returns the data.
     * @return The data of the image which is stored in an 1D-Array.
     */
    unsigned char* varDataGetter();

    /**
     * @brief Returns the width of the image.
     * @return Width of the image.
     */
    int widthGetter() const;

    /**
     * @brief Returns the height of the image.
     * @return Height of the image.
     */
    int heightGetter() const;

    /**
     * @brief Returns the number of channels of the image.
     * @return Number of channels of the image.
     */
    int channelGetter() const;

    /**
     * @brief Replaces the data with different data.
     * @param data The data that should be used to replace the old data.
     * The new data should be stored in an 1D-Array.
     */
    void setData(unsigned char* data);

    /**
     * @brief Saves the data stored in this object and saves it
     * as an image file.
     * @param write_dir The directory where the image should be stored.
     * @param write_filename The filename that should be used for the image.
     */
    bool write(const std::string& write_dir, const std::string& write_filename);

private:
    int width, height, channels;
    unsigned char* data;
    const char* theFilename;
};
