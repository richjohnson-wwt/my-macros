
#include "RecipeModel.h"

#include <spdlog/spdlog.h>

RecipeModel::RecipeModel(RecipeListModel *recipeListModel)
:m_db("../db/my-macro.sqlite3"), m_recipeListModel(recipeListModel)
{
    
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

int RecipeModel::getSelectedId()
{
    spdlog::debug("RecipeModel::getSelectedId({})", m_selectedId);
    return m_recipeListModel->getSelectedId();
}

Recipe RecipeModel::getRecipeById(int id)
{
    return m_db.getRecipeById(id);
}
