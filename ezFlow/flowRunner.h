//
// Created by Mircea on 1/9/2024.
//

#ifndef OOP_FLOWRUNNER_H
#define OOP_FLOWRUNNER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class FlowRunner {
public:
    std::vector<string> run_time_errors;

    FlowRunner() {
        cout << "Flow runner started...\n";
    }

    void addError(const string &error) {
        run_time_errors.emplace_back(error);
    }

    static vector<vector<string>> readCSV(const string &fname) {
        vector<vector<string>> content;
        vector<string> row;
        string line, word;

        fstream file(fname, ios::in);
        if (file.is_open()) {
            while (getline(file, line)) {
                row.clear();

                stringstream str(line);

                while (getline(str, word, ','))
                    row.push_back(word);
                content.push_back(row);
            }
        } else {
            cout << "Could not open the file\n";
        }

        return content;
    }

    static void displayContent(const vector<vector<string>> &content) {
        for (auto &i: content) {
            for (const auto &j: i) {
                cout << j << " | ";
            }
            cout << "\n";
        }
    }

    std::string chooseFlow(const std::vector<std::vector<std::string>>& content) {
        try {
            fflush(stdin);
            std::string choice;
            std::cout << "Enter a flow to run:\n";
            std::cin >> choice;

            for (const auto& i : content) {
                if (!i.empty() && i[0] == choice) {
                    return choice;
                }
            }
            // If the loop completes without returning, the choice was not found
            throw std::runtime_error("Flow not found: " + choice);
        } catch (const std::exception& e) {
            addError(e.what());
            std::cerr << "Exception: " << e.what() << '\n';
            return "";
        }
    }

    static void flowParser(const vector<vector<string>> &content) {
        for (auto &i: content) {
            for (const auto &j: i) {
                cout << j << " | ";
            }
            cout << "\n";
        }
    }
};

#endif//OOP_FLOWRUNNER_H
