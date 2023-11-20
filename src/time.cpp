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
#include <string>
#include <vector>
#include <chrono>
#include <functional>
#include "Image.h"
#include "Filter.h"
#include "Slice.h"
#include "Projection.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// g++-12 src/time.cpp src/Image.cpp src/Filter.cpp src/Volume.cpp src/Slice.cpp src/Util.cpp src/Projection.cpp -o time

double timeFunction(std::function<void(Image&, int)> func, const char* filepath, const int input=-1, const int n=3) {
    auto total_duration = 0;

    // Executtes the function n times
    for(int i=0; i<n; i++) {
        
        // Read Image again every time, since the
        // methods update the image inplace
        Image image(filepath);

        // Only measure the actual method
        auto start = std::chrono::steady_clock::now();
        func(image, input);
        auto end = std::chrono::steady_clock::now();

        // adding this iteration to total count
        total_duration += std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    }

    return total_duration / n;
}



// Times all 2D Filter Functions
void time2DFilters(std::vector<std::string> imagePaths) {
    for(int i=0; i<imagePaths.size(); i++) {
        std::cout << "- Timings for image '" << imagePaths[i] << "':\n";

        // Testing greyscale function
        double greyscaleTiming = timeFunction(Filter::applyGreyscaleFilter, imagePaths[i].c_str());
        std::cout << "\u23F3 Avg. timing of greyscale: " << greyscaleTiming << "ms\n";

        // Testing brightness function
        double brightnessTiming = timeFunction(Filter::Brightness, imagePaths[i].c_str());
        std::cout << "\u23F3 Avg. timing of brightness: " << brightnessTiming << "ms\n";

        // Testing medianblur function
        double medianblurTiming5 = timeFunction(Filter::applyMedianBlurFilter, imagePaths[i].c_str(), 5);
        std::cout << "\u23F3 Avg. timing of medianblur (5x5): " << medianblurTiming5 << "ms\n";

        double medianblurTiming7 = timeFunction(Filter::applyMedianBlurFilter, imagePaths[i].c_str(), 7);
        std::cout << "\u23F3 Avg. timing of medianblur (7x7): " << medianblurTiming7 << "ms\n";

        // Testing medianblur function
        double gaussianblurTiming5 = timeFunction(Filter::applyGaussianBlurFilter, imagePaths[i].c_str(), 5);
        std::cout << "\u23F3 Avg. timing of gaussianblur (5x5): " << gaussianblurTiming5 << "ms\n";

        double gaussianblurTiming7 = timeFunction(Filter::applyGaussianBlurFilter, imagePaths[i].c_str(), 7);
        std::cout << "\u23F3 Avg. timing of gaussianblur (7x7): " << gaussianblurTiming7 << "ms\n";

        // Testing sobel function
        double sobelTiming = timeFunction(Filter::sobel, imagePaths[i].c_str());
        std::cout << "\u23F3 Avg. timing of sobel: " << sobelTiming << "ms\n";

        // Testing prewitt function
        double prewittTiming = timeFunction(Filter::prewitt, imagePaths[i].c_str());
        std::cout << "\u23F3 Avg. timing of prewitt: " << prewittTiming << "ms\n";

        std::cout << "\n";
    }
}

double timeSliceFunction(std::function<void(Volume&, int val)> func, Volume& volume, int val, const int n=3) {
    auto total_duration = 0;
    // Volume volume(filepath, zmin, zmax);

    // Executes the function n times
    for(int i=0; i<n; i++) {

        // Only measure the actual method
        auto start = std::chrono::steady_clock::now();
        func(volume, val);
        auto end = std::chrono::steady_clock::now();

        // adding this iteration to total count
        total_duration += std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    }

    return total_duration / n;
}

void timeSlicing(std::vector<std::string> volumePaths, int vol_size) {

    for(int i = 0; i < volumePaths.size(); i++) {
        Volume volume(volumePaths[i].c_str(), 0, vol_size, true);
        std::cout << "- Timings for volume '" << volumePaths[i] << " with num images: " << volume.numImagesGetter() + 1 << ":\n";

        double xzIntensityTiming = timeSliceFunction(Slice::getPlaneXZ, volume, 10);
        std::cout << "\u23F3 Avg. timing of XZ Slicing: " << xzIntensityTiming << "ms\n";

        double yzIntensityTiming = timeSliceFunction(Slice::getPlaneYZ, volume, 10);
        std::cout << "\u23F3 Avg. timing of YZ Slicing: " << yzIntensityTiming << "ms\n";

        std::cout << "\n";
    }
}

double timeProjectionFunction(std::function<void(Volume&)> func, Volume& volume, const int n=3) {
    auto total_duration = 0;
    // Volume volume(filepath, zmin, zmax);

    // Executes the function n times
    for(int i=0; i<n; i++) {

        // Only measure the actual method
        auto start = std::chrono::steady_clock::now();
        func(volume);
        auto end = std::chrono::steady_clock::now();

        // adding this iteration to total count
        total_duration += std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    }

    return total_duration / n;
}


void time3DProjections(std::vector<std::string> volumePaths, int vol_size) {

    for(int i = 0; i < volumePaths.size(); i++) {
        Volume volume(volumePaths[i].c_str(), 0, vol_size, true);
        std::cout << "- Timings for volume '" << volumePaths[i] << " with num images: " << volume.numImagesGetter() + 1 << ":\n";

        double maxIntensityTiming = timeProjectionFunction(Projection::maximumIntensityProjection, volume);
        std::cout << "\u23F3 Avg. timing of maximum intensity projection: " << maxIntensityTiming << "ms\n";

        double minIntensityTiming = timeProjectionFunction(Projection::minimumIntensityProjection, volume);
        std::cout << "\u23F3 Avg. timing of minimum intensity projection: " << minIntensityTiming << "ms\n";

        double meanIntensityTiming = timeProjectionFunction(Projection::meanIntensityProjection, volume);
        std::cout << "\u23F3 Avg. timing of mean intensity projection: " << meanIntensityTiming << "ms\n";

        double medianIntensityTiming = timeProjectionFunction(Projection::medianIntensityProjection, volume);
        std::cout << "\u23F3 Avg. timing of median intensity projection: " << medianIntensityTiming << "ms\n";

        std::cout << "\n";
    }
}

double time3DFilterFunction(std::function<void(Volume&, int val)> func, Volume& volume, int val, const int n=3) {
    auto total_duration = 0;
    // Volume volume(filepath, zmin, zmax);

    // Executes the function n times
    for(int i=0; i<n; i++) {

        // Only measure the actual method
        auto start = std::chrono::steady_clock::now();
        std::cout.setstate(std::ios_base::failbit);
        func(volume, val);
        std::cout.clear();
        auto end = std::chrono::steady_clock::now();

        // adding this iteration to total count
        total_duration += std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
    }

    return total_duration / n;
}

void time3DFilters(std::vector<std::string> volumePaths, int vol_size) {

    for(int i = 0; i < volumePaths.size(); i++) {
        Volume volume(volumePaths[i].c_str(), 0, 10, true);
        std::cout << "- Timings for volume '" << volumePaths[i] << " with num images: " << vol_size << ":\n";

        // Median Blur
        double medianTiming5 = time3DFilterFunction(Filter::median3D, volume, 5, 1);
        std::cout << "\u23F3 Avg. timing (projected) of the median 3d filter (5x5): " << (medianTiming5/10)*vol_size << "s\n";

        // Gaussian
        double gaussianTiming5 = time3DFilterFunction(Filter::gaussian3D, volume, 5, 1);
        std::cout << "\u23F3 Avg. timing (projected) of the gaussian 3d filter (5x5): " << (gaussianTiming5/10)*vol_size << "s\n";

        std::cout << "\n";
    }
}


int main() {

    // 2D Filters
    std::cout << "=============================\n";
    std::cout << "TIMING\n";
    std::cout << "=============================\n";

    std::cout << "Timings of 2D-Filters:\n\n";
    std::vector<std::string> imagePaths = {"Images/gracehopper.png", "Images/tienshan.png"};
    time2DFilters(imagePaths);

    // Volumes
    std::vector<std::string> volumePaths = {"Scans/confuciusornis", "Scans/fracture"};

    // Slicing
    std::cout << "=============================\n\n";
    std::cout << "Timings of Slicing:\n\n";
    timeSlicing(volumePaths, 20);
    timeSlicing(volumePaths, 200);

    // Projections
    std::cout << "=============================\n\n";
    std::cout << "Timings of 3D-Projections:\n\n";
    time3DProjections(volumePaths, 20);
    time3DProjections(volumePaths, 200);

    // 3D-Filters
    std::cout << "=============================\n\n";
    std::cout << "Timings of 3D-Filters:\n\n";
    time3DFilters(volumePaths, 20);
    time3DFilters(volumePaths, 200);

    return 0;
}