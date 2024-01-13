//
// Created by Mircea on 1/12/2024.
//

#ifndef OOP_ANALYTICS_H
#define OOP_ANALYTICS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <steps.h>
#include <flowRunner.h>

class Observer {
public:
    string flow_name;
    int times_started = 0;
    int times_finished = 0;

    void updateStarted();
    void updateFinished();

    void setFlowName(string flow_name);

    static string getFlowName(const Observer& observer);
    static int getTimesStarted(const Observer& observer);
    static int getTimesFinished(const Observer& observer);

    static void updateAnalytics(const Observer& observer);

    Observer();
};

#endif//OOP_ANALYTICS_H
