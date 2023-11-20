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

#include "Image.h"
#include "Volume.h"
#include <iostream>

/**
 * @brief The class has two methods to slice a Volume
 * into a new plane.
 */
class Slice {
public:

    /**
     * @brief Calcualtes the x-z plane of a volume at a fixed y position.
     * @param volume The volume that should be used for the slicing.
     * @param y The constant y-value that should be used for the slicing
     * @return Returns the Image from the Slicing process.
     */
    static Image getPlaneXZ(Volume& volume, int y);

    /**
     * @brief Calcualtes the y-z plane of a volume at a fixed x position.
     * @param volume The volume that should be used for the slicing.
     * @param y The constant x-value that should be used for the slicing
     * @return Returns the Image from the Slicing process.
     */
    static Image getPlaneYZ(Volume& volume, int x);
};
