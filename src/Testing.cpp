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
#include "Testing.h"

/**
 * Test
*/
Test::Test(const std::string& name) : name(name) {}

TestSuite::~TestSuite(){
    this->tests.clear();
}

const std::string& Test::getName() const {
    return this->name;
}

void Test::assert_true(bool condition, const std::string& name) {
    if (condition) {
        std::cout << "\u2705 '" << name << "' passed!\n";

    } else {
        std::cout << "\u274C '" << name << "' failed!\n";

    }
}

void Test::assert_false(bool condition, const std::string& name) {
    if (!condition) {
        std::cout << "\u2705 '" << name << "' passed!\n";

    } else {
        std::cout << "\u274C '" << name << "' failed!\n";

    }
}


/**
 * TestSuite
*/
TestSuite::TestSuite(const std::string& name) : name(name) {}

const std::string& TestSuite::getName() const {
    return this->name;
}

void TestSuite::addTest(Test* test) {
    this->tests.push_back(test);
}

void TestSuite::run() {
    std::cout << "\n\nTesting: " << this->getName() << "\n";

    for (auto test : this->tests) {
        std::cout << "\n\U0001F9EA Running Test for: " << test->getName() << "\n";
        test->run();
    }
}