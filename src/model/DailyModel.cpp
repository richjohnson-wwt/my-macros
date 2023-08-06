
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
    spdlog::info("DailyModel::getDailyFood() {}", m_dateString);
    DailyFood df = m_dbDaily->getDailyFood(m_dateString);
    return df;
}

std::vector<XrefDailyFood> DailyModel::getXrefDailyFoods(const DailyFood& df)
{
    spdlog::info("DailyModel::getXrefDailyFoods() {}", df.id);
    return m_dbDaily->getXrefDailyFoods(df);
}

void DailyModel::addExercise(int exerciseCalories)
{
    spdlog::info("DailyModel::addExercise() {}", exerciseCalories);
    DailyFood df = m_dbDaily->getDailyFood(m_dateString);
    df.dailyActivityBonusCalories += exerciseCalories;
    m_dbDaily->updateDailyFood(df);
}

void DailyModel::addXrefDailyFood(const XrefDailyFood &xdf)
{
    spdlog::info("DailyModel::addDailyFood()");
    m_dbDaily->addXrefDailyFood(xdf);
    
}

Food DailyModel::getFood()
{
    spdlog::info("DailyModel::getFood()");
    return m_foodListModel->getSelectedFood();
}

Recipe DailyModel::getRecipe()
{
    spdlog::info("DailyModel::getRecipe()");
    return m_recipeListModel->getSelectedRecipe();
}

std::vector<Ingredient> DailyModel::getIngredients()
{
    spdlog::info("DailyModel::getIngredients()");
    return m_recipeModel->getIngredients();
}

void DailyModel::setSelectedDailyFoodId(int id)
{
    spdlog::info("DailyModel::setSelectedDailyFoodId({})", id);
    m_selectedDailyFoodId = id;
}

void DailyModel::deleteXrefDailyFood()
{
    spdlog::info("DailyModel::deleteXrefDailyFood {}", m_selectedDailyFoodId);
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