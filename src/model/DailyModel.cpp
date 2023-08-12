
#include "DailyModel.h"

#include <spdlog/spdlog.h>

DailyModel::DailyModel(DbDaily *dbDaily, 
    DbGoal *dbGoal,
    DbFood *dbFood,
    IFoodListModel *foodListModel, 
    IRecipeListModel *recipeListModel, 
    IRecipeModel *recipeModel)
: m_dbDaily(dbDaily), 
    m_dbGoal(dbGoal), 
    m_dbFood(dbFood),
    m_foodListModel(foodListModel), 
    m_recipeListModel(recipeListModel), 
    m_recipeModel(recipeModel)
{
}

void DailyModel::createDailyFood(const DailyFood& df)
{
    spdlog::debug("DailyModel::createDailyFood() {}", df.date);
    m_dbDaily->saveDailyFood(df);
}

bool DailyModel::doesDateExist(const std::string& date)
{
    spdlog::debug("DailyModel::doesDateExist() {}", date);
    return m_dbDaily->doesDateExist(date);
}

void DailyModel::setSelectedDate(const std::string& date)
{
    spdlog::debug("DailyModel::setSelectedDate() {}", date);
    m_dateString = date;
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

void DailyModel::addWeight(double weight)
{
    spdlog::debug("DailyModel::addWeight() {}", weight);
    DailyFood df = m_dbDaily->getDailyFood(m_dateString);
    df.weight = weight;
    m_dbDaily->updateDailyFood(df);
}

void DailyModel::addXrefDailyFood(const XrefDailyFood &xdf, int foodId)
{
    spdlog::debug("DailyModel::addDailyFood()");
    m_dbDaily->addXrefDailyFood(xdf);
    if (foodId != -1) {
        Food f = m_dbFood->getFood(foodId);
        m_dbFood->updatePopularity(f.id, f.popularity + 1);
    } else {
        spdlog::debug("DailyModel::addDailyFood() - recipe. Not bumping popularity");
    }
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

void DailyModel::loadGoal() {
    m_goal = m_dbGoal->getGoal();
}

int DailyModel::getGoalFatGrams()
{
    spdlog::debug("DailyModel::getGoalFatGrams() fatPercent: {} bmrCalories: {}", m_goal.fatPercent, m_goal.bmrCalories);
    int fatCalories = (m_goal.fatPercent * m_goal.bmrCalories) / 100;
    int grams = fatCalories / 9;
    spdlog::debug("DailyModel::getGoalFatGrams()fatCalories: {} grams: {}", fatCalories, grams);
    return grams;
}

int DailyModel::getGoalProteinGrams()
{
    int proteinCalories = m_goal.proteinPercent * m_goal.bmrCalories / 100;
    int grams = proteinCalories / 4;
    spdlog::debug("DailyModel::getGoalProteinGrams() {}", grams);
    return grams;
}

int DailyModel::getGoalCarbGrams()
{
    int carbCalories = m_goal.carbPercent * m_goal.bmrCalories / 100;
    int grams = carbCalories / 4;
    spdlog::debug("DailyModel::getGoalCarbGrams() {}", grams);
    return grams;
}

int DailyModel::getGoalCalories()
{
    spdlog::debug("DailyModel::getGoalCalories() {}", m_goal.bmrCalories);
    return m_goal.bmrCalories;
}