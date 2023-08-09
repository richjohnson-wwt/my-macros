#include "OutlookModel.h"

OutlookModel::OutlookModel(DbDaily *dbDaily, DbGoal *dbGoal): m_dbDaily(dbDaily), m_dbGoal(dbGoal)
{
}


std::vector<DailyFood> OutlookModel::getDailyFoodsByRange(const std::string& startDate, const std::string& endDate) {
    return m_dbDaily->getDailyFoodByRange(startDate, endDate);
}
    
std::vector<XrefDailyFood> OutlookModel::getXrefDailyFoods(const DailyFood &df) {
    return m_dbDaily->getXrefDailyFoods(df);
}

std::string OutlookModel::getGoalStartDate() {
    return m_dbGoal->getGoal().startDate;
}

DailyFood OutlookModel::getDailyFoodByDate(const std::string& date) {
    return m_dbDaily->getDailyFood(date);
}

long OutlookModel::getGoalTargetWeight() {
    return m_dbGoal->getGoal().targetWeight;
}

long OutlookModel::getBmr() {
    return m_dbGoal->getGoal().bmrCalories;
}