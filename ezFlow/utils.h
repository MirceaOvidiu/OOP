// Utils.h

#ifndef OOP_UTILS_H
#define OOP_UTILS_H

#include <chrono>
#include <iostream>
#include <regex>
#include <string>
#include <type_traits>

using namespace std;

class Utils {
public:
    static bool titleValidity(const std::string &title);

    static bool textValidity(const std::string &text);

    static bool isTxtFile(const std::string &filename);

    static bool isCsvFile(const std::string &filename);

    static bool operationValidity(const std::string &operation);

    static std::string getTimeStamp();

    /// No sense to write it in a separate .cpp
    template<typename T>
    static bool isInt(const T& value) {
        return std::is_same<T, int>::value;
    }

};

class FlowUtils {
public:
    static void listSteps();

    static void listStepDetails();

    static int chooseStep();

    static void printOperations();
};

#endif // OOP_UTILS_H
