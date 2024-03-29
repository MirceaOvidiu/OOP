#ifndef ezFlow_STEPS_H
#define ezFlow_STEPS_H

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include "utils.h"

using namespace std;

class TitleStep {
public:
    string type;
    int index;
    string title;
    string subtitle;

    TitleStep();

    ~TitleStep();

    void setTitle(string new_title);
    void setSubtitle(string new_subtitle);
    void setIndex(int new_index);

    [[nodiscard]] string getTitle() const;
    [[nodiscard]] string getSubtitle() const;
    [[nodiscard]] int getIndex() const;

    static string enterTitle();
    static string enterSubtitle();
    static void setupTitleStep(TitleStep &newTitle);
    static void writeTitleStep(const TitleStep &titleStep);
    static string writeTitleStep(const TitleStep &titleStep, const string &filename);
};

class TextStep : public TitleStep {
public:
    string type;
    int index;

    TextStep();

    void setText(string new_text);
    void setCopy();

    [[nodiscard]] string getText() const;
    [[nodiscard]] string getCopy() const;

    static string enterText();
    static void setupTextStep(TextStep &newText);
    static void writeTextStep(const TextStep &textStep, const string &filename);
};

class TextInputStep : public TitleStep {
public:
    string type;
    int index;

    TextInputStep();

    void setDescription(string new_description);
    void setTextInput(string new_text_input);

    [[nodiscard]] string getDescription() const;
    [[nodiscard]] string getTextInput() const;

    static string enterDescription();
    static string enterText();
    static void setupTextInputStep(TextInputStep &newTextInput);
    static void writeTextInputStep(TextInputStep &newTextInput, const string &filename);
};

class NumberInputStep {
public:
    string type;
    int index;
    float number_input;
    string description;

    NumberInputStep();

    void setNumberInput(float new_number_input);
    void setDescription(string new_description);
    void setIndex(int new_index);

    [[nodiscard]] float getNumberInput() const;
    [[nodiscard]] string getDescription() const;
    [[nodiscard]] int getIndex() const;

    static string enterDescription();
    static float enterNumberStepInput();
    static void setupNumberInputStep(NumberInputStep &newNumberInput);
    static void writeNumberInputStep(NumberInputStep &newNumberInput, const string &filename);
};

class CalculusStep {
public:
    int index;
    string type;
    float number_output;
    vector<string> operations;
    vector<NumberInputStep> involved_steps;

    CalculusStep();

    [[nodiscard]] float getNumberOutput() const;
    [[nodiscard]] int getIndex() const;
    [[nodiscard]] vector<string> getOperations() const;
     /// [[nodiscard]] vector<NumberInputStep> getInvolvedSteps() const;

    static void setInvolvedSteps(CalculusStep &calculusStep, vector<NumberInputStep> &involved_steps);
    static void setIndex(CalculusStep &calculusStep, int new_index);
    static void setNumberOutput(CalculusStep &calculusStep, float new_number_output);
    string setOperation(const string &operation);

    static float returnMax(vector<NumberInputStep> &involved_steps);
    static float returnMin(vector<NumberInputStep> &involved_steps);

    static string enterOperation();
    static void printSteps(CalculusStep &calculusStep);
    static int enterStep(CalculusStep &calculusStep);
    static void writeCalculusStep(CalculusStep &calculusStep, const string &filename);
    static void writeCalculusStepComponents(CalculusStep &calculusStep, const string& rule, const string &filename);
};

class TextFileStep {
public:
    int index;
    string type;
    string description;
    string filename;

    TextFileStep();

    void setFilename(string new_filename);
    void setDescription(string new_description);
    virtual void setIndex(int new_index);

    [[nodiscard]] string getFilename() const;

    static string enterFilename();
    static void setupTextFileStep(TextFileStep &newTextFile);
    static void writeFileStep(TextFileStep &newTextFile, const string &filename);

    friend class CSVFileStep;
};

class CSVFileStep : public TextFileStep {
public:
    int index;
    string type;

    CSVFileStep();

    static string enterFilename();
    void setIndex(int new_index) override;

    [[nodiscard]] int getIndex() const;

    static void setupCSVFileStep(CSVFileStep &newCSVFile);
    static void writeFileStep(CSVFileStep &newCSVFile, const string &filename);

    friend class TextFileStep;
};

class DisplayStep {
public:
    int index;
    string file_to_display;
    string type;

    DisplayStep();

    virtual void setIndex(int new_index);
    void setFileToDisplay(string new_filename);

    [[nodiscard]] string getFileToDisplay() const;

    static string enterFilename();
    static void displayFile(const string &filename);
    static void setupDisplayStep(DisplayStep &newDisplayStep);
    static void writeDisplayStep(const DisplayStep &displayStep, const string &filename);
};

class OutputStep : DisplayStep {
public:
    int index;
    string type;
    string out_file;

    OutputStep();

    void setIndex(int new_index) override;
    void setOutFile(string new_out_file);

    [[nodiscard]] string getOutFile() const;
    static void writeOutputStep(const OutputStep &outputStep, const string &filename);
};

class EndStep : public TitleStep{
public:
    int index;
    string type;
    string flow_list;
    string time_created;

    EndStep();

    void setTimeCreated(string new_time_created);

    static void writeEndStep(const EndStep &endStep, const string &filename);
    static void addFlowToList(const TitleStep &titleStep);
};

#endif //ezFlow_STEPS_H