
#include "RecipeEditModel.h"

#include <spdlog/spdlog.h>

RecipeEditModel::RecipeEditModel(DbRecipe *db, RecipeListModel *recipeListModel, FoodListModel *foodListModel, RecipeCommonModel *recipeCommonModel)
:m_dbRecipe(db), m_recipeListModel(recipeListModel), m_foodListModel(foodListModel), m_recipeCommonModel(recipeCommonModel)
{
    
}

Recipe RecipeEditModel::getEditRecipe()
{
    spdlog::debug("RecipeEditModel::getEditRecipe");
    return m_dbRecipe->getRecipeById(m_recipeListModel->getSelectedId());
}

Recipe RecipeEditModel::getNewRecipe()
{
    spdlog::debug("RecipeEditModel::getNewRecipe");
    return Recipe{NEW_RECIPE_ID, "", "", "", "", 0};
}

std::vector<Ingredient> RecipeEditModel::getEditIngredients()
{
    spdlog::debug("RecipeEditModel::getEditIngredients");
    Recipe r = m_dbRecipe->getRecipeById(m_recipeListModel->getSelectedId());
    return m_dbRecipe->getIngredients(r);
}

std::vector<Ingredient> RecipeEditModel::getNewIngredients()
{
    spdlog::debug("RecipeEditModel::getNewIngredients");
    return std::vector<Ingredient>{};
}

void RecipeEditModel::cancelNewRecipe()
{
    spdlog::debug("RecipeEditModel::cancelNewRecipe");
    // m_recipeUnderConstruction = Recipe{NEW_RECIPE_ID, "", "", "", "", 0};
    // m_ingredientsUnderConstruction.clear();
    // notify();
    m_recipeCommonModel->setInEditMode(false);
}

void RecipeEditModel::addIngredient(double unitMultiplier)
{
    spdlog::debug("RecipeEditModel::addIngredient");
    int foodId = m_foodListModel->getSelectedId();
    Food f = m_dbRecipe->getFoodById(foodId);
    Unit u = m_dbRecipe->getUnit(f.unit_id);
    Ingredient i = Ingredient{f, unitMultiplier, u};
    // m_ingredientsUnderConstruction.push_back(i);
    // notify();
}

void RecipeEditModel::saveRecipe()
{
    spdlog::debug("RecipeEditModel::saveRecipe");
    m_recipeCommonModel->setInEditMode(false);
    // m_buildingRecipe = false;
    // m_dbRecipe->saveRecipe(m_recipeUnderConstruction, m_ingredientsUnderConstruction);
    // m_recipeUnderConstruction = Recipe{NEW_RECIPE_ID, "", "", "", "", 0};
    // m_ingredientsUnderConstruction.clear();
    // notify();
}

void RecipeEditModel::deleteIngredient()
{
    spdlog::debug("RecipeEditModel::deleteIngredient");
        
    // m_dbRecipe->deleteIngredient(m_recipeListModel->getSelectedId(), m_selectedIngredient);
    
    
    // notify();
}