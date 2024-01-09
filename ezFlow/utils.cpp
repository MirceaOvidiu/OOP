//
// Created by Mircea on 1/9/2024.
//

// Utils.cpp

#include "Utils.h"

using namespace std;

bool Utils::titleValidity(const std::string &title) {
    // Regex pattern: allows letters, whitespace, and numbers
    std::regex pattern("^[a-zA-Z0-9\\s]+$");
    // True if title matches the pattern
    return std::regex_match(title, pattern);
}

bool Utils::textValidity(const std::string &text) {
    // Regex pattern: allows letters, whitespace, numbers, punctuation, and symbols
    std::regex pattern(R"(^[a-zA-Z0-9\s\p{P}\p{S}]+$)");
    // True if text matches the pattern
    return std::regex_match(text, pattern);
}

bool Utils::isTxtFile(const std::string &filename) {
    // Regex pattern: allows letters, numbers, and underscores
    std::regex pattern("[a-zA-Z0-9_]+\\.txt");
    // True if text matches the pattern
    return std::regex_match(filename, pattern);
}

bool Utils::isCsvFile(const std::string &filename) {
    // Regex pattern: allows letters, numbers, and underscores
    std::regex pattern("[a-zA-Z0-9_]+\\.csv");
    // True if text matches the pattern
    return std::regex_match(filename, pattern);
}

bool Utils::operationValidity(const std::string &operation) {
    if (operation == "+" || operation == "-" || operation == "*" || operation == "/" ||
        operation == "MIN" || operation == "MAX") {
        return true;
    } else {
        return false;
    }
}

std::string Utils::getTimeStamp() {
    // Get the current time point
    auto now = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert time_t to a string
    std::string timeString = std::ctime(&currentTime);
    timeString.pop_back();

    return timeString;
}

void FlowUtils::listSteps() {
    cout << "1.TITLE        - title and subtitle of the flow.\n"
         << "2.TEXT         - text to be displayed and a copy.\n"
         << "3.TEXT INPUT   - description and actual text.\n"
         << "4.NUMBER INPUT - description and float value.\n"
         << "5.CALCULUS     -  involved NumberSteps and numeric result.\n"
         << "6.TEXT FILE    - description of the file and file path.\n"
         << "7.CSV FILE     - description of the file and file path.\n"
         << "8.DISPLAY      - display the contents of a .csv/.txt file.\n"
         << "9.OUTPUT       - description, steps written, and outfile name.\n"
         << "10.EXIT        - time created, signals flow end.\n";
}

int FlowUtils::chooseStep() {
    int choice;
    cout << "Choose a step: \n";
    cin >> choice;
    return choice;
}

void FlowUtils::printOperations() {
    cout << " + : Addition\n";
    cout << " - : Subtraction\n";
    cout << " * : Multiplication\n";
    cout << " / : Division\n";
    cout << " MIN : Minimum\n";
    cout << " MAX : Maximum\n";
}

