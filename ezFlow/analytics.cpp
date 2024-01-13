//
// Created by Mircea on 1/12/2024.
//

#include "analytics.h"

#include <utility>

using namespace std;

///@brief Observer class

Observer::Observer(){
    this->times_finished = 0;
    this->times_started = 0;

}

void Observer::setFlowName(string new_flow_name) {
    this->flow_name = std::move(new_flow_name);
}

string Observer::getFlowName(const Observer& observer) {
    return observer.flow_name;
}

int Observer::getTimesStarted(const Observer& observer) {
    return observer.times_started;
}

int Observer::getTimesFinished(const Observer& observer) {
    return observer.times_finished;
}

void Observer::updateStarted() {
    this->times_started += 1;
}

void Observer::updateFinished() {
    this->times_finished += 1;
}

void Observer::updateAnalytics(const Observer& observer) {
    string flow_list = "FlowList.csv";
    vector<vector<string>> flow_list_content = FlowRunner::readCSV(flow_list);
    string flow_name = observer.flow_name;

    ofstream flow_list_file;
    flow_list_file.open(flow_list, ios::app);

    ///@details iterates backwards to get the latest entry of the flow
    for (auto it = flow_list_content.rbegin(); it != flow_list_content.rend(); ++it) {
        auto &i = *it;

        if (i[0] == flow_name) {
            i[2] = std::to_string(observer.times_started);
            i[3] = std::to_string(observer.times_finished);

            flow_list_file << i[0] << "," << i[1] << "," << i[2] << "," << i[3] << "\n";
            break;
        }
    }
}