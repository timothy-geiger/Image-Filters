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
#include "UserInterface.h"

// Constructor
UserInterface::UserInterface() {
    this->getUserInput();
}

// Desturctor
UserInterface::~UserInterface() {}

// Get the path
std::string UserInterface::getInputPath() {
    // Delete old output
    system("clear || cls");

    std::cout << "Please input the path to the input data.\n";
    std::cout << "- For 2D images specify a path to an image (for example 'Images/gracehopper.png').\n";
    std::cout << "- For 3D volumes specify a path to a folder (for example 'Scans/confuciusornis').\n\n";
    std::cout << "> ";

    std::string path;
    std::cin >> path;

    return path;
}

// gives the multiple options and waits until the user selects one:
template <class T>
int UserInterface::getSelectionFormOptions(const char* question, std::map<int, T> options) {
    int input = -1;

    system("clear || cls");

    // aks for input until the input is valid
    while(input == -1) {

        // prints out the question
        std::cout << question << "\n\n";

        // prints all possible options
        for(auto const& option : options) {
            std::cout << "[" << option.first << "] " << option.second.name << "\n";
        }

        // asks for the user input
        std::cout << "\n> ";
        std::cin >> input;

        // Delete old output
        system("clear || cls");

        // Check if input is valid
        if(options.find(input) == options.end()) {
            std::cout << "Please select a valid option!\n\n";
            input = -1;
        }
    }

    return input;
}


// Get all 2D filters that sould be applied
std::vector<int> UserInterface::get2DFiltersFromUser() {

    // save all the filters that should be applied sequentially
    // (only the index)
    std::vector<int> result = {};

    // save user input (number of filter)
    int input;

    // ask for more filters if input is not 0
    while(input != 0 || result.size() == 0) {
        std::cout << "\nPlease input the number of the 2D filter you want to apply.\n";
        std::cout << "[0] Apply selected filter\n\n";

        // print all possible filters
        for(auto const& filter : this->filters2D) {
            std::cout << "[" << filter.first << "] " << filter.second.name << "\n";
        }

        // print all selected Filters:
        std::cout << "\n\n";
        std::cout << "Selected filters: [";

        for(int i=0; i<result.size(); i++) {
            std::cout << this->filters2D[result[i]].name << ((i == result.size()-1) ? "" : " -> ");
        }

        // Ask for user Input
        std::cout << "]\n";
        std::cout << "> ";
        std::cin >> input;

        // Delete old output
        system("clear || cls");

        // Check if input is valid
        if (this->filters2D.find(input) == this->filters2D.end()) {

            // User wants to apply all selected filters
            if(input == 0) {

                // Check if at least one filter was selected
                if(result.size() == 0) {
                    std::cout << "Please select at least one filter!\n";

                } else {
                    break;

                }
            } else {
                std::cout << "Please select a valid option!\n";

            }

        } else {
            result.push_back(input);

        }
    }

    return result;
}

// apply all filters from user input
template <class T>
void UserInterface::applyFilters(T& data, std::map<int, FunctionOption<T>>& allFilters, std::vector<int>& filtersToApply) {
    for(int i=0; i<filtersToApply.size(); i++) {

        // additional input needed for Filter
        if(allFilters[filtersToApply[i]].additionalString != "") {

            // Delete old output
            system("clear || cls");

            // Ask for input
            std::cout << allFilters[filtersToApply[i]].additionalString << "\n";
            std::cin >> allFilters[filtersToApply[i]].input;

            allFilters[filtersToApply[i]].function(data, allFilters[filtersToApply[i]].input);

        } else {
            allFilters[filtersToApply[i]].function(data, -1);
        }
    }
}


void UserInterface::applySlicing(Volume& volume, int slicerIdx, std::string& filename) {
    int val = -1;

    while(val == -1) {
        std::cout << "Please input the constant " << this->slicers[slicerIdx].additionalString << "-value:\n> ";
        std::cin >> val;

        // Delete old output
        system("clear || cls");

        if(val < 0) {
            std::cout << "Your value should not be smaller than 0!\n\n";
            val = -1;

        } else {
            // check if the input is valid
            if(this->slicers[slicerIdx].additionalString == "x") {
                if(val >= volume.widthGetter()) {
                    val = -1;
                    std::cout << "Your value should be smaller than " << volume.widthGetter() << "!\n\n";
                }  

            } else {
                if(val >= volume.heightGetter()) {
                    val = -1;
                    std::cout << "Your value should be smaller than " << volume.heightGetter() << "!\n\n";
                }
            }
        }
    }

    Image slicedImage = this->slicers[slicerIdx].function(volume, val);

    // create output directory if it does not exists
    std::string outputDirectory = "Output/" + filename;
    mkdir(outputDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    // save final image
    slicedImage.write("Output/"+ filename, this->slicers[slicerIdx].name + "_" + std::to_string(val) + ".png");
}


void UserInterface::applyProjection(Volume& volume, int projectionIdx, std::string filename, int filter3Didx) {
    
    // apply projection
    Image image = this->projections[projectionIdx].function(volume);

    // create output directory if it does not exists
    std::string outputDirectory = "Output/" + filename;
    mkdir(outputDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    int volsize = volume.numImagesGetter();
    // save final image
    if (filter3Didx == -1) {
        image.write("Output/"+ filename, this->projections[projectionIdx].name + "_" + std::to_string(volsize) + "images.png");
    } else {
        image.write("Output/"+ filename, this->filters3D[filter3Didx].name + "_" + this->projections[projectionIdx].name + "_" + std::to_string(volsize) + "images.png");
    }
    
}


// Get Input from the User
void UserInterface::getUserInput() {

    // Ask for Image/Volume
    std::string path = getInputPath();
    std::string filename;

    // If 2D Image -> 2D Filters
    // If 3D Volume -> Projection / Slice
    // Check if path if a directory
    size_t posLastDirSep = path.find_last_of("/\\");
    
    // could not find a directory sperator
    if (posLastDirSep == std::string::npos) {
        filename = path;

    // could find a directory sperator
    } else {
        filename = path.substr(posLastDirSep + 1);
    }

    size_t posDot = filename.find('.');

    // 2D Image
    if(posDot != std::string::npos) {
        Image image(path.c_str());

        // if image could not be found => exit
        if(!image.constDataGetter()) {
            return;
        }

        // Delete old output
        system("clear || cls");

        // get Filters from the user that sould be applied
        std::vector<int> filtersToApply = get2DFiltersFromUser();

        // apply filters
        applyFilters<Image>(image, this->filters2D, filtersToApply);

        // edit filename where to save the image
        std::string filtersAppliedStr;

        for(int i=0; i<filtersToApply.size(); i++) {
            filtersAppliedStr += this->filters2D[filtersToApply[i]].name + ((i == filtersToApply.size()-1) ? "" : "_");
        }

        std::string outputDirectory = "Output/" + filename.substr(0, posDot);
        std::string outputFileName = filtersAppliedStr + "." + filename.substr(posDot + 1);

        // create directory if it does not exists
        mkdir(outputDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

        // save final image
        image.write("Output/"+ filename.substr(0, posDot), outputFileName);

    } else {
        int useSubspace = getSelectionFormOptions(
            "Do you want to use all the images in that folder?",
            std::map<int, Option>{
                {1, {"Yes"}},
                {2, {"No"}},
            });

        int fromIdx, toIdx = -1;

        if(useSubspace == 2) {
            std::cout << "Please input the first z-value:\n";
            std::cin >> fromIdx;

            system("clear || cls");

            std::cout << "Please input the second z-value:\n";
            std::cin >> toIdx;
        }

        // Create Volume Object
        Volume volume(path.c_str(), fromIdx, toIdx);

        int volumeInput = getSelectionFormOptions(
            "Please input a number between 1 and 3!:",
            std::map<int, Option>{
                {1, {"Slice"}},
                {2, {"Projection"}},
                {3, {"3D-Filter & Projection"}},
            });

        // Do Slicing
        if(volumeInput == 1) {
            int slicerIdx = getSelectionFormOptions("Please input the number of the plane:", this->slicers);
            applySlicing(volume, slicerIdx, filename);
        
        // Do projection
        } else if(volumeInput == 2) {
            int projectionIdx = getSelectionFormOptions("Please input the Projection you want to apply:", this->projections);
            applyProjection(volume, projectionIdx, filename);

        // Apply a 3d Filter and a projection
        } else {
            int filter3dIdx = getSelectionFormOptions("Please input the 3D Filter you want to apply:", this->filters3D);
            int projectionIdx = getSelectionFormOptions("Please input the Projection you want to apply:", this->projections);
            
            // apply filters
            std::vector<int> filter3dList = {filter3dIdx};
            applyFilters(volume, this->filters3D, filter3dList);

            // apply projection
            applyProjection(volume, projectionIdx, filename, filter3dIdx);
        }
    }
}
