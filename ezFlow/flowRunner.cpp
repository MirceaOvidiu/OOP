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
    TextStep::writeTextStep(textStep, runfile);

    std::cout << "Text step written to run file...\n";
}

void FlowRunner::runTextInputStep(std::vector<std::string> &line, const string &runfile) {
    std::cout << "Running text input step...\n";
    std::cout << "Index: " << line[0] << "\n";
    std::cout << "Description: " << line[2] << "\n";
    std::cout << "Text input: " << line[3] << " _SET AT RUNTIME_"
              << "\n";

    TextInputStep textInputStep = TextInputStep();
    textInputStep.setIndex(std::stoi(line[0]));
    textInputStep.setDescription(line[2]);
    textInputStep.setTextInput(TextInputStep::enterText());///@details set at runtime
    TextInputStep::writeTextInputStep(textInputStep, runfile);

    std::cout << "Text input step written to run file...\n";
}

NumberInputStep FlowRunner::runNumberInputStep(std::vector<std::string> &line, const string &runfile, std::vector<NumberInputStep> &number_steps_ptr) {
    std::cout << "Running number input step...\n";
    std::cout << "Index: " << line[0] << "\n";
    std::cout << "Description: " << line[2] << "\n";

    NumberInputStep numberInputStep = NumberInputStep();
    numberInputStep.setIndex(std::stoi(line[0]));
    numberInputStep.setDescription(line[2]);

    float number_step_value = NumberInputStep::enterNumberStepInput();///@details set at runtime
    numberInputStep.setNumberInput(number_step_value);

    std::cout << "Numeric value: " << numberInputStep.getNumberInput() << "_SET AT RUNTIME_"
              << "\n";

    NumberInputStep::writeNumberInputStep(numberInputStep, runfile);

    std::cout << "Number input step written to run file...\n";

    return numberInputStep;
}

float FlowRunner::parseCalculusRule(std::vector<NumberInputStep> &number_steps_ptr, const std::string &rule) {
    float result = number_steps_ptr[0].getNumberInput();
    std::vector<std::string> operations;
    std::vector<float> number_inputs;

    for (auto &nr_input_step: number_steps_ptr) {
        float temp_value = nr_input_step.getNumberInput();
        number_inputs.push_back(temp_value);
        std::cout << "Number step " << nr_input_step.getIndex() << " value: " << temp_value << "\n";
    }

    /// extract operations
    for (auto &word: rule) {
        if (word == '+' || word == '-' || word == '*' || word == '/' || word == 'm' || word == 'M') {
            std::cout << "Operation: " << word << "\n";
            operations.emplace_back(1, word);
        }
    }

    /// parse operations
    for (int i = 0; i < operations.size(); i++) {
        if (operations[i] == "+") {
            result += number_inputs[i + 1];
        }
        if (operations[i] == "-") {
            result -= number_inputs[i + 1];
        }
        if (operations[i] == "*") {
            result *= number_inputs[i + 1];
        }
        if (operations[i] == "/") {
            result /= number_inputs[i + 1];
        }
        if (operations[i] == "m") {
            result = CalculusStep::returnMin(number_steps_ptr);
        }
        if (operations[i] == "M") {
            result = CalculusStep::returnMax(number_steps_ptr);
        }
    }

    return result;
}

void FlowRunner::runCalculusStep(std::vector<std::string> &line, const string &runfile, std::vector<NumberInputStep> &number_steps_ptr) {
    float result;
    std::string rule = line[2];
    std::cout << "Running calculus step...\n";
    std::cout << "Index: " << line[0] << "\n";
    std::cout << "Rule: " << rule << "\n";

    CalculusStep calculusStep = CalculusStep();
    CalculusStep::setIndex(calculusStep, std::stoi(line[0]));
    calculusStep.setOperation(line[2]);
    /// calculus rule parser
    result = parseCalculusRule(number_steps_ptr, rule);
    CalculusStep::setNumberOutput(calculusStep, result);
    CalculusStep::writeCalculusStepComponents(calculusStep, rule, runfile);

    std::cout << "Calculus step written to run file with final value: " << calculusStep.getNumberOutput() << "...\n";
}

void FlowRunner::runTxtFileStep(std::vector<std::string> &line, const string &run_file) {
    std::cout << "Running file step...\n";
    std::cout << "Index: " << line[0] << "\n";
    std::cout << "Description: " << line[2] << "\n";

    TextFileStep textFileStep = TextFileStep();
    textFileStep.setIndex(std::stoi(line[0]));
    textFileStep.setDescription(line[2]);
    textFileStep.setFilename(TextFileStep::enterFilename());///@details set at runtime
    cout << "Filename: " << textFileStep.getFilename() << "\n";
    TextFileStep::writeFileStep(textFileStep, run_file);

    std::cout << "Txt file step written to run file...\n";
}

void FlowRunner::runCSVFileStep(std::vector<std::string> &line, const string &run_file) {
    std::cout << "Running file step...\n";
    std::cout << "Index: " << line[0] << "\n";
    std::cout << "Description: " << line[2] << "\n";

    CSVFileStep csvFileStep = CSVFileStep();
    csvFileStep.setIndex(std::stoi(line[0]));
    csvFileStep.setDescription(line[2]);
    csvFileStep.setFilename(CSVFileStep::enterFilename());///@details set at runtime
    cout << "Filename: " << csvFileStep.getFilename() << "\n";
    CSVFileStep::writeFileStep(csvFileStep, run_file);

    std::cout << "CSV file step written to run file...\n";
}

void FlowRunner::runDisplayStep(std::vector<std::string> &line, const std::string &run_file) {
    std::cout << "Running display step...\n";
    std::cout << "Index: " << line[0] << "\n";
    std::cout << "Filename to display:  " << line[2] << "\n";

    DisplayStep displayStep = DisplayStep();
    displayStep.setIndex(std::stoi(line[0]));
    displayStep.file_to_display = line[2];
    FlowRunner::displayContent(FlowRunner::readCSV(line[2]));
    DisplayStep::writeDisplayStep(displayStep, run_file);
    std::cout << "Display step written to run file...\n";
}

template<typename T>
void FlowRunner::writeStep(const T &input, const vector<vector<string>> &run_file, const string &out_file) {
    std::cerr << "Wrong selection input";
}

template<>
void FlowRunner::writeStep(const string &input, const vector<vector<string>> &run_file, const string &out_file) {
    std::ofstream outfile;
    outfile.open(out_file, std::ios::app);

    for (auto &line: run_file) {
        if (line[1] == input) {
            outfile << line[0] << "," << line[1] << "," << line[2] << "," << line[3] << "\n";
        }
    }

    outfile.close();
}

template<>
void FlowRunner::writeStep(const int &input, const vector<vector<string>> &run_file, const string &out_file) {
    std::ofstream outfile;
    outfile.open(out_file, std::ios::app);

    for (auto &line: run_file) {
        if (line[0] == std::to_string(input)) {
            outfile << line[0] << "," << line[1] << "," << line[2] << "," << line[3] << "\n";
        }
    }

    outfile.close();
}

void FlowRunner::runOutputStep(std::vector<std::string> &line, const std::string &run_file) {
    std::vector<std::vector<std::string>> run_file_content;
    string flow_title;
    string out_file_name;
    string out_file_full_path;
    run_file_content = FlowRunner::readCSV(run_file);

    for (const auto &i: run_file_content) {
        if (i[1] == "TITLE") {
            flow_title = i[2];
        }
    }

    std::cout << "Running output step...\n";
    std::cout << "Index: " << line[0] << "\n";

    std::cout << "Enter outfile name (.csv) "
              << "\n";
    out_file_name = CSVFileStep::enterFilename();

    out_file_full_path = "./FlowOutfiles/" + flow_title + "_" + out_file_name;

    ofstream outfile;
    outfile.open(out_file_full_path, std::ios::app);

    cout << "Select by: index or type?\n";

    string selection;
    cin >> selection;

    if (selection == "index") {
        std::cout << " ! Type 112 to exit !\n";
        for (int i = 0; i < run_file_content.size(); i++) {
            int index;
            cout << "Enter index: \n";
            cin >> index;

            if (index == 112) {
                break;
            } else {
                writeStep(index, run_file_content, out_file_full_path);
            }
        }
    }

    if (selection == "type") {
        std::cout << " ! Type 112 to exit !\n";
        for (int i = 0; i < run_file_content.size(); i++) {
            string type;
            cout << "Enter type: \n";
            cin >> type;

            if (type == "112") {
                break;
            } else {
                writeStep(type, run_file_content, out_file_full_path);
            }
        }
    }

    OutputStep outputStep = OutputStep();
    outputStep.setIndex(std::stoi(line[0]));
    outputStep.setOutFile(out_file_full_path);
    OutputStep::writeOutputStep(outputStep, run_file);
}

void FlowRunner::runEndStep(std::vector<std::string> &line, const std::string &run_file) {
    std::cout << "Running end step...\n";
    std::cout << "Index: " << line[0] << "\n";
    std::cout << "Time created: " << Utils::getTimeStamp() << "\n";

    EndStep endStep = EndStep();
    endStep.setIndex(std::stoi(line[0]));
    endStep.setTimeCreated(Utils::getTimeStamp());
    EndStep::writeEndStep(endStep, run_file);

    std::cout << "End step written to run file...\n";
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
                numberInputSteps.push_back(runNumberInputStep(line, runfile, numberInputSteps));
            }

            if (word == "CALCULUS") {
                if (numberInputSteps.empty()) {
                    string message = " non - fatal: No number input steps found\n";
                    std::cerr << message;
                    break;
                }
                runCalculusStep(line, runfile, numberInputSteps);
            }

            if (word == "TEXT FILE") {
                runTxtFileStep(line, runfile);
            }

            if (word == "CSV FILE") {
                runCSVFileStep(line, runfile);
            }

            if (word == "DISPLAY") {
                runDisplayStep(line, runfile);
            }

            if (word == "OUTPUT") {
                runOutputStep(line, runfile);
            }

            if (word == "END") {
                std::cout << "End of flow reached...\n";
                FlowRunner::runEndStep(line, runfile);
                break;
            }
        }
        std::cout << "\n";
    }
}
