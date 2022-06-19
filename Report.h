//
// Created by amiramyss on 6/14/22.
//

#ifndef OS3_REPORT_H
#define OS3_REPORT_H

#include <iostream>

enum ReportType {SPORTS, NEWS, WEATHER, ERROR};
class Report {
private:
    unsigned int _producerId, _reportId;
    ReportType _type;
    int randomCategory();
public:
    Report();
    Report(unsigned int producerId, unsigned int reportId);
    friend std::ostream& operator<<(std::ostream& os, const Report &report);
    std::string toString() const;
    static ReportType getReportType(const std::string& rep);
};


#endif //OS3_REPORT_H
