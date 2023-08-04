#ifndef DB_DAILY_H
#define DB_DAILY_H

#include "DbBase.h"

class DbDaily : public DbBase {
public:
    DbDaily(const std::string& dbfile);

    DailyFood getDailyFood(const std::string& date);
    std::vector<XrefDailyFood> getXrefDailyFoods(const DailyFood& df);

};

#endif // DB_DAILY_H