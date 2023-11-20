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
#include "Volume.h"
#include "Util.h"

// Constructor for testing
Volume::Volume(int width, int height, int channels, int num_images) {
    this->width = width;
    this->height = height;
    this->channels = channels;
    this->num_images = num_images;
}

Volume::Volume(const char* path, int fromIdx, int toIdx, bool removeDebug) {
    this->path = path;
    
    // get all file names in folder
    std::vector<std::string> filenames;

    for (const auto & file: std::filesystem::directory_iterator(path)) {
        filenames.push_back(file.path());
    }

    if (filenames.size() == 0) {
        std::cerr << "Could not find any files inside the specified path: " << path << "\n";
        exit(0);
    }

    // Sorting images
    Util::mergeSort(filenames);

    // only use a small slab of the data
    if(fromIdx != -1 && toIdx != -1) {
        if(toIdx <= fromIdx) {
            std::cerr << "Theire is something wrong with your specified z-values!\n";
            exit(0);
        }

        filenames.erase(filenames.begin()+toIdx, filenames.end());
        filenames.erase(filenames.begin(), filenames.begin()+fromIdx+1);
    }

    // Setting the number of images
    this->num_images = filenames.size();

    if (!removeDebug) std::cout << "Loading Volume... 0%\n";
    
    int percentage = 0;
    int idx;

    // iterate over the filenames and read them
    for(int i=0; i<this->num_images; i++) {
        unsigned char* dataTmp = stbi_load(filenames[i].c_str(), &this->width, &this->height, &this->channels, 0);

        if (!dataTmp) {
            std::cerr << "Could load file: " << filenames[i] << "\n";
            continue;
        }

        // get width and heigh to create array
        if(i == 0) {
            this->data = new unsigned char[this->width * this->height * this->channels * this->num_images];
            idx = (this->width * this->height * this->channels);
        }

        // copy image into main data array
        for(int j=0; j<idx; j++) {
            this->data[i*idx + j] = dataTmp[j];
        }

        if((double)i/this->num_images*100 >= percentage && !removeDebug) {
            // Delete old output
            system("clear || cls");

            std::cout << "Loading Volume... " << percentage << "%\n";
            percentage += 10;
        }
    }
}

Volume::~Volume() {
    if (data) {
        stbi_image_free(data);
    }
}

const unsigned char* Volume::constDataGetter() const {
    return this->data;
}

unsigned char Volume::constGetValueFromData(int x, int y, int c, int z) const {
    int idx = (z * this->width * this->height * this->channels) + (y * this->width * this->channels) + (x * this->channels) + c;
    return this->data[idx];
}

unsigned char* Volume::varDataGetter() {
    return this->data;
}

int Volume::widthGetter() const {
    return this->width;
}

int Volume::heightGetter() const {
    return this->height;
}

int Volume::channelsGetter() const {
    return this->channels;
}

int Volume::numImagesGetter() const {
    return this->num_images;
}

void Volume::setData(unsigned char* data) {
    this->data = data;
}

