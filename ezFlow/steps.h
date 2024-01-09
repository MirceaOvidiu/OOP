#ifndef ezFlow_STEPS_H
#define ezFlow_STEPS_H

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include "utils.h"

using namespace std;

/// In the step creation process, the user will be constrained to provide correct input
/// Therefore, the while(true) loops will be used instead of try catch blocks.

/// Lots of boilerplate code will still remain at this level, for the sake of
/// readability and function/variable name consistency at flow creation level.

/// @brief TitleStep
/// @param title: configured at flow creation
/// @param subtitle: configured at flow creation
class TitleStep {
public:
    string type = "TITLE";
    int index = 0; /// will remain
    string title;
    string subtitle;

    TitleStep() {
        this->title = "default";
        this->subtitle = "default";
    }

    void setTitle(string new_title) {
        this->title = std::move(new_title);
    }

    void setSubtitle(string new_subtitle) {
        this->subtitle = std::move(new_subtitle);
    }

    void setIndex(int new_index) {
        this->index = new_index;
    }

    [[nodiscard]] string getTitle() const {
        return this->title;
    }

    [[nodiscard]] string getSubtitle() const {
        return this->subtitle;
    }

    [[nodiscard]] int getIndex() const {
        return this->index;
    }

    static string enterTitle() {
        fflush(stdin);
        string temp_title;

        while (true) {
            cout << "Enter title: ";
            getline(cin, temp_title);

            if (Utils::titleValidity(temp_title)) {
                return temp_title;
            } else {
                cout << "Invalid title. Try again.\n";
            }
        }
    }

    static string enterSubtitle() {
        fflush(stdin);
        string temp_subtitle;

        while (true) {
            cout << "Enter subtitle: ";
            getline(cin, temp_subtitle);

            if (Utils::titleValidity(temp_subtitle)) {
                return temp_subtitle;
            } else {
                cout << "Invalid subtitle. Try again.\n";
            }
        }
    }

    static void setupTitleStep(TitleStep &newTitle) {
        std::cout << "Setting up step " << newTitle.getIndex() << ": TITLE...\n";
        newTitle.setTitle(enterTitle());
        newTitle.setSubtitle(enterSubtitle());
    }

    static void writeTitleStep(const TitleStep &titleStep) {
        ofstream file;
        /// @brief The flow file is created in the FlowConfigFiles folder
        ///        to preserve tidiness and our sanity
        string filename = "./FlowConfigFiles/" + titleStep.getTitle() + "FlowConfig.csv";
        file.open(filename, ios::app);
        file << "INDEX, TYPE, ARG1, ARG2\n";
        file << titleStep.index << "," << titleStep.type << "," << titleStep.getTitle() << ","
             << titleStep.getSubtitle() << "\n";
        file.close();
    }
};

/// There are a lot of classes with 2 strings and a type string
/// So, to avoid even more boilerplate code, we can inherit from TitleStep

/// @brief Fields: title, subtitle
/// @param: title - configured at flow creation
/// @param: subtitle - configured at flow creation
class TextStep : TitleStep {
public:
    int index = 0;
    string type = "TEXT";

    TextStep() {
        this->title = "default";
        this->subtitle = "default";
    }

    void setText(string new_text) {
        this->title = std::move(new_text);
    }

    void setCopy() {
        this->subtitle = this->title;
    }


    [[nodiscard]] string getText() const {
        return this->title;
    }

    [[nodiscard]] string getCopy() const {
        return this->subtitle;
    }

    static string enterText() {
        fflush(stdin); /// to avoid extra "invalid input"
        string temp_text = "unset";

        while (true) {
            cout << "Enter text: ";
            getline(cin, temp_text);

            if (Utils::textValidity(temp_text)) {
                return temp_text;
            } else {
                cout << "Invalid text. Try again.\n";
            }
        }
    }

    static void setupTextStep(TextStep &newText) {
        std::cout << "Setting up a TEXT step...\n";
        string new_text = enterText();
        newText.setText(new_text);
        newText.setCopy();
    }

    static void writeTextStep(const TextStep &textStep, const string &filename) {
        ofstream file;
        file.open(filename, ios::app);
        file << textStep.index << "," << textStep.type << "," << textStep.getText() << "," << textStep.getCopy()
             << "\n";
        file.close();
    }
};

/// @brief Fields: description, text input
/// @param: description - configured at flow creation
/// @param: text input - configured at runtime
class TextInputStep : TitleStep {
public:
    int index = 0;
    string type = "TEXT INPUT";

    TextInputStep() {
        this->title = "default";
        this->subtitle = "default";
    }

    void setDescription(string new_description) {
        this->title = std::move(new_description);
    }

    void setTextInput(string new_text_input) {
        this->subtitle = std::move(new_text_input);
    }

    [[nodiscard]] string getDescription() const {
        return this->title;
    }

    [[nodiscard]] string getTextInput() const {
        return this->subtitle;
    }

    static string enterDescription() {
        fflush(stdin);
        string temp_description;

        while (true) {
            cout << "Enter description: ";
            cin >> temp_description;

            if (Utils::textValidity(temp_description)) {
                return temp_description;
            } else {
                cout << "Invalid description. Try again.\n";
            }
        }
    }

    static string enterText() {
        string temp_text_input = "unset";

        while (true) {
            cout << "Enter text input: ";
            getline(cin, temp_text_input);

            if (Utils::textValidity(temp_text_input)) {
                return temp_text_input;
            } else {
                cout << "Invalid text input. Try again.\n";
            }
        }
    }

    static void setupTextInputStep(TextInputStep &newTextInput) {
        std::cout << "Setting up a TEXT INPUT step...\n";
        newTextInput.setDescription(enterDescription());
    }

    static void writeTextInputStep(TextInputStep &newTextInput, const string &filename) {
        ofstream file;
        file.open(filename, ios::app);
        file << newTextInput.index << "," << newTextInput.type << "," << newTextInput.title << ","
             << newTextInput.subtitle << "\n";
        file.close();
    }
};

/// @brief Fields: description, number input
/// @param description: configured at flow creation
/// @param number input: configured at runtime
class NumberInputStep {
public:
    string type = "NUMBER INPUT";
    int index = 0;
    float number_input = 0;
    string description;

    NumberInputStep() {
        this->description = "default";
    }

    void setNumberInput(float new_number_input) {
        this->number_input = new_number_input;
    }

    void setDescription(string new_description) {
        this->description = std::move(new_description);
    }

    [[nodiscard]] float getNumberInput() const {
        return this->number_input;
    }

    [[nodiscard]] string getDescription() const {
        return this->description;
    }

    static string enterDescription() {
        fflush(stdin);
        string temp_description;

        while (true) {
            cout << "Enter description: ";
            getline(cin, temp_description);

            if (Utils::textValidity(temp_description)) {
                return temp_description;
            } else {
                cout << "Invalid description. Try again.\n";
            }
        }
    }

    static float enterNumberStepInput() {
        fflush(stdin);
        float temp_number_input;

        while (true) {
            cout << "Enter number input: ";
            cin >> temp_number_input;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid number input. Try again.\n";
            } else {
                return temp_number_input;
            }
        }
    }

    static void setupNumberInputStep(NumberInputStep &newNumberInput) {
        std::cout << "Setting up a NUMBER INPUT step..."
                  << "\n";
        newNumberInput.setDescription(enterDescription());
        /// newNumberInput.setNumberInput(enterNumberStepInput()); - at runtime
    }

    static void writeNumberInputStep(NumberInputStep &newNumberInput, const string &filename) {
        ofstream file;
        file.open(filename, ios::app);
        file << newNumberInput.index << "," << newNumberInput.type << "," << newNumberInput.description << ","
             << "\n";
        file.close();
    }
};

/// @brief Fields: number output, operations, involved steps
/// @param number output: configured at runtime
/// @param operations: configured at runtime
/// @param involved steps: | step number - at flow creation
///                        | actual value - at runtime
class CalculusStep {
public:
    int index = 0;
    string type = "CALCULUS";
    float number_output;
    std::vector<string> operations; /// Contains: +, -, *, /, MAX, MIN
    std::vector<NumberInputStep> involved_steps;

    /*
      In the config file, the syntax consist of NrSteps intertwined with operations.
     */

    CalculusStep() {
        this->number_output = 0;
    }

    [[nodiscard]] float getNumberOutput() const {
        return this->number_output;
    }

    [[nodiscard]] int getIndex() const {
        return this->index;
    }

    static void setInvolvedSteps(CalculusStep &calculusStep, std::vector<NumberInputStep> &involved_steps) {
        calculusStep.involved_steps = involved_steps;
    }

    static void setIndex(CalculusStep &calculusStep, int new_index) {
        calculusStep.index = new_index;
    }

    static float returnMax(std::vector<NumberInputStep> &involved_steps) {
        float max = 0;
        for (auto &involved_step: involved_steps) {
            if (max > involved_step.number_input) {
                max = involved_step.number_input;
            } else
                continue;
        }
        return max;
    }

    static float returnMin(std::vector<NumberInputStep> &involved_steps) {
        float min = 0;
        for (auto &involved_step: involved_steps) {
            if (min < involved_step.number_input) {
                min = involved_step.number_input;
            } else
                continue;
        }
        return min;
    }

    static string enterOperation() {
        fflush(stdin);
        string temp_operation = "+";

        while (true) {
            cout << "Enter operation: ";
            getline(cin, temp_operation);

            if (Utils::operationValidity(temp_operation)) {
                return temp_operation;
            } else {
                cout << "Invalid operation. Try again.\n";
            }
        }
    }

    static void printSteps(CalculusStep &calculusStep) {
        std::vector<int> involved_steps_indexes;
        for (auto &involved_step: calculusStep.involved_steps) {
            cout << "Step " << involved_step.index << " (" << involved_step.description << ")"
                 << "\n";
        }
    }

    static int enterStep(CalculusStep &calculusStep) {
        int choice;
        cout << "Available number input steps: \n";
        printSteps(calculusStep);

        while (true) {
            cout << "Choose a step by its index: ";
            cin >> choice;

            for (auto &involved_step: calculusStep.involved_steps) {
                if (involved_step.index == choice) {
                    cout << "Step " << choice << " chosen. \n";
                    return choice;
                }
            }
        }
    }

    static void writeCalculusStep(CalculusStep &calculusStep, const string &filename) {
        cout << "Writing calculus step to file...\n";
        ofstream file;
        file.open(filename, ios::app);
        file << calculusStep.index << "," << calculusStep.type << ",";

        FlowUtils::printOperations();
        printSteps(calculusStep);

        if (calculusStep.involved_steps.empty()) {
            cout << "No number steps were added. \n";
            return;
        }

        if (calculusStep.involved_steps.size() == 1) {
            file << "Step " << enterStep(calculusStep) << ","
                 << "\n";
            return;
        } else {

            for (int i = 0; i < calculusStep.involved_steps.size() - 1; i++) {
                file << "Step " << enterStep(calculusStep) << " " << enterOperation() << " ";
            }

            /// for the last one
            file << "Step " << enterStep(calculusStep) << ","
                 << "\n";
        }
    }
};

/// @param filename: configured at runtime
class TextFileStep {
public:
    int index;
    string type = "TEXT FILE";
    string filename;

    TextFileStep() {
        this->index = 0;
        this->filename = "default";
    }

    void setFilename(string new_filename) {
        this->filename = std::move(new_filename);
    }

    virtual void setIndex(int new_index) {
        this->index = new_index;
    }

    [[nodiscard]] string getFilename() const {
        return this->filename;
    }

    static string enterFilename() {
        fflush(stdin);
        string temp_filename;

        while (true) {
            cout << "Enter filename: ";
            getline(cin, temp_filename);

            if (Utils::isTxtFile(temp_filename)) {
                return temp_filename;
            } else {
                cout << "Not a .txt file. \n";
            }
        }
    }

    static void setupTextFileStep(TextFileStep &newTextFile) {
        std::cout << "Setting up a TEXT FILE step...\n";
        newTextFile.setFilename(enterFilename());
    }

    static void writeFileStep(TextFileStep &newTextFile, const string &filename) {
        ofstream file;
        file.open(filename, ios::app);
        file << newTextFile.index << "," << newTextFile.type << "," << newTextFile.getFilename() << "\n";
        file.close();
    }
};

/// @brief CSVFileStep will inherit TextFileStep
/// it only performs a different regex check
class CSVFileStep : TextFileStep {
public:
    int index;
    string type = "CSV FILE";

    CSVFileStep() {
        this->index = 0;
        this->filename = "default";
    }

    static string enterFilename() {
        fflush(stdin);
        string temp_filename;

        while (true) {
            cout << "Enter filename: ";
            getline(cin, temp_filename);

            if (Utils::isCsvFile(temp_filename)) {
                return temp_filename;
            } else {
                cout << "Not a .csv file name. \n";
            }
        }
    }

    void setIndex(int new_index) override {
        this->index = new_index;
    }

    [[nodiscard]] string getFilename() {
        return this->filename;
    }

    [[nodiscard]] int getIndex() const {
        return this->index;
    }

    static void setupCSVFileStep(CSVFileStep &newCSVFile) {
        std::cout << "Setting up a CSV FILE step...\n";
        newCSVFile.setFilename(enterFilename());
    }

    static void writeFileStep(CSVFileStep &newCSVFile, const string &filename) {
        ofstream file;
        file.open(filename, ios::app);
        file << newCSVFile.index << "," << newCSVFile.type << "," << newCSVFile.filename << "\n";
        file.close();
    }
};

/// @brief Fields: file to display
/// @param file to display: configured at flow creation
class DisplayStep {
public:
    int index;
    string file_to_display;
    string type = "DISPLAY";

    DisplayStep() {
        this->index = 0;
        this->file_to_display = "default";
    };

    void setFileToDisplay(string new_filename) {
        this->file_to_display = std::move(new_filename);
    }

    [[nodiscard]] string getFileToDisplay() const {
        return this->file_to_display;
    }

    static string enterFilename() {
        fflush(stdin);
        string temp_filename;

        while (true) {
            cout << "File to display: ";
            getline(cin, temp_filename);

            if (Utils::isTxtFile(temp_filename) || Utils::isCsvFile(temp_filename)) {
                return temp_filename;
            } else {
                cout << "Not a .txt/.csv file. \n";
            }
        }
    }

    static void displayFile(const string &filename) {
        ifstream file;
        file.open(filename);
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    }

    static void setupDisplayStep(DisplayStep &newDisplayStep) {
        std::cout << "Setting up a DISPLAY step...\n";
        newDisplayStep.setFileToDisplay(enterFilename());
    }

    static void writeDisplayStep(const DisplayStep &displayStep, const string &filename) {
        ofstream file;
        file.open(filename, ios::app);
        cout << "Output file will be written in: " << displayStep.getFileToDisplay() << "\n";
        file << displayStep.index << "," << displayStep.type << "," << displayStep.file_to_display << ","
             << "\n";
        file.close();
    }
};

class OutputStep {
public:
    int index;
    string type = "OUTPUT";
    string out_file;

    OutputStep() {
        this->index = 0;
        this->out_file = "set at runtime";
    }

    /// No variables to be set at flow creation

    static void writeOutputStep(const OutputStep &outputStep, const string &filename) {
        ofstream file;
        file.open(filename, ios::app);
        file << outputStep.index << "," << outputStep.type << "," << outputStep.out_file << "\n";
        file.close();
    }
};

class EndStep {
public:
    int index;
    string type = "END";
    string flow_list = "FlowList.csv";

    EndStep() {
        this->index = 0;
    }

    static void writeEndStep(const EndStep &endStep, const string &filename) {
        ofstream file;
        file.open(filename, ios::app);
        file << endStep.index << "," << endStep.type << "," << "created at: " << Utils::getTimeStamp() << "\n";
        file.close();
    }

    static void addFlowToList(const TitleStep &titleStep) {
        ofstream file;
        file.open("FlowList.csv", ios::app);
        file << titleStep.getTitle() << ",./FlowConfigFiles/" << titleStep.getTitle() << "FlowConfig.csv" << "\n";
        file.close();
    }
};

#endif