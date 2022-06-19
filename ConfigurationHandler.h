//
// Created by amiramyss on 6/9/22.
//

#pragma once

#include <vector>
#include <string>

class ConfigurationHandler {
public:
    struct ConfigurationItem {
        int producerId, numProducts, capacityQueue;
    };
    static std::vector<ConfigurationItem> *ReadConfig(std::string, int *);
private:

};