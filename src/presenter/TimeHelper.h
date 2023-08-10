#ifndef TIME_HELPER_H
#define TIME_HELPER_H

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

class TimeHelper {
public:
    virtual std::string getNow();
    virtual std::chrono::system_clock::time_point getTimePointFromString(const std::string &dateString);
    virtual std::chrono::seconds getSecondsBetweenDateAndToday(const std::chrono::system_clock::time_point &tpDate);
    virtual std::string getFutureDateInWeeks(const std::chrono::system_clock::time_point &tpStartDate, long weeks);
    virtual std::string getOneWeekAgo();
    virtual bool isDateInFuture(const std::string& date_str);
};

#endif // TIME_HELPER_H