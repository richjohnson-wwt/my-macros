
#include "RecipeModel.h"

#include <spdlog/spdlog.h>

RecipeModel::RecipeModel():m_db("../db/my-macro.sqlite3"), m_selectedId(0)
{
    
}


std::vector<Recipe> RecipeModel::getRecipes()
{
    return m_db.getRecipes();
}

void RecipeModel::setSelectedId(int id)
{
    spdlog::debug("RecipeModel::setSelectedId({})", id);
    m_selectedId = id;
    notify();
}

int RecipeModel::getSelectedId()
{
    spdlog::debug("RecipeModel::getSelectedId({})", m_selectedId);
    return m_selectedId;
}
Recipe RecipeModel::getRecipeById(int id)
{
    return m_db.getRecipeById(id);
}

void RecipeModel::attach(IRecipeObserver *observer)
{
    spdlog::debug("RecipeModel::attach");
    m_observers.push_back(observer);
}

void RecipeModel::notify()
{
    for (auto observer : m_observers)
    {
        observer->update();
    }
}