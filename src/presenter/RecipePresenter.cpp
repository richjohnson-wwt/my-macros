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
    spdlog::info("RecipePresenter::update");
    Recipe recipe = m_recipeModel->getRecipe();
    m_topRecipeView->setRecipeId(std::to_string(recipe.id));
    m_topRecipeView->setRecipeName(recipe.name);
    m_topRecipeView->setRecipeDescription(recipe.description);
    m_topRecipeView->setRecipeInstructions(recipe.instructions);
    m_topRecipeView->setRecipeUrl(recipe.url);
    m_topRecipeView->setRecipeServings(std::to_string(recipe.servings));
    m_topRecipeView->setRecipeIngredients(m_recipeModel->getIngredients());
}