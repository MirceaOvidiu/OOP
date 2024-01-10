#ifndef OOP_FLOWRUNNER_H
#define OOP_FLOWRUNNER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace std;

class FlowRunner {
public:
    std::vector<std::string> run_time_errors;

    FlowRunner();

    ///@brief Flow runner utilities
    void addError(const std::string &error);

    static std::vector<std::vector<std::string>> readCSV(const std::string &fname);

    static void displayContent(const std::vector<std::vector<std::string>> &content);

    static string getFlowTitle(const std::vector<std::vector<std::string>> &content);

    static std::string chooseFlow(const std::vector<std::vector<std::string>>& content);

    static string createRunFile(const std::string &flowName);

    ///@brief Functions to be called by the Parser
    static void runTitleStep(std::vector<std::string> &line, const string &run_file);

    static void runTextStep(std::vector<std::string> &line, const string &run_file);

    static void runTextInputStep(std::vector<std::string> &line, const string &run_file);

    ///@brief The actual parser
    static void flowParser(std::vector<std::vector<std::string>> &content);
};

#endif // OOP_FLOWRUNNER_H