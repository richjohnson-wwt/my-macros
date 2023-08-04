
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

Recipe RecipeModel::getRecipe()
{
    spdlog::debug("RecipeModel::getRecipe and selected is: {}", m_recipeListModel->getSelectedId());
    return m_db.getRecipeById(m_recipeListModel->getSelectedId());
}

std::vector<Ingredient> RecipeModel::getIngredients()
{
    Recipe r = getRecipe();
    return m_db.getIngredients(r);
}