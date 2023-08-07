
#include "RecipeModel.h"

#include <spdlog/spdlog.h>

RecipeModel::RecipeModel(DbRecipe *db, RecipeListModel *recipeListModel, RecipeCommonModel *commonModel)
:m_dbRecipe(db), m_recipeListModel(recipeListModel), m_commonModel(commonModel)
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

void RecipeModel::setInEditMode(bool inEditMode)
{
    spdlog::debug("FoodModel::setInEditMode {}", inEditMode);
    m_commonModel->setInEditMode(inEditMode);
}

bool RecipeModel::isInEditMode()
{
    return m_commonModel->isInEditMode();
}

Recipe RecipeModel::getRecipe()
{
    spdlog::debug("RecipeModel::getRecipe and selected is: {}", m_recipeListModel->getSelectedId());
    return m_dbRecipe->getRecipeById(m_recipeListModel->getSelectedId());

}

std::vector<Ingredient> RecipeModel::getIngredients()
{
    Recipe r = getRecipe();
    return m_dbRecipe->getIngredients(r);
}

void RecipeModel::newRecipe()
{
    spdlog::debug("RecipeModel::newRecipe");
    notify();
}

void RecipeModel::cancelNewRecipe()
{
    spdlog::debug("RecipeModel::cancelNewRecipe");
    notify();
}

void RecipeModel::addIngredient(double unitMultiplier)
{
    spdlog::debug("RecipeModel::addIngredient");
    int foodId = m_foodListModel->getSelectedId();
    Food f = m_dbRecipe->getFoodById(foodId);
    Unit u = m_dbRecipe->getUnit(f.unit_id);
    Ingredient i = Ingredient{f, unitMultiplier, u};
    // m_ingredientsUnderConstruction.push_back(i);
    notify();
}

void RecipeModel::saveRecipe()
{
    spdlog::debug("RecipeModel::saveRecipe");
    // m_dbRecipe->saveRecipe(m_recipeUnderConstruction, m_ingredientsUnderConstruction);
    // m_recipeUnderConstruction = Recipe{NEW_RECIPE_ID, "", "", "", "", 0};
    notify();
}

void RecipeModel::deleteRecipe()
{
    spdlog::debug("RecipeModel::deleteRecipe");
    m_dbRecipe->deleteRecipe(m_recipeListModel->getSelectedId());
    notify();
}

void RecipeModel::deleteIngredient()
{
    spdlog::debug("RecipeModel::deleteIngredient");
    // if (m_buildingRecipe){
        // m_ingredientsUnderConstruction.erase(m_ingredientsUnderConstruction.begin() + m_selectedIngredient);
    // } else {
        // TODO updating still needs to be done correctly
        // m_dbRecipe->deleteIngredient(m_recipeListModel->getSelectedId(), m_selectedIngredient);
    // }
    
    // notify();
}