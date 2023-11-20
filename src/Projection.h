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
#include <functional>

/**
 * @brief Class with static methods to apply projections.
 */
class Projection
{
public:
    /**
     * @brief Applies the Maximum intensity projection on an volume.
     *
     * @param volume the reference of the volume that should be used
     * for the projection.
     */
    static Image maximumIntensityProjection(Volume& volume);
    
    /**
     * @brief Applies the Minumum intensity projection on an volume.
     *
     * @param volume the reference of the volume that should be used
     * for the projection.
     */
    static Image minimumIntensityProjection(Volume& volume);

    /**
     * @brief Applies the mean intensity projection on an volume.
     *
     * @param volume the reference of the volume that should be used
     * for the projection.
     */
    static Image meanIntensityProjection(Volume& volume);

    /**
     * @brief Applies the median intensity projection on an volume.
     *
     * @param volume the reference of the volume that should be used
     * for the projection.
     */
    static Image medianIntensityProjection(Volume& volume);

    
private:
    // static Image projection(Volume& volume, std::function<unsigned char(std::vector<unsigned char>)> proj_function);
    static Image intensityProjection(Volume& volume, std::function<unsigned char(Volume&, int, int, int, int)> projectionFunction);
    static unsigned char maxPixelProjection(Volume& volume, int i, int j, int c, int z);
    static unsigned char minPixelProjection(Volume& volume, int i, int j, int c, int z);
    static unsigned char meanPixelProjection(Volume& volume, int i, int j, int c, int z);
    static unsigned char medianPixelProjection(Volume& volume, int i, int j, int c, int z);
};
