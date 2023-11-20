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
#include <cstring>
#include <iostream>
#include "Testing.h"
#include "Image.h"
#include "Filter.h"
#include "Slice.h"
#include "Volume.h"
#include "Projection.h"
#include "Util.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"




bool hasSameContents2D(unsigned char* a, unsigned char* b, const int size) {
    if(std::memcmp(a, b, sizeof(unsigned char) * size) == 0) {
        return true;

    } else {
        return false;

    }
}

class MergeSortTest : public Test {
public:
    MergeSortTest() : Test("MergeSortTest") {}
    void run() override {
        bool simple_test = testSimple();
        assert_true(simple_test, "simple merge sort test");

        bool filename_test = testFileNames();
        assert_true(filename_test, "merge sort test with filenames");
    }

    bool testSimple() {
        std::vector<std::string> stringdata = {"6", "2", "3", "1", "4", "5"};

        std::vector<std::string> expectedResult = {"1", "2", "3", "4", "5", "6"};

        // Check if function has correct results
        Util::mergeSort(stringdata);

        return expectedResult == stringdata;
    }

    bool testFileNames() {
        std::vector<std::string> stringdata = {"confu010.png", "confu008.png", "confu009.png", "confu001.png", "confu011.png", "confu004.png"};

        std::vector<std::string> expectedResult = {"confu001.png", "confu004.png",  "confu008.png", "confu009.png", "confu010.png", "confu011.png"};

        // Check if function has correct results
        Util::mergeSort(stringdata);

        return expectedResult == stringdata;
    }
    
};

class QuickSelectTest : public Test {
public:
    QuickSelectTest() : Test("QuickSelectTest") {}
    void run() override {
        bool simple_test = testsmall();
        assert_true(simple_test, "simple quick select test");

        bool large_test = testlarge();
        assert_true(large_test, "larger quick select test");
    }

    bool testsmall() {
        std::vector<unsigned char> data = {8,5,6,2,1,3,7,4,9};

        unsigned char expected = static_cast<unsigned char>(3);

        // Check if function has correct results
        unsigned char result = Util::quickselect(data, 2);

        return result == expected;
    }

    bool testlarge() {
        std::vector<unsigned char> data = {8,5,6,2,1,3,7,4,9,200,10,15,20,12};

        unsigned char expected = static_cast<unsigned char>(200);

        // Check if function has correct results
        unsigned char result = Util::quickselect(data, 13);

        return result == expected;
    }
    
};


class GreyscaleTest : public Test {
public:
    GreyscaleTest() : Test("Greyscale") {}
    void run() override {
        // Set starting data with 1 row, 1 column and 3 channels 
        Image image5(1, 3, 3);

        unsigned char* data5 = new unsigned char[9]{ 255, 0, 0,   // Red pixel
                                                      0, 255, 0,   // Green pixel
                                                      0, 0, 255 }; // Blue pixel;
        image5.setData(data5);
        // Expected Data (Calculated on paper)
        unsigned char expectedData5[9] = {76, 76, 76, 148, 148, 148, 29, 29, 29};
        // Check if function has correct results
        Filter::applyGreyscaleFilter(image5);
        unsigned char* data_tmp = image5.varDataGetter();

        bool res5 = hasSameContents2D(image5.varDataGetter(), expectedData5, 9);
        // print out the test result
        assert_true(res5, "1x3x3 Pixel");

    }
    
};


class MedianBlurTest : public Test {
public:
    MedianBlurTest() : Test("MedianBLur") {}
    void run() override {
        bool white_img_test = testMedianBlurOnWhiteImage();
        assert_true(white_img_test, "white_image_medianblur");

        bool black_img_test = testMedianBlurOnBlackImage();
        assert_true(black_img_test, "black_image_medianblur");

        bool horiz_img_test = testMedianBlurOnHorizontalEdge();
        assert_true(horiz_img_test, "horizontal_edge_medianblur");

    }

    bool testMedianBlurOnWhiteImage() {
        // Set starting data
        Image white_img(3, 3, 2);

        unsigned char* white_data = new unsigned char[18]{255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
        white_img.setData(white_data);

        unsigned char expected_data[18] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

        Filter::applyMedianBlurFilter(white_img, 3);

    
        bool whitemedian = hasSameContents2D(white_img.varDataGetter(), expected_data, 18);
        return whitemedian;
    }

    bool testMedianBlurOnBlackImage() {
        Image black_img(3, 3, 2);

        unsigned char* black_data = new unsigned char[18]{0, 0, 0, 0, 0, 0, 
                                                          0, 0, 0, 0, 0, 0, 
                                                          0, 0, 0, 0, 0, 0};
        black_img.setData(black_data);

        unsigned char expected_data[18] = {0, 0, 0, 0, 0, 0, 
                                           0, 0, 0, 0, 0, 0, 
                                           0, 0, 0, 0, 0, 0};

        Filter::applyMedianBlurFilter(black_img, 3);
        
        bool blackmedian = hasSameContents2D(black_img.varDataGetter(), expected_data, 18);
        return blackmedian;
    }

    bool testMedianBlurOnHorizontalEdge() {
        Image horizontal_edge_img(3,3,2);

        unsigned char* horizontal_edge_data = new unsigned char[18]{0, 0, 0, 0, 0, 0, 
                                                                    0, 0, 0, 0, 0, 0,
                                                                    255, 255, 255, 255, 255, 255};
        horizontal_edge_img.setData(horizontal_edge_data);

        unsigned char expected_data[18] = {0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0,
                                           127, 127, 127, 127, 127, 127};

        Filter::applyMedianBlurFilter(horizontal_edge_img, 3);
        
        bool horiz = hasSameContents2D(horizontal_edge_img.varDataGetter(), expected_data, 18);
        return horiz;
    }
};

class GaussianBlurTest : public Test {
public:
   GaussianBlurTest() : Test("GaussianBLur") {}
    void run() override {
        bool white_img_test = testGaussianBlurOnWhiteImage();
        assert_true(white_img_test, "white_image_gaussianblur");

        bool black_img_test = testGaussianBlurOnBlackImage();
        assert_true(black_img_test, "black_image_gaussianblur");

        bool horiz_img_test = testGaussianBlurOnHorizontalEdge();
        assert_true(horiz_img_test, "horizontal_edge_gaussianblur");

    }

    bool testGaussianBlurOnWhiteImage() {
        // Set starting data
        Image white_img(3, 3, 2);

        unsigned char* white_data = new unsigned char[18]{255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
        white_img.setData(white_data);

        unsigned char expected_data[18] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

        Filter::applyGaussianBlurFilter(white_img, 5);

    
        bool whitemedian = hasSameContents2D(white_img.varDataGetter(), expected_data, 18);
        return whitemedian;
    }

    bool testGaussianBlurOnBlackImage() {
        Image black_img(3, 3, 2);

        unsigned char* black_data = new unsigned char[18]{0, 0, 0, 0, 0, 0, 
                                                          0, 0, 0, 0, 0, 0, 
                                                          0, 0, 0, 0, 0, 0};
        black_img.setData(black_data);

        unsigned char expected_data[18] = {0, 0, 0, 0, 0, 0, 
                                           0, 0, 0, 0, 0, 0, 
                                           0, 0, 0, 0, 0, 0};

        Filter::applyGaussianBlurFilter(black_img, 5);
        
        bool blackmedian = hasSameContents2D(black_img.varDataGetter(), expected_data, 18);
        return blackmedian;
    }

    bool testGaussianBlurOnHorizontalEdge() {
        Image horizontal_edge_img(3,3,2);

        unsigned char* horizontal_edge_data = new unsigned char[18]{0, 0, 0, 0, 0, 0, 
                                                                    0, 0, 0, 0, 0, 0,
                                                                    255, 255, 255, 255, 255, 255};
        horizontal_edge_img.setData(horizontal_edge_data);


        unsigned char expected_data[18] = {39, 39, 39, 39, 39, 39,
                                           95, 95, 95, 95, 95, 95,
                                           160, 160, 160, 160, 160, 160};

        Filter::applyGaussianBlurFilter(horizontal_edge_img, 5);
        

        bool horiz = hasSameContents2D(horizontal_edge_img.varDataGetter(), expected_data, 18);
        return horiz;
    }
};

class BrightnessTest: public Test{
public:
    BrightnessTest(): Test("Brightness"){}
    void run() override{
        // Test 1
        Image image1(1, 1, 1);
        unsigned char* data1 = new unsigned char[1]{1};
        image1.setData(data1);
        unsigned char* expectedData1 = new unsigned char[1]{21};
        // Check the result of Brightness function
        Filter::Brightness(image1, 20);
        bool res1 = hasSameContents2D(image1.varDataGetter(), expectedData1, 1);
        assert_true(res1, "Test 1");

        // Test 2
        Image image2(3, 2, 1);
        unsigned char* data2 = new unsigned char[6]{23, 24, 25, 26, 27, 28};
        image2.setData(data2);
        unsigned char* expectedData2 = new unsigned char[6]{3, 4, 5, 6, 7, 8};
        // Check the result of Brightness function
        Filter::Brightness(image2, -20);
        bool res2 = hasSameContents2D(image2.varDataGetter(), expectedData2, 6);
        assert_true(res2, "Test 2");
    }
};


class PrewittTest : public Test {
public:
    PrewittTest() : Test("Prewitt") {}
    void run() override {
        int numPassedTests = 0;

        /** 
         * Test function with one Pixel
        */

        // Set starting data
        Image image1(1, 1, 1);

        unsigned char* data1 = new unsigned char[1]{1};
        image1.setData(data1);

        // Expected Data
        unsigned char expectedData1[1] = {0};

        // Check if function has correct results
        Filter::prewitt(image1);
        bool res1 = hasSameContents2D(image1.varDataGetter(), expectedData1, 1);
        assert_true(res1, "1x1 Pixel");


        /**
         * Test function with 1 colum and 3 rows
        */

        // Set starting data
        Image image2(1, 3, 1);

        unsigned char* data2 = new unsigned char[3]{1, 1, 1};
        image2.setData(data2);

        // Expected Data
        unsigned char expectedData2[3] = {0, 0, 0};

        // Check if function has correct results
        Filter::prewitt(image2);
        bool res2 = hasSameContents2D(image2.varDataGetter(), expectedData2, 3);
        assert_true(res2, "1x3 Pixel");


        /**
         * Test function with 3 colums and 1 row
        */

        // Set starting data
        Image image3(3, 1, 1);

        unsigned char* data3 = new unsigned char[3]{1, 1, 1};
        image3.setData(data3);

        // Expected Data
        unsigned char expectedData3[3] = {0, 0, 0};

        // Check if function has correct results
        Filter::prewitt(image3);
        bool res3 = hasSameContents2D(image3.varDataGetter(), expectedData3, 3);
        assert_true(res3, "3x1 Pixel");


        /**
         * Test function with 3 colums and 3 row
        */

        // Set starting data
        Image image4(3, 3, 1);

        unsigned char* data4 = new unsigned char[9]{50, 50, 100, 50, 50, 100, 50, 50, 100};
        image4.setData(data4);

        // Expected Data (Calculated on paper)
        unsigned char expectedData4[9] = {0, 150, 0, 0, 150, 0, 0, 150, 0};

        // Check if function has correct results
        Filter::prewitt(image4);
        bool res4 = hasSameContents2D(image4.varDataGetter(), expectedData4, 9);
        assert_true(res4, "3x3 Pixel");


        /**
         * Test function with 3 colums and 3 row and 2 channels
        */

        // Set starting data
        Image image5(3, 3, 2);

        unsigned char* data5 = new unsigned char[18]{50, 100, 50, 50, 100, 50, 50, 100, 50, 50,100, 50, 50, 100, 50, 50, 100, 50};
        image5.setData(data5);

        // Expected Data (Calculated on paper)
        unsigned char expectedData5[18] = {0, 0, 150, 150, 0, 0, 0, 0, 150, 150, 0, 0, 0, 0, 150, 150, 0, 0};

        // Check if function has correct results
        Filter::prewitt(image5);
        bool res5 = hasSameContents2D(image5.varDataGetter(), expectedData5, 18);
        assert_true(res5, "3x3x2 Pixel");

    }
};

class SobelTest : public Test {
public:
    SobelTest() : Test("Sobel") {}
    void run() override {
        bool white_img_test = testSobelEdgeDetectionOnWhiteImage();
        assert_true(white_img_test, "white_image_sobel");

        bool black_img_test = testSobelEdgeDetectionOnBlackImage();
        assert_true(black_img_test, "black_image_sobel");

        bool horiz_img_test = testSobelHorizontalEdge();
        assert_true(horiz_img_test, "horizontal_edge_sobel");

    }

    bool testSobelEdgeDetectionOnWhiteImage() {
        // Set starting data
        Image white_img(3, 3, 2);

        unsigned char* white_data = new unsigned char[18]{255, 255, 255, 255, 255, 255, 
                                                          255, 255, 255, 255, 255, 255, 
                                                          255, 255, 255, 255, 255, 255};
        white_img.setData(white_data);

        unsigned char expected_data[18] = {0, 0, 0, 0, 0, 0, 
                                           0, 0, 0, 0, 0, 0, 
                                           0, 0, 0, 0, 0, 0};

        Filter::sobel(white_img);

        bool whitesobel = hasSameContents2D(white_img.varDataGetter(), expected_data, 18);
        return whitesobel;
    }

    bool testSobelEdgeDetectionOnBlackImage() {
        Image black_img(3, 3, 2);

        unsigned char* black_data = new unsigned char[18]{0, 0, 0, 0, 0, 0, 
                                                          0, 0, 0, 0, 0, 0, 
                                                          0, 0, 0, 0, 0, 0};
        black_img.setData(black_data);

        unsigned char expected_data[18] = {0, 0, 0, 0, 0, 0, 
                                           0, 0, 0, 0, 0, 0, 
                                           0, 0, 0, 0, 0, 0};

        Filter::sobel(black_img);
        
        bool blacksobel = hasSameContents2D(black_img.varDataGetter(), expected_data, 18);
        return blacksobel;
    }

    bool testSobelHorizontalEdge() {
        Image horizontal_edge_img(3,3,2);

        unsigned char* horizontal_edge_data = new unsigned char[18]{0, 0, 0, 0, 0, 0, 
                                                                    0, 0, 0, 0, 0, 0,
                                                                    255, 255, 255, 255, 255, 255};
        horizontal_edge_img.setData(horizontal_edge_data);

        unsigned char expected_data[18] = {0, 0, 0, 0, 0, 0,
                                           255, 255, 255, 255, 255, 255,
                                           255, 255, 255, 255, 255, 255};

        Filter::sobel(horizontal_edge_img);

        bool horiz = hasSameContents2D(horizontal_edge_img.varDataGetter(), expected_data, 18);
        return horiz;
    }

};


class VolumeValueGetterTest : public Test {
public:
    VolumeValueGetterTest() : Test("Volume Test") {}
    void run() override {
        bool result1x1 = checkFor1x1x1x1Volumes();
        assert_true(result1x1, "1x1x1x1 dimesnions");

        bool result4x3x3x3 = checkFor4x3x3x3Volumes();
        assert_true(result4x3x3x3, "4x3x3x3 dimesnions");
    }

    bool checkFor1x1x1x1Volumes() {
        // Set starting data
        Volume volume(1, 1, 1, 1);

        unsigned char* data = new unsigned char[1]{3};
        volume.setData(data);

        unsigned char expected_data = 3;
        unsigned char res = volume.constGetValueFromData(0, 0, 0, 0);

        return res == expected_data;
    }

    bool checkFor4x3x3x3Volumes() {
        // Set starting data
        Volume volume(4, 3, 3, 3);

        unsigned char* data = new unsigned char[108]{
            // Image 1
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,

            // Image 2
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,

            // Image 3
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,1,0,  0,0,0,  0,0,0,
        };
        
        volume.setData(data);

        unsigned char expected_data = 1;

        // third image -> 2 channel ->
        unsigned char res = volume.constGetValueFromData(1, 2, 1, 2);

        return res == expected_data;
    }

};


class XZPlaneTest : public Test {
public:
    XZPlaneTest() : Test("x-z plane") {}
    void run() override {
        bool result1x1 = checkFor1x1Images();
        assert_true(result1x1, "3 images with 1x1 dimesnions");

        bool result3x3 = checkFor3x3Images();
        assert_true(result3x3, "3 images with 3x3 dimesnions");

        bool result3x3_n = checkFor3x3ImagesNeg();
        assert_true(result3x3_n, "3 images with 3x3 dimesnions (negative example)");
    }

    bool checkFor1x1Images() {
        // Set starting data
        Volume volume(1, 1, 1, 3);

        unsigned char* data = new unsigned char[3]{0, 0, 0};
        volume.setData(data);

        unsigned char expected_data[3] = {0, 0, 0};

        Image image = Slice::getPlaneXZ(volume, 0);

        bool res = hasSameContents2D(image.varDataGetter(), expected_data, 3);
        return res;
    }

    bool checkFor3x3Images() {
        // Set starting data
        Volume volume(3, 3, 1, 3);

        unsigned char* data = new unsigned char[27]{
            0, 0, 0, 1, 1, 1, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 0, 0, 0
        };

        volume.setData(data);

        unsigned char expected_data[9] = {
            1, 1, 1, 1, 1, 1, 1, 1, 1
        };

        Image image = Slice::getPlaneXZ(volume, 1);

        bool res = hasSameContents2D(image.varDataGetter(), expected_data, 9);
        return res;
    }

    bool checkFor3x3ImagesNeg() {
        // Set starting data
        Volume volume(3, 3, 1, 3);

        unsigned char* data = new unsigned char[27]{
            0, 0, 0, 1, 1, 1, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 0, 0, 0
        };

        volume.setData(data);

        unsigned char expected_data[9] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0
        };

        Image image = Slice::getPlaneXZ(volume, 0);

        bool res = hasSameContents2D(image.varDataGetter(), expected_data, 9);
        return res;
    }

};

class YZPlaneTest : public Test {
public:
    YZPlaneTest() : Test("y-z plane") {}
    void run() override {
        bool result1x1 = checkFor1x1Images();
        assert_true(result1x1, "3 images with 1x1 dimesnions");

        bool result3x3 = checkFor3x3Images();
        assert_true(result3x3, "3 images with 3x3 dimesnions");

        bool result3x3_n = checkFor3x3ImagesNeg();
        assert_true(result3x3_n, "3 images with 3x3 dimesnions (negative example)");
    }

    bool checkFor1x1Images() {
        // Set starting data
        Volume volume(1, 1, 1, 3);

        unsigned char* data = new unsigned char[3]{0, 0, 0};
        volume.setData(data);

        unsigned char expected_data[3] = {0, 0, 0};

        Image image = Slice::getPlaneYZ(volume, 0);

        bool res = hasSameContents2D(image.varDataGetter(), expected_data, 3);
        return res;
    }

    bool checkFor3x3Images() {
        // Set starting data
        Volume volume(3, 3, 1, 3);

        unsigned char* data = new unsigned char[27]{
            0, 0, 0, 1, 1, 1, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 0, 0, 0,
            0, 0, 0, 1, 1, 1, 0, 0, 0
        };

        volume.setData(data);

        unsigned char expected_data[9] = {
            0, 0, 0, 1, 1, 1, 0, 0, 0
        };

        Image image = Slice::getPlaneYZ(volume, 1);

        bool res = hasSameContents2D(image.varDataGetter(), expected_data, 9);
        return res;
    }

    bool checkFor3x3ImagesNeg() {
        // Set starting data
        Volume volume(3, 3, 1, 3);

        unsigned char* data = new unsigned char[27]{
            0, 0, 1, 0, 0, 1, 0, 0, 1,
            0, 0, 1, 0, 0, 1, 0, 0, 1,
            0, 0, 1, 0, 0, 1, 0, 0, 1
        };

        volume.setData(data);

        unsigned char expected_data[9] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0
        };

        Image image = Slice::getPlaneYZ(volume, 1);

        bool res = hasSameContents2D(image.varDataGetter(), expected_data, 9);
        return res;
    }

};


class MinProjectionTest : public Test {
public:
    MinProjectionTest() : Test("minimum intensity projection") {}
    void run() override {
        bool test = Min_test();
        bool test_3images_3channels = MinProjection_3images_3channels();
        assert_true(test, "Minimum Projection");
        assert_true(test_3images_3channels, "Minimum Projection on 3 images with 3 channels");
    }
    
    bool Min_test() {
        Volume testVolume(3, 2, 1, 2);
        unsigned char* testData = new unsigned char[12]{
            // Image 1
            0,1,2,
            1,0,3,

            // Image 2
            2,0,3,
            0,1,1,
        };

        testVolume.setData(testData);
        unsigned char* expectedResult0 = new unsigned char[6]{0,0,2,0,0,1};

        Image result = Projection::minimumIntensityProjection(testVolume);

        unsigned char* result0 = result.varDataGetter();
        for (int i = 0; i < 6; i++) {
            // std::cout << static_cast<int>(result0[i]) << '\n';
            if (result0[i] != expectedResult0[i]) return false;
        }
        
        return true;
    }
    
    bool MinProjection_3images_3channels() {
        int width = 4;
        int height = 3;
        int channels = 3;
        int num_images = 3;
        Volume testVolume(width, height, channels, num_images);

        unsigned char* testData = new unsigned char[108]{
            // Image 1
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,

            // Image 2
            1,1,1,  2,2,2,  3,3,3,  4,4,4,
            1,1,1,  2,2,2,  3,3,3,  4,4,4,
            1,1,1,  2,2,2,  3,3,3,  4,4,4,

            // Image 3
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
        };

        testVolume.setData(testData);
        unsigned char* expectedResult0 = new unsigned char[36]{
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
        };

        Image result = Projection::minimumIntensityProjection(testVolume);

        unsigned char* result0 = result.varDataGetter();
        for (int i = 0; i < 36; i++) {
            //std::cout << static_cast<int>(result0[i]) << '\n';
            if (result0[i] != expectedResult0[i]) return false;
        }
        return true;
    }
};


class MaxProjectionTest : public Test {
public:
    MaxProjectionTest() : Test("maximum intensity projection") {}
    void run() override {
        bool test = MIPtest();
        bool test_3images_3channels = MaxProjection_3images_3channels();
        assert_true(test, "MIP");
        assert_true(test_3images_3channels, "MIP on 3 images with 3 channels");

    }
    
    // check the test result
    bool MIPtest() {
        Volume testVolume(3, 2, 1, 2);
        unsigned char* testData = new unsigned char[12]{
            // Image 1
            0,1,2,
            1,0,3,

            // Image 2
            2,0,3,
            0,1,1,
        };
        testVolume.setData(testData);
        // the expected value (maximum)
        unsigned char* expectedResult0 = new unsigned char[6]{2,1,3,1,1,3};

        Image result = Projection::maximumIntensityProjection(testVolume);

        // check the MIP algorithm result
        unsigned char* result0 = result.varDataGetter();
        for (int i = 0; i < 6; i++) {
            // fail if some values not is the same as the expected
            if (result0[i] != expectedResult0[i]) return false;
        }
        
        return true;
    }

    bool MaxProjection_3images_3channels() {
        int width = 4;
        int height = 3;
        int channels = 3;
        int num_images = 3;
        Volume testVolume(width, height, channels, num_images);

        unsigned char* testData = new unsigned char[108]{
            // Image 1
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,

            // Image 2
            1,1,1,  2,2,2,  3,3,3,  4,4,4,
            1,1,1,  2,2,2,  3,3,3,  4,4,4,
            1,1,1,  2,2,2,  3,3,3,  4,4,4,

            // Image 3
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
        };

        testVolume.setData(testData);
        unsigned char* expectedResult0 = new unsigned char[36]{
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
        };

        Image result = Projection::maximumIntensityProjection(testVolume);

        unsigned char* result0 = result.varDataGetter();
        for (int i = 0; i < 36; i++) {
            //std::cout << static_cast<int>(result0[i]) << '\n';
            if (result0[i] != expectedResult0[i]) return false;
        }
        return true;
    }
};

class MeanProjectionTest : public Test {
public:
    MeanProjectionTest() : Test("mean projection") {}
    void run() override {
        bool test1images = meanProjection_1images_1channels();
        bool test3images = meanProjection_3images_3channels();
        bool test3images_1channels = meanProjection_3images_1channels();
        assert_true(test1images, "mean projection with 1 images");
        assert_true(test3images, "mean projection with 3 images with 3 channels");
        assert_true(test3images_1channels,"mean projection with 3 images with 1 channels");

    }

    bool meanProjection_1images_1channels() {
        int width = 4;
        int height = 3;
        int channels = 1;
        int num_images = 1;
        Volume testVolume(width, height, channels, num_images);

        unsigned char* testData = new unsigned char[12]{
            // image1
            1,3,3,2,
            3,2,2,3,
            2,3,1,1
        };

        testVolume.setData(testData);
        unsigned char* expectedResult0 = new unsigned char[12]{
            1,3,3,2,
            3,2,2,3,
            2,3,1,1
        };

        Image result = Projection::meanIntensityProjection(testVolume);

        unsigned char* result0 = result.varDataGetter();
        for (int i = 0; i < 12; i++) {
            // std::cout << static_cast<int>(result0[i]) << '\n';
            if (result0[i] != expectedResult0[i]) return false;
        }
        
        return true;
    }

    bool meanProjection_3images_3channels() {
        int width = 4;
        int height = 3;
        int channels = 3;
        int num_images = 3;
        Volume testVolume(width, height, channels, num_images);

        unsigned char* testData = new unsigned char[108]{
            // Image 1
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,

            // Image 2
            1,1,1,  2,2,2,  3,3,3,  4,4,4,
            1,1,1,  2,2,2,  3,3,3,  4,4,4,
            1,1,1,  2,2,2,  3,3,3,  4,4,4,

            // Image 3
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
        };

        testVolume.setData(testData);
        unsigned char* expectedResult0 = new unsigned char[36]{
            2,2,2,  2,2,2,  3,3,3,  4,4,4,
            2,2,2,  2,2,2,  3,3,3,  4,4,4,
            2,2,2,  2,2,2,  3,3,3,  4,4,4,
        };

        Image result = Projection::meanIntensityProjection(testVolume);

        unsigned char* result0 = result.varDataGetter();
        for (int i = 0; i < 36; i++) {
            //std::cout << static_cast<int>(result0[i]) << '\n';
            if (result0[i] != expectedResult0[i]) return false;
        }
        return true;
    }
        
    bool meanProjection_3images_1channels() {
        int width = 4;
        int height = 3;
        int channels = 1;
        int num_images = 3;
        Volume testVolume(width, height, channels, num_images);

        unsigned char* testData = new unsigned char[36]{
            // Image 1
            0,0,0,0,
            0,0,0,0,
            0,0,0,0,
            // Image 2
            20,20,20,20,
            20,20,20,20,
            20,20,20,20,
            // Image 3
            190,190,190,190,
            190,190,190,190,
            190,190,190,190,
        };

        testVolume.setData(testData);
        unsigned char* expectedResult0 = new unsigned char[12]{
            70,70,70,70,
            70,70,70,70,
            70,70,70,70,};

        Image result = Projection::meanIntensityProjection(testVolume);

        unsigned char* result0 = result.varDataGetter();
        for (int i = 0; i < 12; i++) {
            //std::cout << static_cast<int>(result0[i]) << '\n';
            if (result0[i] != expectedResult0[i]) return false;
        }
        
        return true;
    }
};

class MedianProjectionTest : public Test {
public:
    MedianProjectionTest() : Test("median projection") {}
    void run() override {
        bool test1images1channels = medianProjection_1image();
        bool test3images3channels = medianProjection_3images_3channels();
        bool test3images1channels = medianProjection_3images_1channels();
        assert_true(test1images1channels, "median projection with 1 image with 1 channel");
        assert_true(test3images3channels, "median projection with 3 images with 3 channels");
        assert_true(test3images1channels, "median projection with 3 images with 1 channel");

    }

    bool medianProjection_1image() {
        int width = 4;
        int height = 3;
        int channels = 1;
        int num_images = 1;
        Volume testVolume(width, height, channels, num_images);

        unsigned char* testData = new unsigned char[12]{
            // image1
            1,3,3,2,
            3,2,2,3,
            2,3,1,1
        };

        testVolume.setData(testData);
        unsigned char* expectedResult0 = new unsigned char[12]{
            1,3,3,2,
            3,2,2,3,
            2,3,1,1
        };

        Image result = Projection::medianIntensityProjection(testVolume);
        unsigned char* result0 = result.varDataGetter();
        for (int i = 0; i < 12; i++) {
            // std::cout << static_cast<int>(result0[i]) << '\n';
            if (result0[i] != expectedResult0[i]) return false;
        }
        
        return true;
    }

    bool medianProjection_3images_3channels() {
        int width = 4;
        int height = 3;
        int channels = 3;
        int num_images = 3;
        Volume testVolume(width, height, channels, num_images);

        unsigned char* testData = new unsigned char[108]{
            // Image 1
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,
            0,0,0,  0,0,0,  0,0,0,  0,0,0,

            // Image 2
            1,1,1,  2,2,2,  3,3,3,  4,4,4,
            1,1,1,  2,2,2,  3,3,3,  4,4,4,
            1,1,1,  2,2,2,  3,3,3,  4,4,4,

            // Image 3
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
            5,5,5,  6,6,6,  7,7,7,  8,8,8,
        };

        testVolume.setData(testData);
        unsigned char* expectedResult0 = new unsigned char[36]{
            1,1,1,  2,2,2,  3,3,3,  4,4,4,
            1,1,1,  2,2,2,  3,3,3,  4,4,4,
            1,1,1,  2,2,2,  3,3,3,  4,4,4,
        };

        Image result = Projection::medianIntensityProjection(testVolume);

        unsigned char* result0 = result.varDataGetter();
        for (int i = 0; i < 36; i++) {
            // std::cout << static_cast<int>(result0[i]) << '\n';
            if (result0[i] != expectedResult0[i]) return false;
        }
        
        return true;
    }

    bool medianProjection_3images_1channels() {
        int width = 4;
        int height = 3;
        int channels = 1;
        int num_images = 3;
        Volume testVolume(width, height, channels, num_images);

        unsigned char* testData = new unsigned char[36]{
            // Image 1
            0,0,0,0,
            0,0,0,0,
            0,0,0,0,

            // Image 2
            1,2,3,4,
            1,2,3,4,
            1,2,3,4,

            // Image 3
            2,3,4,5,
            2,3,4,5,
            2,3,4,5,
        };

        testVolume.setData(testData);
        unsigned char* expectedResult0 = new unsigned char[12]{
            1,2,3,4,
            1,2,3,4,
            1,2,3,4};

        Image result = Projection::medianIntensityProjection(testVolume);

        unsigned char* result0 = result.varDataGetter();
        for (int i = 0; i < 12; i++) {
            // std::cout << static_cast<int>(result0[i]) << '\n';
            if (result0[i] != expectedResult0[i]) return false;
        }
        
        return true;
    }
};

class MedianBlurTest_3D : public Test {
public:
    MedianBlurTest_3D() : Test("3D-MedianBLur") {}
    void run() override {
        std::cout.setstate(std::ios_base::failbit);
        bool white_volume_test = testMedianBlurOnWhiteImage();
        std::cout.clear();
        assert_true(white_volume_test, "white_volume_3Dmedianblur");

        std::cout.setstate(std::ios_base::failbit);
        bool black_volume_test = testMedianBlurOnBlackImage();
        std::cout.clear();
        assert_true(black_volume_test, "black_volume_3Dmedianblur");

        std::cout.setstate(std::ios_base::failbit);
        bool horiz_volume_test = testMedianBlurOnHorizontalEdge();
        std::cout.clear();
        assert_true(horiz_volume_test, "horizontal_edge_3Dmedianblur");

    }

    bool testMedianBlurOnWhiteImage() {
        // Set starting data
        Volume white_volume(3, 3, 1, 3);

        unsigned char* white_data = new unsigned char[27]{255, 255, 255, 255, 255, 255, 255, 255, 255, 
                                                          255, 255, 255, 255, 255, 255, 255, 255, 255, 
                                                          255, 255, 255, 255, 255, 255, 255, 255, 255};
        white_volume.setData(white_data);

        unsigned char expected_data[27] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 
                                           255, 255, 255, 255, 255, 255, 255, 255, 255, 
                                           255, 255, 255, 255, 255, 255, 255, 255, 255};

        Filter::median3D(white_volume, 3);

    
        bool whitemedian = hasSameContents2D(white_volume.varDataGetter(), expected_data, 27);
        return whitemedian;
    }

    bool testMedianBlurOnBlackImage() {
        Volume black_volume(3, 3, 1, 3);

        unsigned char* black_data = new unsigned char[27]{0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                          0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                          0, 0, 0, 0, 0, 0, 0, 0, 0};
        black_volume.setData(black_data);

        unsigned char expected_data[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0, 
                                           0, 0, 0, 0, 0, 0, 0, 0, 0};

        Filter::median3D(black_volume, 3);
        
        bool blackmedian = hasSameContents2D(black_volume.varDataGetter(), expected_data, 18);
        return blackmedian;
    }

    bool testMedianBlurOnHorizontalEdge() {
        Volume horizontal_edge_volume(3,3,1,3);

        unsigned char* horizontal_edge_data = new unsigned char[27]{0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 
                                                                    255, 255, 255, 255, 255, 255, 255, 255, 255};
        horizontal_edge_volume.setData(horizontal_edge_data);

        unsigned char expected_data[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           127, 127, 127, 127, 127, 127, 127, 127, 127};

        Filter::median3D(horizontal_edge_volume, 3);
        
        bool horiz = hasSameContents2D(horizontal_edge_volume.varDataGetter(), expected_data, 27);
        return horiz;
    }
};

class GaussianBlurTest_3D : public Test {
public:
    GaussianBlurTest_3D() : Test("3D-GaussianBLur") {}
    void run() override {
        std::cout.setstate(std::ios_base::failbit);
        bool white_volume_test = testGaussianBlurOnWhiteImage();
        std::cout.clear();
        assert_true(white_volume_test, "white_volume_3Dgaussianblur");

        std::cout.setstate(std::ios_base::failbit);
        bool black_volume_test = testGaussianBlurOnBlackImage();
        std::cout.clear();
        assert_true(black_volume_test, "black_volume_3Dgaussianblur");

        std::cout.setstate(std::ios_base::failbit);
        bool random_volume_test = testGaussianBlurOnRandom();
        std::cout.clear();
        assert_true(random_volume_test, "Random_volume_3D_gaussianblur");

    }

    bool testGaussianBlurOnWhiteImage() {
        // Set starting data
        Volume white_volume(3, 3, 1, 3);

        unsigned char* white_data = new unsigned char[27]{255, 255, 255, 255, 255, 255, 255, 255, 255, 
                                                          255, 255, 255, 255, 255, 255, 255, 255, 255, 
                                                          255, 255, 255, 255, 255, 255, 255, 255, 255};
        white_volume.setData(white_data);

        unsigned char expected_data[27] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 
                                           255, 255, 255, 255, 255, 255, 255, 255, 255, 
                                           255, 255, 255, 255, 255, 255, 255, 255, 255};

        Filter::gaussian3D(white_volume, 5);

    
        bool whitegaussian = hasSameContents2D(white_volume.varDataGetter(), expected_data, 27);
        return whitegaussian;
    }

    bool testGaussianBlurOnBlackImage() {
        Volume black_volume(3, 3, 1, 3);

        unsigned char* black_data = new unsigned char[27]{0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                          0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                          0, 0, 0, 0, 0, 0, 0, 0, 0};
        black_volume.setData(black_data);

        unsigned char expected_data[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0, 
                                           0, 0, 0, 0, 0, 0, 0, 0, 0};

        Filter::gaussian3D(black_volume, 5);
        
        bool blackgaussian = hasSameContents2D(black_volume.varDataGetter(), expected_data, 18);
        return blackgaussian;
    }

    bool testGaussianBlurOnRandom() {
        Volume horizontal_edge_volume(3,3,1,3);

        unsigned char* horizontal_edge_data = new unsigned char[27]{1, 2, 3, 4, 5, 6, 7, 8, 9,
                                                                    9, 8, 7, 6, 5, 4, 3, 2, 1, 
                                                                    1, 2, 3, 4, 5, 6, 7, 8, 9};
        horizontal_edge_volume.setData(horizontal_edge_data);

        unsigned char expected_data[27] = {4, 4, 4, 5, 5, 5, 6, 6, 6,
                                           4, 4, 5, 5, 5, 5, 5, 6, 6,
                                           4, 4, 4, 5, 5, 5, 6, 6, 6,};

        Filter::gaussian3D(horizontal_edge_volume, 5);
        
        bool randomn = hasSameContents2D(horizontal_edge_volume.varDataGetter(), expected_data, 27);
        return randomn;
    }
};


int main() {
    std::cout << "=============================\n";
    std::cout << "           TESTING\n";
    std::cout << "=============================\n";

    TestSuite suiteSorting("Sorting Functions");
    suiteSorting.addTest(new MergeSortTest);
    suiteSorting.addTest(new QuickSelectTest);
    suiteSorting.run();

    TestSuite suite2D("2D-Filters");
    suite2D.addTest(new GreyscaleTest);
    suite2D.addTest(new BrightnessTest);
    suite2D.addTest(new MedianBlurTest);
    suite2D.addTest(new GaussianBlurTest);
    suite2D.addTest(new PrewittTest);
    suite2D.addTest(new SobelTest);
    suite2D.run();
    
    TestSuite suiteVolume("Volume");

    suiteVolume.addTest(new VolumeValueGetterTest);
    suiteVolume.run();

    TestSuite suiteSlicing("Slicing");

    suiteSlicing.addTest(new XZPlaneTest);
    suiteSlicing.addTest(new YZPlaneTest);
    suiteSlicing.run();

    TestSuite suiteProjections("Projections");

    suiteProjections.addTest(new MaxProjectionTest);
    suiteProjections.addTest(new MinProjectionTest);
    suiteProjections.addTest(new MedianProjectionTest);
    suiteProjections.addTest(new MeanProjectionTest);
    suiteProjections.run();

    TestSuite suite3D("3D-Filters");

    suite3D.addTest(new MedianBlurTest_3D);
    suite3D.addTest(new GaussianBlurTest_3D);
    suite3D.run();


    return 0;
}