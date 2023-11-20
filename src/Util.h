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
#include <vector>
#include <string>

/**
 * @brief Utility class for sorting algorithms used in the filters and projections
 */
class Util {
public:
    /**
     * @brief Quick-select algorithm to find the k-th smallest element in a vector of unsigned chars
     *
     * @param values the reference of the values to be sorted through
     * @param k the index of the smallest element we want to find
     */
    static unsigned char quickselect(std::vector<unsigned char>& values, int k);
    /**
     * @brief Merge sort function for strings
     *
     * @param strings the reference of the vector of strings to be sorted
     */
    static void mergeSort(std::vector<std::string>& strings);
private:
    static int partition(std::vector<unsigned char>& values, int left, int right);
    static void swap(std::vector<unsigned char>& values, int i, int j);
    static void mergeHelper(std::vector<std::string>& strings, int start, int mid, int end);
};