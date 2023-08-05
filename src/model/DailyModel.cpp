
#include "DailyModel.h"

#include <spdlog/spdlog.h>

DailyModel::DailyModel(DbDaily *dbDaily, IFoodListModel *foodListModel, IRecipeListModel *recipeListModel)
: m_dbDaily(dbDaily), m_foodListModel(foodListModel), m_recipeListModel(recipeListModel)
{

}

void DailyModel::setSelectedDate(const std::string& date)
{
    spdlog::debug("DailyModel::setSelectedDate() {}", date);
    m_dateString = date;
    if (m_dbDaily->doesTodayExist(date)){
        spdlog::info("DailyModel::setSelectedDate() {} does exist", date);
    } else {
        spdlog::info("DailyModel::setSelectedDate() {} does not exist", date);
        DailyFood df = DailyFood{0, date, 0};
        m_dbDaily->saveDailyFood(df);
    }
}

DailyFood DailyModel::getDailyFood()
{
    spdlog::info("DailyModel::getDailyFood() {}", m_dateString);
    DailyFood df = m_dbDaily->getDailyFood(m_dateString);
    return df;
}

std::vector<XrefDailyFood> DailyModel::getXrefDailyFoods(const DailyFood& df)
{
    spdlog::info("DailyModel::getXrefDailyFoods() {}", df.id);
    return m_dbDaily->getXrefDailyFoods(df);
}