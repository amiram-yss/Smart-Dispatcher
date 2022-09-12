//
// Created by amiramyss on 6/9/22.
//

#pragma once

#include <vector>
#include <string>

/**
 * Handles configuration file.
 */
class ConfigurationHandler {
public:
    /**
     * Holding the data held in a single configuration block.
     */
    struct ConfigurationItem {
        int producerId, numProducts, capacityQueue;
    };

    /**
     * Read and process config file.
     * @return Array of configuration items, and updates 2nd param to screen buffer's size.
     */
    static std::vector<ConfigurationItem> *ReadConfig(std::string, int *);
private:

};