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

void Observer::updateStarted() {
    this->times_started += 1;
}

void Observer::updateFinished() {
    this->times_finished += 1;
}

void Observer::updateAnalytics(const Observer& observer) {
    string flow_list = "FlowList.csv";
    vector<vector<string>> flow_list_content = FlowRunner::readCSV(flow_list);
    vector<vector<string>> config_file_content;
    vector<vector<string>> run_file_content;
    int errors;
    string flow_name = observer.flow_name;

    ofstream flow_list_file;
    flow_list_file.open(flow_list, ios::app);

    ///@details iterates backwards to get the latest entry of the flow
    for (auto it = flow_list_content.rbegin(); it != flow_list_content.rend(); ++it) {
        auto &i = *it;

        if (i[0] == flow_name) {
            i[2] = std::to_string(observer.times_started);
            i[3] = std::to_string(observer.times_finished);

            config_file_content = FlowRunner::readCSV("./FlowConfigFiles/" + flow_name + "FlowConfig.csv");
            run_file_content = FlowRunner::readCSV("./FlowRunFiles/" + flow_name + "FlowRun.csv");

            errors = run_file_content.size() - config_file_content.size();

            flow_list_file << i[0] << "," << i[1] << "," << i[2] << "," << i[3] << "," << errors << "\n";
            break;
        }
    }
}