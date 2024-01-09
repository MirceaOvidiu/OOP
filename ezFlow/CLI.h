#ifndef OOP_CLI_H
#define OOP_CLI_H

#include "flowRunner.h"
#include <iostream>

class CLI {
public:
    CLI();

    static void createFlowMenu();

    static void runFlowMenu();

    static void mainMenu();
};

#endif // OOP_CLI_H