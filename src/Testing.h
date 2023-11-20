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
#include <string>
#include <vector>

/**
 * @brief This abstract class represents one single Unit Test.
 */
class Test {
public:

    /**
     * @brief Creates an instance of a test.
     * @param name The name of the test.
     */
    Test(const std::string& name);

    /**
     * @brief Runs the test. This method is pure virtual. This
     * is why this class is abstract.
     */
    virtual void run() = 0;

    /**
     * @brief Returns the name of the test.
     * @return The name of the test.
     */
    const std::string& getName() const;

    /**
     * @brief Checks if the condition is true.
     * @param condition The conditions that should be checked.
     * @param name name of the test.
     */
    void assert_true(bool condition, const std::string& name);

    /**
     * @brief Checks if the condition is false.
     * @param condition The conditions that should be checked.
     * @param name name of the test.
     */
    void assert_false(bool condition, const std::string& name);

private:
    std::string name;
};


/**
 * @brief This class represents one Test Suite. It can contain multiple Tests.
 */
class TestSuite {
public:

    /**
     * @brief Creates an instance of a test suite.
     * @param name The name of the test suite.
     */
    TestSuite(const std::string& name);

    ~TestSuite();

     /**
     * @brief Returns the name of the test suite.
     * @return The name of the test suite.
     */
    const std::string& getName() const;

     /**
     * @brief Add a test to the test suite.
     * @param test The test that should be added to the Suite.
     */
    void addTest(Test* test);

     /**
     * @brief Runs all the tests in the test suite.
     */
    void run();

private:
    std::string name;
    std::vector<Test*> tests;
};