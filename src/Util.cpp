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
#include <vector>
#include "Util.h"

using namespace std;

unsigned char Util::quickselect(std::vector<unsigned char>& values, int k) {
    int left = 0;
    int right = values.size() - 1;
    while (left <= right) { // while there are still values we havent seen
        // partition the values around the pivot
        int pivotIndex = Util::partition(values, left, right); 
        // if pivot is the kth smallest value, return it. otherwise increment left or right
        if (pivotIndex == k) {
            return values[k];
        } else if (pivotIndex < k) {
            left = pivotIndex + 1;
        } else {
            right = pivotIndex - 1;
        }
    }
    return values[left]; // should never reach here unless k is out of range
}

int Util::partition(std::vector<unsigned char>& values, int left, int right) {
    int pivotIndex = (left + right) / 2; // set pivot to middle index
    unsigned char pivotValue = values[pivotIndex];
    // move pivot to right
    Util::swap(values, pivotIndex, right);
    int curr = left;
    for (int i = left; i < right; i++) {
        // if value is less than pivot, swap it with the current left index and increment it
        if (values[i] < pivotValue) {
            Util::swap(values, i, curr);
            curr++;
        }
    }
    // move pivot to sorted position
    Util::swap(values, curr, right);
    return curr;
}

// swap two indices in a vector
void Util::swap(std::vector<unsigned char>& values, int i, int j) {
    unsigned char tmp = values[i];
    values[i] = values[j];
    values[j] = tmp;
}

void Util::mergeSort(vector<string>& strings) {
    int size = strings.size();

    // Divide into subvectors of size 1, 2, 4.. up to n - 1 that we can merge
    for(int i = 1; i < size - 1; i *= 2) {
        // loop through each subvector and merge adjacent ones
        for (int start = 0; start < size - 1; start += 2*i) {
            // get start middle end of subvector for merge
            int mid = min(start + i - 1, size - 1);
            int end = min(start + 2 * i - 1, size - 1);

            mergeHelper(strings, start, mid, end);
        }
    }
}

void Util::mergeHelper(vector<string>& strings, int start, int mid, int end) {
    // size of the subvectors
    int v1 = mid - start + 1;
    int v2 = end - mid;
    
    vector<string> left(v1), right(v2);

    // copy each half of the vector into temporary vectors
    for (int i = 0; i < v1; i++) {
        left[i] = strings[start + i];
    }
    for (int j = 0; j < v2; j++) {
        right[j] = strings[mid + j + 1];
    }

    int i = 0;
    int j = 0;
    int k = start;

    // merge the two temp vectors into a sorted one
    while(i < v1 && j < v2) {
        if(left[i] <= right[j]) {
            strings[k++] = left[i++];
        } else {
            strings[k++] = right[j++];
        }
    }

    // copy the rest of the left subvector
    while (i < v1) {
        strings[k++] = left[i++];
    }
    // copy the rest of the right subvector
    while (j < v2) {
        strings[k++] = right[j++];
    }
}