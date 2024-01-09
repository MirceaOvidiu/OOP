#ifndef OOP_FLOWRUNNER_H
#define OOP_FLOWRUNNER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>  // Include necessary header for std::runtime_error

class FlowRunner {
public:
    std::vector<std::string> run_time_errors;

    FlowRunner();

    void addError(const std::string &error);

    static std::vector<std::vector<std::string>> readCSV(const std::string &fname);

    static void displayContent(const std::vector<std::vector<std::string>> &content);

    std::string chooseFlow(const std::vector<std::vector<std::string>>& content);

    static void flowParser(const std::vector<std::vector<std::string>> &content);
};

#endif // OOP_FLOWRUNNER_H