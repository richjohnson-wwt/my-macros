#ifndef TIME_HELPER_H
#define TIME_HELPER_H

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

class TimeHelper {
public:
    std::string getNow();
    std::chrono::system_clock::time_point getTimePointFromString(const std::string &dateString);
    std::chrono::seconds getSecondsBetweenDateAndToday(const std::chrono::system_clock::time_point &tpDate);
    std::string getFutureDateInWeeks(const std::chrono::system_clock::time_point &tpStartDate, long weeks);
    std::string getOneWeekAgo();
    bool isDateInFuture(const std::string& date_str);


};

#endif // TIME_HELPER_H