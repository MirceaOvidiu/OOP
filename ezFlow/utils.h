//
// Created by Mircea on 12/28/2023.
//

#ifndef OOP_UTILS_H
#define OOP_UTILS_H

#include <iostream>
#include <regex>
#include <string>
#include "steps.h"
#include "UX.h"
#include "utils.h"

using namespace std;

class Utils
{
public:
    static bool titleValidity(const string &title)
    {
        // Regex pattern: allows letters, whitespace, and numbers
        std::regex pattern("^[a-zA-Z0-9\\s]+$");
        // True if title matches the pattern
        return std::regex_match(title, pattern);
    }

    static bool textValidity(const string &text)
    {
        // Regex pattern: allows letters, whitespace, numbers, punctuation and symbols
        std::regex pattern(R"(^[a-zA-Z0-9\s\p{P}\p{S}]+$)");
        // True if text matches the pattern
        return std::regex_match(text, pattern);
    }

    static bool isTxtFile(const string &filename)
    {
        // Regex pattern: allows letters, numbers and underscores
        std::regex pattern("[a-zA-Z0-9_]+\\.txt");
        // True if text matches the pattern
        return std::regex_match(filename, pattern);
    }

    static bool isCsvFile(const string &filename)
    {
        // Regex pattern: allows letters, numbers and underscores
        std::regex pattern("[a-zA-Z0-9_]+\\.csv");
        // True if text matches the pattern
        return std::regex_match(filename, pattern);
    }

    static bool operationValidity(const string &operation)
    {
        if(operation == "+" || operation == "-" || operation == "*" || operation == "/" ||
           operation == "MIN" || operation == "MAX")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class FlowUtils
{
public:
    static void listSteps()
    {
        cout << "1.TITLE 2.TEXT 3.TEXT INPUT 4.NUMBER INPUT 5.CALCULUS 6.TEXT FILE 7.CSV FILE 8.DISPLAY 9.OUTPUT 10.END\n";
    }

    static int chooseStep()
    {
        int choice;
        cout << "Choose a step out of: \n";
        listSteps();
        cin >> choice;
        return choice;
    }

    static void printOperations(){
        cout << " + : Addition\n";
        cout << " - : Subtraction\n";
        cout << " * : Multiplication\n";
        cout << " / : Division\n";
        cout << " MIN : Minimum\n";
        cout << " MAX : Maximum\n";
    }
};

#endif // OOP_UTILS_H
