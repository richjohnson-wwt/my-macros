#ifndef OUTLOOK_MODEL_H
#define OUTLOOK_MODEL_H

#include "db/DbDaily.h"
#include "db/DbGoal.h"
#include "MyMacroTypes.h"
#include <vector>

class IOutlookModel {
public:
    virtual std::vector<DailyFood> getDailyFoodsByRange(const std::string& startDate, const std::string& endDate) = 0;
    virtual std::vector<XrefDailyFood> getXrefDailyFoods(const DailyFood &df) = 0;
    virtual std::string getGoalStartDate() = 0;
    virtual DailyFood getDailyFoodByDate(const std::string& date) = 0;
    virtual long getGoalTargetWeight() = 0;

};

class OutlookModel : public IOutlookModel {
private:
    DbDaily *m_dbDaily;
    DbGoal *m_dbGoal;

public:
    OutlookModel(DbDaily *dbDaily, DbGoal *dbGoal);

    std::vector<DailyFood> getDailyFoodsByRange(const std::string& startDate, const std::string& endDate) override;
    std::vector<XrefDailyFood> getXrefDailyFoods(const DailyFood &df) override;
    std::string getGoalStartDate() override;
    DailyFood getDailyFoodByDate(const std::string& date) override;
    long getGoalTargetWeight() override;

};


#endif // OUTLOOK_MODEL_H