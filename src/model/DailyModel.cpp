
#include "DailyModel.h"

#include <spdlog/spdlog.h>

DailyModel::DailyModel():m_db("../db/my-macro.sqlite3")
{
    
}

void DailyModel::setFoodSelectedId(int id)
{
    spdlog::info("DailyModel::setFoodSelectedId({})", id);
    m_selectedFoodId = id;
}

void DailyModel::setRecipeSelectedId(int id)
{
    spdlog::info("DailyModel::setRecipeSelectedId({})", id);
    m_selectedRecipeId = id;
}

std::vector<Food> DailyModel::getFoods()
{
    return m_db.getFoods();
}

std::vector<Recipe> DailyModel::getRecipes()
{
    return m_db.getRecipes();
}
