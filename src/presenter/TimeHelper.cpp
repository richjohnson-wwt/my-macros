#include "TimeHelper.h"


std::string TimeHelper::getNow() {
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    auto today_time_t = std::chrono::system_clock::to_time_t(today);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&today_time_t), "%Y-%m-%d");
    return ss.str();
}

std::chrono::system_clock::time_point TimeHelper::getTimePointFromString(const std::string &dateString) {
    std::tm tm = {};
    std::stringstream ss(dateString);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::chrono::seconds TimeHelper::getSecondsBetweenDateAndToday(const std::chrono::system_clock::time_point &tpDate) {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - tpDate);
}

std::string TimeHelper::getFutureDateInWeeks(const std::chrono::system_clock::time_point &tpStartDate, long weeks) {
    std::chrono::system_clock::time_point tpEndDate = tpStartDate + std::chrono::hours(7 * 24 * weeks);
    auto normalizedTime_t = std::chrono::system_clock::to_time_t(tpEndDate);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&normalizedTime_t), "%Y-%m-%d");
    return ss.str();
}

std::string TimeHelper::getOneWeekAgo() {
    std::chrono::system_clock::time_point oneWeekAgo = std::chrono::system_clock::now() - std::chrono::hours(7 * 24);
    auto one_week_ago_time_t = std::chrono::system_clock::to_time_t(oneWeekAgo);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&one_week_ago_time_t), "%Y-%m-%d");
    return ss.str();
}