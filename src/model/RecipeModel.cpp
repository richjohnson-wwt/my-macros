
#include "RecipeModel.h"

#include <spdlog/spdlog.h>

RecipeModel::RecipeModel():m_db("../db/my-macro.sqlite3")
{
    
}


std::vector<Recipe> RecipeModel::getRecipes()
{
    return m_db.getRecipes();
}

void RecipeModel::setSelectedId(int id)
{
    spdlog::info("RecipeModel::setSelectedId({})", id);
    m_selectedId = id;
}

int RecipeModel::getSelectedId()
{
    spdlog::info("RecipeModel::getSelectedId({})", m_selectedId);
    return m_selectedId;
}