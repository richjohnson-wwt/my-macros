#include "RecipePresenter.h"

#include <spdlog/spdlog.h>

RecipePresenter::RecipePresenter(IRecipeItemView *view, IRecipeModel *model, IRecipeListSubject *recipeListSubject)
: m_recipeModel(model), m_recipeItemView(view), m_recipeListSubject(recipeListSubject)
{
}

void RecipePresenter::postInit()
{
    spdlog::debug("RecipePresenter::postInit");
    m_recipeListSubject->attach(this);
}

void RecipePresenter::update() {
    spdlog::debug("RecipePresenter::update");
    Recipe recipe = m_recipeModel->getRecipe();
    m_recipeItemView->setRecipeId(std::to_string(recipe.id));
    m_recipeItemView->setRecipeName(recipe.name);
    m_recipeItemView->setRecipeDescription(recipe.description);
    m_recipeItemView->setRecipeInstructions(recipe.instructions);
    m_recipeItemView->setRecipeUrl(recipe.url);
    m_recipeItemView->setRecipeServings(std::to_string(recipe.servings));
    m_recipeItemView->setRecipeIngredients(m_recipeModel->getIngredients());
}

void RecipePresenter::onNewRecipe()
{
    spdlog::debug("RecipePresenter::onNewRecipe");
    m_recipeModel->setInEditMode(true);
    m_recipeItemView->insertNewPage(true);
}

void RecipePresenter::onEditRecipe()
{
    spdlog::debug("RecipePresenter::onEditRecipe");
    m_recipeModel->setInEditMode(true);
    m_recipeItemView->insertNewPage(false);
}

void RecipePresenter::onFocus()
{
    spdlog::debug("RecipePresenter::onFocus");
    m_recipeItemView->setButtonStatus(m_recipeModel->isInEditMode());
}

void RecipePresenter::onDeleteRecipe()
{
    spdlog::debug("RecipePresenter::onDeleteRecipe");

    m_recipeModel->deleteRecipe();
}

void RecipePresenter::onSelectIngredient(int id)
{
    spdlog::debug("RecipePresenter::onSelectIngredient");
    // m_recipeModel->selectIngredient(id);
}