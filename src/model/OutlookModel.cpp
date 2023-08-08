#include "OutlookModel.h"

OutlookModel::OutlookModel(DbDaily *dbDaily): m_dbDaily(dbDaily)
{
}


std::vector<DailyFood> OutlookModel::getDailyFoodsByRange(const std::string& startDate, const std::string& endDate) {
    return m_dbDaily->getDailyFoodByRange(startDate, endDate);
}
    
std::vector<XrefDailyFood> OutlookModel::getXrefDailyFoods(const DailyFood &df) {
    return m_dbDaily->getXrefDailyFoods(df);
}