//
// Created by Mircea on 12/28/2023.
//

#ifndef OOP_UX_H
#define OOP_UX_H

#include <iostream>
#include "steps.h"
#include "utils.h"
#include "flowRunner.h"

using namespace std;

class UX {
    /// @brief Creates a new flow file
    /// The step objects are instantiated, personalized,
    /// do a test run, and at the end are written to the flow file.

    /// Steps will be sequentially written to the file.
public:
    UX() {
        cout << " ezFlow session started\n";
    }

    static void createFlow() {

        int step_count = 0;

        cout << "Creating flow...\n";

        /// Will be here by default.
        /// Only 1 title step per flow is allowed.
        /// The flow config file is created here as well.

        TitleStep Title = TitleStep();
        TitleStep::setupTitleStep(Title);
        Title.setIndex(step_count);
        TitleStep::writeTitleStep(Title);

        string filename = "./FlowConfigFiles/" + Title.getTitle() + "FlowConfig.csv";


        /// All the number inputs will be moved here after writing
        /// to be accessed in the Calculus step, without having to
        /// initialize a Calculus step before the NumberInput steps.
        std::vector<NumberInputStep> NumberInputSteps;
        /// For memory management purposes, it will be copied to the Calculus step

        while (true) {
            int choice;

            choice = FlowUtils::chooseStep();

            ///switch cannot be used due to object initialization here

            if(choice == 1)
            {
                cout << "The flow already has a title \n";
            }

            if(choice == 2)
            {
                step_count +=1;

                TextStep Text = TextStep();
                TextStep::setupTextStep(Text);
                Text.index = step_count;
                TextStep::writeTextStep(Text,filename);
            }

            if(choice == 3)
            {
                step_count+=1;
                TextInputStep TextInput = TextInputStep();
                TextInputStep::setupTextInputStep(TextInput);
                TextInput.index = step_count;
                TextInputStep::writeTextInputStep(TextInput,filename);
            }

            if(choice == 4)
            {
                step_count+=1;
                NumberInputStep NumberInput = NumberInputStep();
                NumberInputStep::setupNumberInputStep(NumberInput);
                NumberInput.index = step_count;
                NumberInputSteps.push_back(NumberInput);
                NumberInputStep::writeNumberInputStep(NumberInput,filename);
            }

            /// All the NumberInput steps are to be introduced before this step.
            if(choice == 5)
            {
                step_count+=1;
                CalculusStep Calculus = CalculusStep();
                /// Here, the phases will be added,
                /// the calculus rule will be defined
                /// and the actual values will be introduced at runtime.
                CalculusStep::setIndex(Calculus, step_count);
                CalculusStep::setInvolvedSteps(Calculus, NumberInputSteps);
                CalculusStep::writeCalculusStep(Calculus,filename);
            }

            if(choice == 6)
            {
                step_count+=1;
                TextFileStep TextFile = TextFileStep();
                TextFileStep::setupTextFileStep(TextFile);
                TextFile.setIndex(step_count);
                TextFileStep::writeFileStep(TextFile,filename);
            }

            if(choice == 7)
            {
                step_count+=1;
                CSVFileStep CSVFile = CSVFileStep();
                CSVFileStep::setupCSVFileStep(CSVFile);
                CSVFile.setIndex(step_count);
                CSVFileStep::writeFileStep(CSVFile,filename);
            }

            if(choice == 8)
            {
                step_count+=1;
                DisplayStep Display = DisplayStep();
                DisplayStep::setupDisplayStep(Display);
                Display.index = step_count;
                DisplayStep::writeDisplayStep(Display,filename);
            }

            if(choice == 9)
            {
                step_count+=1;
                OutputStep Output = OutputStep();
                Output.index = step_count;
                OutputStep::writeOutputStep(Output,filename);
            }

            if(choice == 10)
            {
                step_count+=1;
                EndStep End = EndStep();
                /// Nothing to setup here
                End.index = step_count;
                EndStep::writeEndStep(End,filename);
                EndStep::addFlowToList(Title);
                break;
            }

            if(choice == 11){
                cout << "Quitting flow creation...\n";
                break;
            }
        }
    }

    static void runFlow() {
        cout << "Running flow...\n";
        FlowRunner::runFlow();
    }

    static void mainMenu() {
        int choice;
        cout << "1. Create new flow\n";
        cout << "2. Open and run existing flow\n";
        cout << "3. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                createFlow();
                break;
            case 2:
                runFlow();
                break;
            case 3:
                
                cout << "Quitting...\n";
                exit(1);
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    }
};

#endif // OOP_UX_H
