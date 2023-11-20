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
#include <iostream>
#include "Image.h"
#include "Projection.h"
#include "Util.h"

// helper function for intensity projections
Image Projection::intensityProjection(Volume& volume, std::function<unsigned char(Volume&, int, int, int, int)> projectionFunction) {
    int x = volume.widthGetter();
    int y = volume.heightGetter();
    int channels = volume.channelsGetter();
    int z = volume.numImagesGetter();

    Image image(x, y, channels);
    unsigned char* data = new unsigned char [x * y * channels];

    unsigned char value;
    for (int c = 0; c < channels; c++){
        for (int i = 0; i < x; i++){
            for (int j = 0; j < y; j++){
                data[(j * x + i) * channels + c] = projectionFunction(volume, i, j, c, z);
            }
        }
    }
    // set the image pixels values
    image.setData(data);
    return image;
}


unsigned char Projection::maxPixelProjection(Volume& volume, int i, int j, int c, int z) {
    unsigned char max = 0;
    for (int k = 0; k < z; k++) {
        unsigned char value = volume.constGetValueFromData(i, j, c, k);
        if (value > max) {
            max = value;
        }
    }
    return max;
}

unsigned char Projection::minPixelProjection(Volume& volume, int i, int j, int c, int z) {
    unsigned char min = volume.constGetValueFromData(i, j, c, 0);
    for (int k = 0; k < z; k++){
        // get the pixel value with (x, y) in the z-direction
        unsigned char value = volume.constGetValueFromData(i, j, c, k);
        // find the maximum pixel
        if (value < min){
            min = value;
        }
    }
    return min;
}

unsigned char Projection::meanPixelProjection(Volume& volume, int i, int j, int c, int z) {
    int sum = 0;
    for (int k = 0; k < z; k++) {
        sum += volume.constGetValueFromData(i, j, c, k);
    }
    return static_cast<unsigned char>(sum / z);
}

Image Projection::maximumIntensityProjection(Volume& volume) {
    return intensityProjection(volume, Projection::maxPixelProjection);
}

Image Projection::minimumIntensityProjection(Volume& volume)
{
    return intensityProjection(volume, Projection::minPixelProjection);

}

Image Projection::meanIntensityProjection(Volume& volume) {
    return intensityProjection(volume, Projection::meanPixelProjection);
}

Image Projection::medianIntensityProjection(Volume& volume)
{
    return intensityProjection(volume, Projection::medianPixelProjection);
}


unsigned char Projection::medianPixelProjection(Volume& volume, int i, int j, int c, int z) {
    std::vector<unsigned char> values;
    for (int k = 0; k < z; k++) {
        values.push_back(volume.constGetValueFromData(i, j, c, k));
    }
    int n = values.size();
    int k = n / 2;
    unsigned char median = Util::quickselect(values, k);
    if (n % 2 == 0) {
        median = (median + Util::quickselect(values, k - 1)) / 2;
    }
    return median;
}