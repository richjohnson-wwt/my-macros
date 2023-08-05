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

void RecipePresenter::onNewRecipe()
{
    spdlog::info("RecipePresenter::onNewRecipe");
    m_recipeModel->newRecipe();
}

void RecipePresenter::onCancelNewRecipe()
{
    spdlog::info("RecipePresenter::onCancelNewRecipe");
    m_recipeModel->cancelNewRecipe();
}

void RecipePresenter::onAddIngredient(double unitMultiplier)
{
    spdlog::info("RecipePresenter::onAddIngredient");
    m_recipeModel->setRecipeName(m_topRecipeView->getRecipeName());
    m_recipeModel->setRecipeDescription(m_topRecipeView->getRecipeDescription());
    m_recipeModel->setRecipeInstructions(m_topRecipeView->getRecipeInstructions());
    m_recipeModel->setRecipeUrl(m_topRecipeView->getRecipeUrl());
    m_recipeModel->setRecipeServings(m_topRecipeView->getRecipeServings());
    
    m_recipeModel->addIngredient(unitMultiplier);
}

void RecipePresenter::onSaveRecipe()
{
    spdlog::info("RecipePresenter::onSaveRecipe");
    m_recipeModel->setRecipeName(m_topRecipeView->getRecipeName());
    m_recipeModel->setRecipeDescription(m_topRecipeView->getRecipeDescription());
    m_recipeModel->setRecipeInstructions(m_topRecipeView->getRecipeInstructions());
    m_recipeModel->setRecipeUrl(m_topRecipeView->getRecipeUrl());
    m_recipeModel->setRecipeServings(m_topRecipeView->getRecipeServings());

    m_recipeModel->saveRecipe();
}