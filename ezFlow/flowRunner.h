#ifndef OOP_FLOWRUNNER_H
#define OOP_FLOWRUNNER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "steps.h"
#include "analytics.h"

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

    static NumberInputStep runNumberInputStep(std::vector<std::string> &line, const string &run_file, std::vector<NumberInputStep> &number_steps_ptr);

    static float parseCalculusRule(std::vector<NumberInputStep> &number_steps_ptr, const string& operation_ptr);

    static void runCalculusStep(std::vector<std::string> &line, const string &run_file, std::vector<NumberInputStep> &number_steps_ptr);

    static void runTxtFileStep(std::vector<std::string> &line, const string &run_file);

    static void runCSVFileStep(std::vector<std::string> &line, const string &run_file);

    static void runDisplayStep(std::vector<std::string> &line, const string &run_file);


    template<typename T>
    static void writeStep(const T &input, const vector<vector<string>> &run_file, const string &out_file);

    static void runOutputStep(std::vector<std::string> &line, const string &run_file);

    static void runEndStep(std::vector<std::string> &line, const string &run_file);

    static void flowParser(std::vector<std::vector<std::string>> &content, std::vector<vector<string>>& flow_list_content);
};

#endif // OOP_FLOWRUNNER_H