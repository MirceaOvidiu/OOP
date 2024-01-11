//
// Created by Mircea on 1/9/2024.
//

// FlowRunner.cpp

#include "flowRunner.h"
#include "steps.h"

using namespace std;

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
    for (const auto &i: content) {
        for (const auto &j: i) {
            std::cout << j << " | ";
        }
        std::cout << "\n";
    }
}

string FlowRunner::getFlowTitle(const std::vector<std::vector<std::string>> &content) {
    std::string title;
    for (const auto &i: content) {
        if (i[1] == "TITLE") {
            title = i[2];
            return title;
        }
    }
    return "Title not found";
}

std::string FlowRunner::chooseFlow(const std::vector<std::vector<std::string>> &content) {
    std::string choice;
    std::cout << "\nEnter a flow to run:\n";
    std::cin >> choice;

    try {
        for (const auto &i: content) {
            if (i[0] == choice) {
                std::cout << choice << " found\n";
                return choice;
            }
        }
    } catch (std::exception &e) {
        std::cout << "Flow not found\n";
    }

    return "Flow not found";
}

string FlowRunner::createRunFile(const std::string &flowName) {
    std::ofstream runFile;
    string runfile = "./FlowRunFiles/" + flowName + "RunFile.csv";
    runFile.open(runfile, std::ios::out);
    runFile.close();
    return runfile;
}

///@details overloading on implementation the writeTitleStep function in order to create a run file
string TitleStep::writeTitleStep(const TitleStep &titleStep, const string &run_file) {
    std::ofstream runFile;
    runFile.open(run_file, std::ios::app);
    runFile << "INDEX, TYPE, ARG1, ARG2\n";
    runFile << titleStep.getIndex() << "," << titleStep.type << "," << titleStep.getTitle() << ","
            << titleStep.getSubtitle() << "\n";
    runFile.close();
    return run_file;
}

void FlowRunner::runTitleStep(std::vector<std::string> &line, const string &run_file) {
    std::cout << "Running title step...\n";
    std::cout << "Index: " << line[0] << "\n";
    std::cout << "Title: " << line[2] << "\n";
    std::cout << "Subtitle: " << line[3] << "\n";

    TitleStep titleStep = TitleStep();
    titleStep.setIndex(std::stoi(line[0]));
    titleStep.setTitle(line[2]);
    titleStep.setSubtitle(line[3]);
    TitleStep::writeTitleStep(titleStep, run_file);

    std::cout << "Title step written to run file...\n";

    ///@details this function can be made static, after the titleStep object is created,
    ///its' contents are written to the run file and is no longer needed

    ///The titleStep object is out of scope now and will be destroyed
}

void FlowRunner::runTextStep(std::vector<std::string> &line, const string &runfile) {
    std::cout << "Running text step...\n";
    std::cout << "Index: " << line[0] << "\n";
    std::cout << "Text: " << line[2] << "\n";
    std::cout << "Copy: " << line[3] << "\n";

    TextStep textStep = TextStep();
    textStep.setIndex(std::stoi(line[0]));
    textStep.setText(line[2]);
    textStep.setCopy();/// @details has no arguments by design, field is copied from the text field
    TextStep::writeTextStep(textStep,runfile);

    std::cout << "Text step written to run file...\n";
}

void FlowRunner::runTextInputStep(std::vector<std::string> &line, const string &runfile) {
    std::cout << "Running text input step...\n";
    std::cout << "Index: " << line[0] << "\n";
    std::cout << "Description: " << line[2] << "\n";
    std::cout << "Text input: " << line[3] << " _SET AT RUNTIME_" << "\n";

    TextInputStep textInputStep = TextInputStep();
    textInputStep.setIndex(std::stoi(line[0]));
    textInputStep.setDescription(line[2]);
    textInputStep.setTextInput(TextInputStep::enterText()); ///@details set at runtime
    TextInputStep::writeTextInputStep(textInputStep,runfile);

    std::cout << "Text input step written to run file...\n";
}

void FlowRunner::runNumberInputStep(std::vector<std::string> &line, const string &runfile, std::vector<NumberInputStep> &number_steps_ptr) {
    std::cout << "Running number input step...\n";
    std::cout << "Index: " << line[0] << "\n";
    std::cout << "Description: " << line[2] << "\n";
    std::cout << "Number input: " << line[3] << " _SET AT RUNTIME_" << "\n";

    NumberInputStep numberInputStep = NumberInputStep();
    numberInputStep.setIndex(std::stoi(line[0]));
    numberInputStep.setDescription(line[2]);

    float number_step_value = NumberInputStep::enterNumberStepInput();
    number_steps_ptr.emplace_back(numberInputStep);
    numberInputStep.setNumberInput(number_step_value); ///@details set at runtime
    NumberInputStep::writeNumberInputStep(numberInputStep,runfile);

    std::cout << "Number input step written to run file...\n";
}


/// @TODO: parameters are all empty - fix
float FlowRunner::parseCalculusRule(std::vector<NumberInputStep> &number_steps_ptr, std::vector<string> operation_ptr) {
    float result = number_steps_ptr[0].getNumberInput();

    std::cout << "Operations: \n";

    /// PARAMETERS ARE ALL EMPTY
    for(auto &nr_input_step:number_steps_ptr) {
        std::cout << "Number input step: " << nr_input_step.getNumberInput() << "\n";
    }

    for(auto &operation: operation_ptr) {
        std::cout << "Rule made of operations:" << operation << " ";
    }
    cout << "\n";

    return result;
}

void FlowRunner::runCalculusStep(std::vector<std::string> &line, const string &runfile, std::vector<NumberInputStep> &number_steps_ptr) {
    float result;
    std::cout << "Running calculus step...\n";
    std::cout << "Index: " << line[0] << "\n";
    std::cout << "Rule: " << line[2] << "\n";
    std::cout << "Result: " << line[3] << " _COMPUTED AT RUNTIME_" << "\n";

    CalculusStep calculusStep = CalculusStep();
    CalculusStep::setIndex(calculusStep, std::stoi(line[0]));
    calculusStep.setOperation(line[2]);

    /// calculus rule parser
    result = parseCalculusRule(number_steps_ptr, calculusStep.getOperations());

    CalculusStep::writeCalculusStep(calculusStep,runfile);

    std::cout << "Calculus step written to run file with final value: " << result << "...\n";
}

void FlowRunner::flowParser(std::vector<std::vector<std::string>> &content) {
    std::cout << "Parsing flow config file...\n";
    std::string runfile = "./FlowRunFiles/" + getFlowTitle(content) + "RunFile.csv";
    std::vector<NumberInputStep> numberInputSteps;

    for (auto &line: content) {
        for (string &word: line) {
            if (word == "TITLE") {
                runTitleStep(line, runfile);
            }

            if (word == "TEXT") {
                runTextStep(line, runfile);
            }

            if (word == "TEXT INPUT") {
                runTextInputStep(line, runfile);
            }

            if (word == "NUMBER INPUT") {
                runNumberInputStep(line, runfile, numberInputSteps);
            }

            if (word == "CALCULUS") {
                runCalculusStep(line, runfile, numberInputSteps);
            }
        }
        std::cout << "\n";
    }
}
