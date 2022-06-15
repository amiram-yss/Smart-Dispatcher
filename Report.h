//
// Created by amiramyss on 6/14/22.
//

#ifndef OS3_REPORT_H
#define OS3_REPORT_H

#import <iostream>

enum ReportType {SPORTS, NEWS, WEATHER};
class Report {
private:
    unsigned int _producerId, _reportId;
    ReportType _type;
public:
    Report();
    Report(unsigned int producerId, unsigned int reportId);
    friend std::ostream& operator<<(std::ostream& os, const Report &report);
};


#endif //OS3_REPORT_H
