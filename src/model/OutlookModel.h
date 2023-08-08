#ifndef OUTLOOK_MODEL_H
#define OUTLOOK_MODEL_H

#include "db/DbDaily.h"
#include "MyMacroTypes.h"
#include <vector>

class IOutlookModel {
public:
    virtual std::vector<DailyFood> getDailyFoodsByRange(const std::string& startDate, const std::string& endDate) = 0;
    virtual std::vector<XrefDailyFood> getXrefDailyFoods(const DailyFood &df) = 0;
};

class OutlookModel : public IOutlookModel {
private:
    DbDaily *m_dbDaily;
public:
    OutlookModel(DbDaily *dbDaily);

    std::vector<DailyFood> getDailyFoodsByRange(const std::string& startDate, const std::string& endDate) override;
    std::vector<XrefDailyFood> getXrefDailyFoods(const DailyFood &df) override;
};


#endif // OUTLOOK_MODEL_H