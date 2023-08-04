#include "RecipePresenter.h"

#include <spdlog/spdlog.h>

RecipePresenter::RecipePresenter(ITopRecipeView *view, IRecipeModel *model, IRecipeListSubject *recipeListSubject)
: m_recipeModel(model), m_topRecipeView(view), m_recipeListSubject(recipeListSubject)
{
}

void RecipePresenter::postInit()
{
    spdlog::debug("RecipePresenter::postInit");
    m_recipeListSubject->attach(this);
}

void RecipePresenter::update() {
    spdlog::debug("RecipePresenter::update");
    int id = m_recipeModel->getSelectedId();
    Recipe recipe = m_recipeModel->getRecipeById(id);
    m_topRecipeView->setRecipeId(std::to_string(recipe.id));
}