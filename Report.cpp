//
// Created by amiramyss on 6/14/22.
//

#include <cstdlib>
#include "Report.h"

Report::Report(unsigned int producerId, unsigned int reportId) :_producerId(producerId), _reportId(reportId){
    srand(time(NULL)); //Will it be problematic with threads?
    _type = static_cast<ReportType>(std::rand() % 3);
}

std::ostream &operator<<(std::ostream &os, const Report &report) {
    os<< "producer " << report._producerId ;
    os << " ";
    switch (report._type) {
        case ReportType::SPORTS:
            os << "SPORTS";
            break;
        case ReportType::NEWS:
            os << "NEWS";
            break;
        case ReportType::WEATHER:
            os << "WEATHER";
            break;
    }
    os << " ";
    os << report._reportId;
}

Report::Report() : _producerId(-1), _reportId(-1) {
    srand(time(NULL)); //Will it be problematic with threads?
    _type = static_cast<ReportType>(std::rand() % 3);
}
