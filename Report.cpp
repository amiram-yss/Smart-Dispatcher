//
// Created by amiramyss on 6/14/22.
//

#include <cstdlib>
#include "Report.h"

Report::Report(unsigned int producerId, unsigned int reportId) :_producerId(producerId), _reportId(reportId){
    //srand(time(NULL)); //Will it be problematic with threads?
    _type = static_cast<ReportType>(std::rand() % 3);
}

std::ostream &operator<<(std::ostream &os, const Report &report) {
    os << report.toString();
    return os;
    /*os<< "producer " << report._producerId ;
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
    return os;*/
}

Report::Report() : _producerId(-1), _reportId(-1) {
    srand(time(NULL)); //Will it be problematic with threads?
    _type = static_cast<ReportType>(std::rand() % 3);
}

bool Report::isEndingReport() {
    return _reportId == -1;
}

std::string Report::toString() const{
    std::string str = "producer " + std::to_string(this->_producerId) + " ";
    switch (_type) {
        case ReportType::SPORTS:
             str += "SPORTS";
            break;
        case ReportType::NEWS:
            str += "NEWS";
            break;
        case ReportType::WEATHER:
            str+= "WEATHER";
            break;
    }
    str += " " + std::to_string(_reportId);
    return str;
}

ReportType Report::getReportType(const std::string& rep) {
    if (rep.find("SPORTS") != std::string::npos)
        return SPORTS;
    if (rep.find("NEWS") != std::string::npos)
        return NEWS;
    if (rep.find("WEATHER") != std::string::npos)
        return WEATHER;
    return ERROR;
}
