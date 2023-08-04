#include "RecipeListModel.h"

#include <spdlog/spdlog.h>

RecipeListModel::RecipeListModel():m_db("../db/my-macro.sqlite3"), m_selectedId(1)
{
    spdlog::debug("RecipeListModel::RecipeListModel");
}

void RecipeListModel::attach(IRecipeListObserver *observer)
{
    spdlog::debug("RecipeListModel::attach");
    m_observers.push_back(observer);
}

void RecipeListModel::notify()
{
    spdlog::info("RecipeListModel::notify");
    for (auto observer : m_observers)
    {
        observer->update();
    }
}

std::vector<Recipe> RecipeListModel::getRecipes()
{
    return m_db.getRecipes();
}

void RecipeListModel::setSelectedId(int id)
{
    spdlog::debug("RecipeListModel::setSelectedId({})", id);
    m_selectedId = id;
    notify();
}

int RecipeListModel::getSelectedId()
{
    spdlog::debug("RecipeListModel::getSelectedId({})", m_selectedId);
    return m_selectedId;
}