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
#include "Slice.h"

Image Slice::getPlaneXZ(Volume& volume, int y) {
    unsigned char* tmpData = new unsigned char[volume.widthGetter()*volume.numImagesGetter()*volume.channelsGetter()];

    for(int z=0; z<volume.numImagesGetter(); z++) {
        for(int x=0; x<volume.widthGetter(); x++) {
            for(int c=0; c<volume.channelsGetter(); c++) {
                tmpData[z*volume.widthGetter()*volume.channelsGetter() + x*volume.channelsGetter() + c] = volume.constGetValueFromData(x, y, c, z); 
            }
        }
    }

    Image image(volume.widthGetter(), volume.numImagesGetter(), volume.channelsGetter());

    // Image class deletes data with destructor (no deep copy)
    image.setData(tmpData);

    return image;
}


Image Slice::getPlaneYZ(Volume& volume, int x) {
    unsigned char* tmpData = new unsigned char[volume.heightGetter()*volume.numImagesGetter()*volume.channelsGetter()];

    for(int y=0; y<volume.heightGetter(); y++) {
        for(int z=0; z<volume.numImagesGetter(); z++) {
            for(int c=0; c<volume.channelsGetter(); c++) {
                tmpData[y*volume.numImagesGetter()*volume.channelsGetter() + z*volume.channelsGetter() + c] = volume.constGetValueFromData(x, y, c, z); 
            }
        }
    }

    Image image(volume.numImagesGetter(), volume.heightGetter(), volume.channelsGetter());

    // Image class deletes data with destructor (no deep copy)
    image.setData(tmpData);

    return image;
}