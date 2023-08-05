#ifndef DB_DAILY_H
#define DB_DAILY_H

#include "DbBase.h"

class DbDaily : public DbBase {
public:
    DbDaily(const std::string& dbfile);

    DailyFood getDailyFood(const std::string& date);
    std::vector<XrefDailyFood> getXrefDailyFoods(const DailyFood& df);
    bool doesTodayExist(const std::string& today);

    void saveDailyFood(const DailyFood& df);
    void updateDailyFood(const DailyFood& df);
    void addXrefDailyFood(const XrefDailyFood &xrefDailyFood);

};

#endif // DB_DAILY_H