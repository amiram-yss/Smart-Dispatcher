//
// Created by amiramyss on 6/14/22.
//

#include <cstdlib>
#include <random>
#include <sys/time.h>
#include "Report.h"

/**
 * Constructor
 * @param producerId
 * @param reportId
 */
Report::Report(unsigned int producerId, unsigned int reportId) :_producerId(producerId), _reportId(reportId){
    //srand(time(NULL)); //Will it be problematic with threads?
    _type = static_cast<ReportType>(std::rand() % 3);
    //_type = static_cast<ReportType>(randomCategory());
}

/**
 * Default constructor.
 */
Report::Report() : _producerId(-1), _reportId(-1) {
    //srand(time(NULL)); //Will it be problematic with threads?
    _type = static_cast<ReportType>(std::rand() % 3);
    _type = static_cast<ReportType>(randomCategory());
}

/**
 * << operator overload.
 * @param os out stream
 * @param report report item
 * @return stream after printing report on it.
 */
std::ostream &operator<<(std::ostream &os, const Report &report) {
    os << report.toString();
    return os;
}

/**
 *
 * @return String representation of a Report item.
 */
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

/**
 *
 * @param rep String representation of a report item.
 * @return Type of report.
 */
ReportType Report::getReportType(const std::string& rep) {
    if (rep.find("SPORTS") != std::string::npos)
        return SPORTS;
    if (rep.find("NEWS") != std::string::npos)
        return NEWS;
    if (rep.find("WEATHER") != std::string::npos)
        return WEATHER;
    return ERROR;
}

/**
 * Return random category.
 * @return int in range [1,3]
 */
int Report::randomCategory() {
    struct timeval now{};
    gettimeofday(&now, nullptr);
    time_t msec_now = (now.tv_sec * 1000) + (now.tv_usec / 1000);
    return msec_now % 3;
}
