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
#include <vector>
#include <map>

// to have functions as variables
#include <functional>

// for clearing the screen
#include <cstdlib>

// for creating a folder
#include <sys/stat.h>

#include "Filter.h"
#include "Volume.h"
#include "Slice.h"
#include "Projection.h"

/**
 * @brief A struct that represents an option that a User
 * can select in the UserInterface.
 */
struct Option {
    std::string name; /*!< the name of the option. */
};

/**
 * @brief A struct that represents an option that a User
 * can select in the UserInterface. When the user selects this option the
 * specified function will be called.
 * @tparam T The first input type to the function.
 */
template <class T>
struct FunctionOption : Option {
    std::function<void(T&, int)> function; /*!< The function that sould be called
                                            * When the user selects this Options. The function has two 
                                            * parameters. One arbitrary data type and an integer. */

    std::string additionalString = ""; /*!< If a String is specified, the string will be
                                        * displayed to the user and will ask him for an input (integer) */

    int input; /*!< Saves the input of the integer. */
};

/**
 * @brief A struct that represents an option that a User
 * can select in the UserInterface. When the user selects this option the
 * specified function will be called. The function can
 * return something. The function has two parameters.
 * One arbitrary data type and an integer.
 * @tparam T the first input type to the function.
 * @tparam U the return type of the function.
 */
template <class T, class U>
struct FunctionOptionWithReturn : Option {
    std::function<U(T&, int)> function; /*!< The function that should be called
                                        * when the user selects this Options. */

    std::string additionalString = ""; /*!< If a String is specified, the string will be
                                        * displayed to the user and will ask him for an input (integer) */

    int input; /*!< Saves the input of the integer. */
};

/**
 * @brief A struct that represents an option that a User
 * can select in the UserInterface. When the user selects this option the
 * specified function will be called. The function can
 * return something. The function has one parameter with an
 * arbitrary data type.
 * @tparam T the first input type to the function.
 * @tparam U the return type of the function.
 */
template <class T, class U>
struct FunctionOptionWithReturnNoInt : Option {
    std::function<U(T&)> function; /*!< The function that sould be called
                                    * when the user selects this Options. */

    std::string additionalString = ""; /*!< If a String is specified, the string will be
                                        * displayed to the user and will ask him for an input (integer) */

    int input; /*!< Saves the input of the integer. */
};


/**
 * @brief The class has different methods to deal with the input
 * of the user. It will ask the user questions and it will then call
 * based on the user input appropriate functions.
 */
class UserInterface {
public:

    /**
     * @brief Creates an User Interface Instance.
     */
    UserInterface();
    
    ~UserInterface();

    /**
     * @brief This is the main function in the user Interface.
     * This method guides the user through the whole process
     */
    void getUserInput();

    /**
     * @brief Asks the user for the input path at the beginning.
     *
     * @return The path from the user input.
     */
    std::string getInputPath();

    /**
     * @brief Gives the user different Options to choose from. The user can
     * select one Option and the method will return this selected
     * Option.
     * @param question The question that should be displayed to the user.
     * @param options A map that contains multiple Options. The map has integers
     * as keys and an Instance of an Option class as a value.
     * @tparam T Instance of the Option class that is used for the map.
     * @return The selected option.
     */
    template<class T>
    int getSelectionFormOptions(const char* question, std::map<int, T> options);

    /**
     * @brief This method asks the user which 2D Filters he wants to apply. 
     * @return All the filters the user wants to apply. The vector contains
     * integer that correspond to the key of the option in the \p filters2D map.
     */
    std::vector<int> get2DFiltersFromUser();

    /**
     * @brief This function will apply all specified filter to the 
     * specified data. It will edit the data inplace.
     * @param data The data that should be used for the filter. For example
     * Image or Volume.
     * @param allFilters All filters which were available for selection.
     * @param filtersToApply Contains the filters that should be applied from
     * \p allFilters. These are applied in the order in which they are sorted
     * in the vector.
     * @tparam T Instance of the Option class that is used for the map.
     */
    template <class T>
    void applyFilters(T& data, std::map<int, FunctionOption<T>>& allFilters, std::vector<int>& filtersToApply);

    /**
     * @brief This function will apply one slicing on the specified volume.
     * @param volume The volume that should be used for the slicing.
     * @param slicer The slicing operation that should be used for the slicing
     * (x-z plane or y-z plane). The integer corresponds the the key in the
     * \p slicers map.
     * @param filename The filename/directory anme of the volume.
     */
    void applySlicing(Volume& volume, int slicer, std::string& filename);

    /**
     * @brief This function will apply one projection on the specified volume.
     * @param volume The volume that should be used for the projection.
     * @param slicer The projection operation that should be used for the projection.
     * The integer corresponds the the key in the \p projections map.
     * @param filename The filename/directory anme of the volume.
     * @param filter3Didx The index of the 3D filter used before the projection
     */
    void applyProjection(Volume& volume, int projectionIdx, std::string filename, int filter3Didx=-1);

private:
    std::map<int, FunctionOption<Image>> filters2D = {
        {1, {"greyscale", Filter::applyGreyscaleFilter}},
        {2, {"brightness", Filter::Brightness, "Please input a brightness number: "}},
        {3, {"median-blur", Filter::applyMedianBlurFilter, "Please input the kernel size for the median blur: "}},
        {4, {"gaussian-blur", Filter::applyGaussianBlurFilter, "Please input the kernel size for the gaussian blur: "}},
        {5, {"sobel", Filter::sobel}},
        {6, {"prewitt", Filter::prewitt}}
    }; 

    std::map<int, FunctionOptionWithReturn<Volume, Image>> slicers = {
        {1, {"x-z plane", Slice::getPlaneXZ, "y"}},
        {2, {"y-z plane", Slice::getPlaneYZ, "x"}},
    };

    std::map<int, FunctionOptionWithReturnNoInt<Volume, Image>> projections = {
        {1, {"Maximum intensity projection (MIP)", Projection::maximumIntensityProjection}},
        {2, {"Minimum intensity projection (MinIP)", Projection::minimumIntensityProjection}},
        {3, {"Mean - Average intensity projection (AIP)", Projection::meanIntensityProjection}},
        {4, {"Median - Average intensity projection (AIP)", Projection::medianIntensityProjection}}
    };

    std::map<int, FunctionOption<Volume>> filters3D = {
        {1, {"3D Gaussian", Filter::gaussian3D, "Please input a kernel size for the 3D Gaussian blur filter: "}},
        {2, {"3D Median", Filter::median3D, "Please input a kernel size for the 3D Median blur filter: "}}
    };
};
