//
// Created by Mircea on 1/9/2024.
//

// CLI.cpp

#include "CLI.h"
#include "steps.h"

using namespace std;

CLI::CLI() {
    cout << "ezFlow CLI session started\n";
}

void CLI::createFlowMenu() {
    int step_count = 0;


    cout << "Creating flow...\n";

    cout << "Available steps:\n";
    FlowUtils::listStepDetails();

    TitleStep Title = TitleStep();
    TitleStep::setupTitleStep(Title);
    Title.setIndex(step_count);
    TitleStep::writeTitleStep(Title);

    string filename = "./FlowConfigFiles/" + Title.getTitle() + "FlowConfig.csv";

    std::vector<NumberInputStep> NumberInputSteps;

    while (true) {
        int choice;
        FlowUtils::listSteps();
        choice = FlowUtils::chooseStep();

        if (choice == 1) {
            cout << "The flow already has a title \n";
        }

        if (choice == 2) {
            step_count += 1;

            TextStep Text = TextStep();
            TextStep::setupTextStep(Text);
            Text.index = step_count;
            TextStep::writeTextStep(Text, filename);
        }

        if (choice == 3) {
            step_count += 1;
            TextInputStep TextInput = TextInputStep();
            TextInputStep::setupTextInputStep(TextInput);
            TextInput.index = step_count;
            TextInputStep::writeTextInputStep(TextInput, filename);
        }

        if (choice == 4) {
            step_count += 1;
            NumberInputStep NumberInput = NumberInputStep();
            NumberInputStep::setupNumberInputStep(NumberInput);
            NumberInput.index = step_count;
            NumberInputSteps.push_back(NumberInput);
            NumberInputStep::writeNumberInputStep(NumberInput, filename);
        }

        if (choice == 5) {
            step_count += 1;
            CalculusStep Calculus = CalculusStep();
            CalculusStep::setIndex(Calculus, step_count);
            CalculusStep::setInvolvedSteps(Calculus, NumberInputSteps);
            CalculusStep::writeCalculusStep(Calculus, filename);
        }

        if (choice == 6) {
            step_count += 1;
            TextFileStep TextFile = TextFileStep();
            TextFileStep::setupTextFileStep(TextFile);
            TextFile.setIndex(step_count);
            TextFileStep::writeFileStep(TextFile, filename);
        }

        if (choice == 7) {
            step_count += 1;
            CSVFileStep CSVFile = CSVFileStep();
            CSVFileStep::setupCSVFileStep(CSVFile);
            CSVFile.setIndex(step_count);
            CSVFileStep::writeFileStep(CSVFile, filename);
        }

        if (choice == 8) {
            step_count += 1;
            DisplayStep Display = DisplayStep();
            DisplayStep::setupDisplayStep(Display);
            Display.index = step_count;
            DisplayStep::writeDisplayStep(Display, filename);
        }

        if (choice == 9) {
            step_count += 1;
            OutputStep Output = OutputStep();
            Output.index = step_count;
            OutputStep::writeOutputStep(Output, filename);
        }

        if (choice == 10) {
            step_count += 1;
            EndStep End = EndStep();
            End.index = step_count;
            EndStep::writeEndStep(End, filename);
            EndStep::addFlowToList(Title);
            break;
        }

        if (choice == 11) {
            cout << "Quitting flow creation...\n";
            break;
        }
    }
}

void CLI::runFlowMenu() {
    FlowRunner flowRunner = FlowRunner();
    std::vector<vector<string>> flows;
    std::string chosen_flow;
    flows = FlowRunner::readCSV("./FlowList.csv");

    cout << "Choose a flow to run:\n";
    FlowRunner::displayContent(flows);
    chosen_flow = flowRunner.chooseFlow(flows);

    cout << "Chosen flow: " << chosen_flow << "\n";
}

void CLI::mainMenu() {
    int choice;
    cout << "1. Create new flow\n";
    cout << "2. Open and run existing flow\n";
    cout << "3. Exit\n";
    cin >> choice;

    switch (choice) {
        case 1:
            createFlowMenu();
            break;
        case 2:
            runFlowMenu();
            break;
        case 3:
            cout << "Quitting...\n";
            exit(1);
        default:
            cout << "Invalid choice. Try again.\n";
            break;
    }
}
