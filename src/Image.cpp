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
#include "Image.h"
#include <iostream>
#include <filesystem>
#include <fstream>

Image::Image(int width, int height, int channels) {
    this->width = width;
    this->height = height;
    this->channels = channels;
}

Image::Image(const char* filename)
{
    data = stbi_load(filename, &width, &height, &channels, 0);
    theFilename = filename;
    if (!data)
    {
        std::cerr << "This file cannot be loaded " << filename << std::endl;
    }
}

Image::~Image()
{
    if (data)
    {
        stbi_image_free(data);
    }
}

const unsigned char* Image::constDataGetter() const
// if you only want to view the data
{
    return data;
}

unsigned char* Image::varDataGetter()
// if you would like to change the data
{
    return data;
}

int Image::widthGetter() const
{
    return width;
}

int Image::heightGetter() const
{
    return height;
}

int Image::channelGetter() const
{
    return channels;
}

void Image::setData(unsigned char* data) {
    this->data = data;
}

bool Image::write(const std::string& write_dir, const std::string& write_filename)
{
    if (!data)
    {
        std::cerr << "There is no data to be written" << std::endl;
        return false;
    }

    std::string output_path = write_dir + "/" + write_filename;
    int result = stbi_write_png(output_path.c_str(), width, height, channels, data, width * channels);

    if (result == 0)
    {
        std::cerr << "Cannot write to" << output_path << std::endl;
        return false;
    }

    return true;
}
