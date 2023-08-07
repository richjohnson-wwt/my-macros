
#include "DailyModel.h"

#include <spdlog/spdlog.h>

DailyModel::DailyModel(DbDaily *dbDaily, 
    IFoodListModel *foodListModel, IRecipeListModel *recipeListModel, IRecipeModel *recipeModel)
: m_dbDaily(dbDaily), m_foodListModel(foodListModel), m_recipeListModel(recipeListModel), m_recipeModel(recipeModel)
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
    spdlog::debug("DailyModel::getDailyFood() {}", m_dateString);
    DailyFood df = m_dbDaily->getDailyFood(m_dateString);
    return df;
}

std::vector<XrefDailyFood> DailyModel::getXrefDailyFoods(const DailyFood& df)
{
    spdlog::debug("DailyModel::getXrefDailyFoods() {}", df.id);
    return m_dbDaily->getXrefDailyFoods(df);
}

void DailyModel::addExercise(int exerciseCalories)
{
    spdlog::debug("DailyModel::addExercise() {}", exerciseCalories);
    DailyFood df = m_dbDaily->getDailyFood(m_dateString);
    df.dailyActivityBonusCalories += exerciseCalories;
    m_dbDaily->updateDailyFood(df);
}

void DailyModel::addXrefDailyFood(const XrefDailyFood &xdf)
{
    spdlog::debug("DailyModel::addDailyFood()");
    m_dbDaily->addXrefDailyFood(xdf);
    
}

Food DailyModel::getFood()
{
    spdlog::debug("DailyModel::getFood()");
    return m_foodListModel->getSelectedFood();
}

Recipe DailyModel::getRecipe()
{
    spdlog::debug("DailyModel::getRecipe()");
    return m_recipeListModel->getSelectedRecipe();
}

std::vector<Ingredient> DailyModel::getIngredients()
{
    spdlog::debug("DailyModel::getIngredients()");
    return m_recipeModel->getIngredients();
}

void DailyModel::setSelectedDailyFoodId(int id)
{
    spdlog::debug("DailyModel::setSelectedDailyFoodId({})", id);
    m_selectedDailyFoodId = id;
}

void DailyModel::deleteXrefDailyFood()
{
    spdlog::debug("DailyModel::deleteXrefDailyFood {}", m_selectedDailyFoodId);
    m_dbDaily->deleteXrefDailyFood(m_selectedDailyFoodId);
}

int DailyModel::getGoalFatGrams()
{
    return FAT_GRAMS;
}

int DailyModel::getGoalProteinGrams()
{
    return PROTEIN_GRAMS;
}

int DailyModel::getGoalCarbGrams()
{
    return CARB_GRAMS;
}

int DailyModel::getGoalCalories()
{
    return TOTAL_CALORIES;
}