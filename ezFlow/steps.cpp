#include "steps.h"

TitleStep::TitleStep() {
    this->index = 0;
    this->type = "TITLE";
}

TitleStep::~TitleStep() = default;

void TitleStep::setTitle(string new_title) {
    this->title = std::move(new_title);
}

void TitleStep::setSubtitle(string new_subtitle) {
    this->subtitle = std::move(new_subtitle);
}

void TitleStep::setIndex(int new_index) {
    this->index = new_index;
}

string TitleStep::getTitle() const {
    return this->title;
}

string TitleStep::getSubtitle() const {
    return this->subtitle;
}

int TitleStep::getIndex() const {
    return this->index;
}

string TitleStep::enterTitle() {
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

string TitleStep::enterSubtitle() {
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

void TitleStep::setupTitleStep(TitleStep &newTitle) {
    std::cout << "Setting up step " << newTitle.getIndex() << ": TITLE...\n";
    newTitle.setTitle(enterTitle());
    newTitle.setSubtitle(enterSubtitle());
}

void TitleStep::writeTitleStep(const TitleStep &titleStep) {
    ofstream file;
    string filename = "./FlowConfigFiles/" + titleStep.getTitle() + "FlowConfig.csv";
    file.open(filename, ios::app);
    file << "INDEX, TYPE, ARG1, ARG2\n";
    file << titleStep.getIndex() << "," << titleStep.type << "," << titleStep.getTitle() << ","
         << titleStep.getSubtitle() << "\n";
    file.close();
}

TextStep::TextStep() {
    this->index = 0;
    this->type = "TEXT";
}

void TextStep::setText(string new_text) {
    this->title = std::move(new_text);
}

void TextStep::setCopy() {
    this->subtitle = this->title;
}

string TextStep::getText() const {
    return this->title;
}

string TextStep::getCopy() const {
    return this->subtitle;
}

string TextStep::enterText() {
    fflush(stdin);
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

void TextStep::setupTextStep(TextStep &newText) {
    std::cout << "Setting up a TEXT step...\n";
    string new_text = enterText();
    newText.setText(new_text);
    newText.setCopy();
}

void TextStep::writeTextStep(const TextStep &textStep, const string &filename) {
    ofstream file;
    file.open(filename, ios::app);
    file << textStep.getIndex() << "," << textStep.type << "," << textStep.getText() << "," << textStep.getCopy()
         << "\n";
    file.close();
}

TextInputStep::TextInputStep() {
    this->index = 0;
    this->type = "TEXT INPUT";
    this->subtitle = "unset";
}

void TextInputStep::setDescription(string new_description) {
    this->title = std::move(new_description);
}

void TextInputStep::setTextInput(string new_text_input) {
    this->subtitle = std::move(new_text_input);
}

string TextInputStep::getDescription() const {
    return this->title;
}

string TextInputStep::getTextInput() const {
    return this->subtitle;
}

string TextInputStep::enterDescription() {
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

string TextInputStep::enterText() {
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

void TextInputStep::setupTextInputStep(TextInputStep &newTextInput) {
    std::cout << "Setting up a TEXT INPUT step...\n";
    newTextInput.setDescription(enterDescription());
}

void TextInputStep::writeTextInputStep(TextInputStep &newTextInput, const string &filename) {
    ofstream file;
    file.open(filename, ios::app);
    file << newTextInput.getIndex() << "," << newTextInput.type << "," << newTextInput.title << ","
         << newTextInput.subtitle << "\n";
    file.close();
}

NumberInputStep::NumberInputStep() {
    this->index = 0;
    this->number_input = 0;
    this->type = "NUMBER INPUT";
}

void NumberInputStep::setNumberInput(float new_number_input) {
    this->number_input = new_number_input;
}

void NumberInputStep::setDescription(string new_description) {
    this->description = std::move(new_description);
}

float NumberInputStep::getNumberInput() const {
    return this->number_input;
}

string NumberInputStep::getDescription() const {
    return this->description;
}

int NumberInputStep::getIndex() const {
    return this->index;
}

string NumberInputStep::enterDescription() {
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

float NumberInputStep::enterNumberStepInput() {
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

void NumberInputStep::setupNumberInputStep(NumberInputStep &newNumberInput) {
    std::cout << "Setting up a NUMBER INPUT step..."
              << "\n";
    newNumberInput.setDescription(enterDescription());
    // newNumberInput.setNumberInput(enterNumberStepInput()); - at runtime
}

void NumberInputStep::writeNumberInputStep(NumberInputStep &newNumberInput, const string &filename) {
    ofstream file;
    file.open(filename, ios::app);
    file << newNumberInput.getIndex() << "," << newNumberInput.type << "," << newNumberInput.getDescription() << ","
         << newNumberInput.getNumberInput()<< "\n"; ///will be entered as 0 in the config file
    file.close();
}

CalculusStep::CalculusStep() {
    this->index = 0;
    this->number_output = 0;
    this->type = "CALCULUS";
}

void CalculusStep::setInvolvedSteps(CalculusStep &calculusStep, vector<NumberInputStep> &involved_steps) {
    calculusStep.involved_steps = involved_steps;
}

void CalculusStep::setIndex(CalculusStep &calculusStep, int new_index) {
    calculusStep.index = new_index;
}

float CalculusStep::getNumberOutput() const {
    return this->number_output;
}

int CalculusStep::getIndex() const {
    return this->index;
}

float CalculusStep::returnMax(vector<NumberInputStep> &involved_steps) {
    float max = 0;
    for (auto &involved_step: involved_steps) {
        if (max > involved_step.number_input) {
            max = involved_step.number_input;
        } else
            continue;
    }
    return max;
}

float CalculusStep::returnMin(vector<NumberInputStep> &involved_steps) {
    float min = 0;
    for (auto &involved_step: involved_steps) {
        if (min < involved_step.number_input) {
            min = involved_step.number_input;
        } else
            continue;
    }
    return min;
}

string CalculusStep::enterOperation() {
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

void CalculusStep::printSteps(CalculusStep &calculusStep) {
    vector<int> involved_steps_indexes;
    for (auto &involved_step: calculusStep.involved_steps) {
        cout << "Step " << involved_step.index << " (" << involved_step.description << ")"
             << "\n";
    }
}

int CalculusStep::enterStep(CalculusStep &calculusStep) {
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

void CalculusStep::writeCalculusStep(CalculusStep &calculusStep, const string &filename) {
    cout << "Writing calculus step to file...\n";
    ofstream file;
    file.open(filename, ios::app);
    file << calculusStep.getIndex() << "," << calculusStep.type << ",";

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
        file << "Step " << enterStep(calculusStep) << "," << calculusStep.getNumberOutput()
             << "\n";
    }
}

TextFileStep::TextFileStep() {
    this->index = 0;
    this->type = "TEXT FILE";
    this->filename = "unset";
}

void TextFileStep::setFilename(string new_filename) {
    this->filename = std::move(new_filename);
}

void TextFileStep::setIndex(int new_index) {
    this->index = new_index;
}

string TextFileStep::getFilename() const {
    return this->filename;
}

string TextFileStep::enterFilename() {
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

void TextFileStep::setupTextFileStep(TextFileStep &newTextFile) {
    std::cout << "Setting up a TEXT FILE step...\n";
    newTextFile.setFilename(enterFilename());
}

void TextFileStep::writeFileStep(TextFileStep &newTextFile, const string &filename) {
    ofstream file;
    file.open(filename, ios::app);
    file << newTextFile.index << "," << newTextFile.type << "," << newTextFile.getFilename() << "\n";
    file.close();
}

CSVFileStep::CSVFileStep() {
    this->index = 0;
    this->type = "CSV FILE";
    this->filename = "unset";
}

string CSVFileStep::getFilename() {
    return this->filename;
}

int CSVFileStep::getIndex() const {
    return this->index;
}

string CSVFileStep::enterFilename() {
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

void CSVFileStep::setIndex(int new_index) {
    this->index = new_index;
}

void CSVFileStep::setupCSVFileStep(CSVFileStep &newCSVFile) {
    std::cout << "Setting up a CSV FILE step...\n";
    newCSVFile.setFilename(enterFilename());
}

void CSVFileStep::writeFileStep(CSVFileStep &newCSVFile, const string &filename) {
    ofstream file;
    file.open(filename, ios::app);
    file << newCSVFile.index << "," << newCSVFile.type << "," << newCSVFile.filename << "\n";
    file.close();
}

DisplayStep::DisplayStep() {
    this->index = 0;
    this->type = "DISPLAY";
}

void DisplayStep::setFileToDisplay(string new_filename) {
    this->file_to_display = std::move(new_filename);
}

string DisplayStep::getFileToDisplay() const {
    return this->file_to_display;
}

string DisplayStep::enterFilename() {
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

void DisplayStep::displayFile(const string &filename) {
    ifstream file;
    file.open(filename);
    string line;
    while (getline(file, line)) {
        cout << line << "\n";
    }
    file.close();
}

void DisplayStep::setupDisplayStep(DisplayStep &newDisplayStep) {
    std::cout << "Setting up a DISPLAY step...\n";
    newDisplayStep.setFileToDisplay(enterFilename());
}

void DisplayStep::writeDisplayStep(const DisplayStep &displayStep, const string &filename) {
    ofstream file;
    file.open(filename, ios::app);
    cout << "Output file will be written in: " << displayStep.getFileToDisplay() << "\n";
    file << displayStep.index << "," << displayStep.type << "," << displayStep.file_to_display << ","
         << "\n";
    file.close();
}

OutputStep::OutputStep() {
    this->index = 0;
    this->type = "OUTPUT";
    this->out_file = "unset";
}

void OutputStep::writeOutputStep(const OutputStep &outputStep, const string &filename) {
    ofstream file;
    file.open(filename, ios::app);
    file << outputStep.index << "," << outputStep.type << "," << outputStep.out_file << "\n";
    file.close();
}

EndStep::EndStep() {
    this->index = 0;
    this->type = "END";
}

void EndStep::writeEndStep(const EndStep &endStep, const std::string &filename) {
    ofstream file;
    file.open(filename, ios::app);
    file << endStep.index << "," << endStep.type << ","
         << "created at: " << Utils::getTimeStamp() << "\n";
    file.close();
}

void EndStep::addFlowToList(const TitleStep &titleStep) {
    ofstream file;
    file.open("FlowList.csv", ios::app);
    file << titleStep.getTitle() << ",./FlowConfigFiles/" << titleStep.getTitle() << "FlowConfig.csv"
         << "\n";
    file.close();
}