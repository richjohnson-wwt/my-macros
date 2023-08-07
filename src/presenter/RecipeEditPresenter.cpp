#include "RecipeEditPresenter.h"
#include "../view/RecipeEditView.h"

#include <spdlog/spdlog.h>

RecipeEditPresenter::RecipeEditPresenter(IRecipeEditView *view, 
    IRecipeEditModel *model, 
    IRecipeListSubject *recipeListSubject,
    RecipePresenter *recipePresenter)
: m_recipeEditModel(model), m_recipeEditView(view), m_recipeListSubject(recipeListSubject), m_recipePresenter(recipePresenter)
{
}

void RecipeEditPresenter::initNewPage() {
    spdlog::debug("RecipeEditPresenter::update");
    Recipe recipe = m_recipeEditModel->getNewRecipe();
    m_recipeEditView->setRecipeId(std::to_string(recipe.id));
    m_recipeEditView->setRecipeName(recipe.name);
    m_recipeEditView->setRecipeDescription(recipe.description);
    m_recipeEditView->setRecipeInstructions(recipe.instructions);
    m_recipeEditView->setRecipeUrl(recipe.url);
    m_recipeEditView->setRecipeServings(std::to_string(recipe.servings));
    m_recipeEditView->setRecipeIngredients(m_recipeEditModel->getNewIngredients());
}

void RecipeEditPresenter::initEditPage() {
    spdlog::debug("RecipeEditPresenter::update");
    Recipe recipe = m_recipeEditModel->getEditRecipe();
    m_recipeEditView->setRecipeId(std::to_string(recipe.id));
    m_recipeEditView->setRecipeName(recipe.name);
    m_recipeEditView->setRecipeDescription(recipe.description);
    m_recipeEditView->setRecipeInstructions(recipe.instructions);
    m_recipeEditView->setRecipeUrl(recipe.url);
    m_recipeEditView->setRecipeServings(std::to_string(recipe.servings));
    m_recipeEditView->setRecipeIngredients(m_recipeEditModel->getEditIngredients());
}

void RecipeEditPresenter::onCancelNewRecipe()
{
    spdlog::debug("RecipeEditPresenter::onCancelNewRecipe");
    m_recipeEditModel->cancelNewRecipe();
    m_recipePresenter->onFocus();
}

void RecipeEditPresenter::onAddIngredient(double unitMultiplier)
{
    spdlog::debug("RecipeEditPresenter::onAddIngredient");
    
    m_recipeEditModel->addIngredient(unitMultiplier);
}

void RecipeEditPresenter::onSaveRecipe()
{
    spdlog::debug("RecipeEditPresenter::onSaveRecipe");
    Recipe recipe;
    // recipe.id = std::stoi(m_recipeEditView->getRecipeId());
    recipe.name = m_recipeEditView->getRecipeName();
    recipe.description = m_recipeEditView->getRecipeDescription();
    recipe.instructions = m_recipeEditView->getRecipeInstructions();
    recipe.url = m_recipeEditView->getRecipeUrl();

    // TODO save ingredients in model



    m_recipeEditModel->saveRecipe();
    m_recipePresenter->onFocus();
}

void RecipeEditPresenter::onDeleteIngredient()
{
    spdlog::debug("RecipeEditPresenter::onDeleteIngredient");
    m_recipeEditModel->deleteIngredient();
}

void RecipeEditPresenter::onSelectIngredient(int id)
{
    spdlog::debug("RecipeEditPresenter::onSelectIngredient");
    // m_recipeEditModel->selectIngredient(id);
}