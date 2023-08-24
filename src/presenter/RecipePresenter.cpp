#include "RecipePresenter.h"

#include <spdlog/spdlog.h>
#include <sstream>

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
    auto ingredients = m_recipeModel->getIngredients();
    m_recipeItemView->setRecipeIngredients(ingredients);

    CalculatedMacros cm = m_macroCalculator.calculateRecipeMacros(recipe.servings, ingredients, 1);
    m_recipeItemView->setMacroCalories(std::to_string(cm.calories));

    double percentFat = m_macroCalculator.calculateFatPercent(cm.fatGrams, cm.calories);
    double percentProtein = m_macroCalculator.calculateProteinPercent(cm.proteinGrams, cm.calories);
    double percentCarb = m_macroCalculator.calculateCarbPercent(cm.carbGrams, cm.calories);

    auto formattedFat = getFormattedValue(percentFat) + "% (" + getFormattedValue(cm.fatGrams) + "g)";
    auto formattedProtein = getFormattedValue(percentProtein) + "% (" + getFormattedValue(cm.proteinGrams) + "g)";
    auto formattedCarb = getFormattedValue(percentCarb) + "% (" + getFormattedValue(cm.carbGrams) + "g)";
    m_recipeItemView->setFatPercent(formattedFat);
    m_recipeItemView->setProteinPercent(formattedProtein);
    m_recipeItemView->setCarbPercent(formattedCarb);
}

std::string RecipePresenter::getFormattedValue(double v) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << v;
    return ss.str();
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
