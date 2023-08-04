
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