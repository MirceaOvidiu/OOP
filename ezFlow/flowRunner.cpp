//
// Created by Mircea on 1/9/2024.
//

// FlowRunner.cpp

#include "flowRunner.h"

FlowRunner::FlowRunner() {
    std::cout << "Flow runner started...\n";
}

void FlowRunner::addError(const std::string &error) {
    run_time_errors.emplace_back(error);
}

std::vector<std::vector<std::string>> FlowRunner::readCSV(const std::string &fname) {
    std::vector<std::vector<std::string>> content;
    std::vector<std::string> row;
    std::string line, word;

    std::fstream file(fname, std::ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            row.clear();

            std::stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    } else {
        std::cout << "Could not open the file\n";
    }

    return content;
}

void FlowRunner::displayContent(const std::vector<std::vector<std::string>> &content) {
    for (const auto &i : content) {
        for (const auto &j : i) {
            std::cout << j << " | ";
        }
        std::cout << "\n";
    }
}

std::string FlowRunner::chooseFlow(const std::vector<std::vector<std::string>> &content) {
    try {
        std::string choice;
        std::cout << "Enter a flow to run:\n";
        std::cin >> choice;

        for (const auto &i : content) {
            if (!i.empty() && i[0] == choice) {
                return choice;
            }
        }
        // If the loop completes without returning, the choice was not found
        throw std::runtime_error("Flow not found: " + choice);
    } catch (const std::exception &e) {
        addError(e.what());
        std::cerr << "Exception: " << e.what() << '\n';
        return "unselected";
    }
}

void FlowRunner::flowParser(const std::vector<std::vector<std::string>> &content) {
    for (const auto &i : content) {
        for (const auto &j : i) {
            std::cout << j << " | ";
        }
        std::cout << "\n";
    }
}

