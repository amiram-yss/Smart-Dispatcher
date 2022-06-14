//
// Created by amiramyss on 6/9/22.
//

#include "ConfigurationHandler.h"
#include <vector>
#include <fstream>
#include <iostream>

std::vector <ConfigurationHandler::ConfigurationItem>
        *ConfigurationHandler::ReadConfig(std::string confFileName) {

    std::vector<ConfigurationItem>* vtr = new std::vector<ConfigurationItem>();
    std::ifstream confFile(confFileName);
    std::string line;
    while (std::getline(confFile,line)) {
        while (line == "\n")
            std::getline(confFile, line);
        int id = atoi(line.c_str());
        std::getline(confFile, line);
        int num = atoi(line.c_str());
        std::getline(confFile, line);
        int cap = atoi(line.c_str());
        vtr->push_back({id,num,cap});
        do {
            std::getline(confFile, line);
        } while (line == "\n");
    }
    return vtr;
}
