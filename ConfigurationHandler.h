//
// Created by amiramyss on 6/9/22.
//

#ifndef OS3_CONFIGURATIONHANDLER_H
#define OS3_CONFIGURATIONHANDLER_H

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


#endif //OS3_CONFIGURATIONHANDLER_H
