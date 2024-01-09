// Utils.h

#ifndef OOP_UTILS_H
#define OOP_UTILS_H

#include <chrono>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

class Utils {
public:
    static bool titleValidity(const std::string &title);

    static bool textValidity(const std::string &text);

    static bool isTxtFile(const std::string &filename);

    static bool isCsvFile(const std::string &filename);

    static bool operationValidity(const std::string &operation);

    static std::string getTimeStamp();
};

class FlowUtils {
public:
    static void listSteps();

    static int chooseStep();

    static void printOperations();
};

#endif // OOP_UTILS_H
