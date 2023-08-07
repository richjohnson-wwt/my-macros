
#include "RecipeEditModel.h"

#include <spdlog/spdlog.h>

RecipeEditModel::RecipeEditModel(DbRecipe *db, RecipeListModel *recipeListModel, FoodListModel *foodListModel, RecipeCommonModel *recipeCommonModel)
:m_dbRecipe(db), m_recipeListModel(recipeListModel), m_foodListModel(foodListModel), m_recipeCommonModel(recipeCommonModel)
{
    
}

Recipe RecipeEditModel::getEditRecipe()
{
    spdlog::debug("RecipeEditModel::getEditRecipe");
    Recipe r = m_dbRecipe->getRecipeById(m_recipeListModel->getSelectedId());
    m_ingredientsUnderConstruction = m_dbRecipe->getIngredients(r);
    return r;
}

Recipe RecipeEditModel::getNewRecipe()
{
    spdlog::debug("RecipeEditModel::getNewRecipe");
    m_ingredientsUnderConstruction.clear();
    return Recipe{NEW_RECIPE_ID, "", "", "", "", 0};
}

std::vector<Ingredient> RecipeEditModel::getIngredients()
{
    spdlog::debug("RecipeEditModel::getIngredients");
    return m_ingredientsUnderConstruction;
}

void RecipeEditModel::cancelNewRecipe()
{
    spdlog::debug("RecipeEditModel::cancelNewRecipe");
    m_ingredientsUnderConstruction.clear();
    m_recipeCommonModel->setInEditMode(false);
}

void RecipeEditModel::addIngredient(double unitMultiplier)
{
    spdlog::debug("RecipeEditModel::addIngredient");
    int foodId = m_foodListModel->getSelectedId();
    Food f = m_dbRecipe->getFoodById(foodId);
    Unit u = m_dbRecipe->getUnit(f.unit_id);
    Ingredient i = Ingredient{f, unitMultiplier, u};
    m_ingredientsUnderConstruction.push_back(i);
}

void RecipeEditModel::saveRecipe(const Recipe& r)
{
    spdlog::debug("RecipeEditModel::saveRecipe");
    m_recipeCommonModel->setInEditMode(false);
    if (r.id == NEW_RECIPE_ID)
    {
        m_dbRecipe->addNewRecipe(r);
    }
    else
    {
        m_dbRecipe->updateRecipe(r);
    }
    m_dbRecipe->saveRecipe(r, m_ingredientsUnderConstruction);
    m_ingredientsUnderConstruction.clear();
}

void RecipeEditModel::deleteIngredient()
{
    spdlog::debug("RecipeEditModel::deleteIngredient");

    m_ingredientsUnderConstruction.erase(m_ingredientsUnderConstruction.begin() + m_selectedIngredient);
        
}

void RecipeEditModel::setSelectIngredient(int id)
{
    spdlog::debug("RecipeEditModel::setSelectIngredient");
    m_selectedIngredient = id;
}