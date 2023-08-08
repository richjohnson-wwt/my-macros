
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
    m_ingredientsOriginal = m_ingredientsUnderConstruction;
    return r;
}

Recipe RecipeEditModel::getNewRecipe()
{
    spdlog::debug("RecipeEditModel::getNewRecipe");
    m_ingredientsUnderConstruction.clear();
    m_ingredientsOriginal.clear();
    return Recipe{NEW_RECIPE_ID, "", "", "", "", 0};
}

std::vector<Ingredient> RecipeEditModel::getIngredients()
{
    spdlog::info("RecipeEditModel::getIngredients size {}", m_ingredientsUnderConstruction.size());
    return m_ingredientsUnderConstruction;
}

void RecipeEditModel::cancelNewRecipe()
{
    spdlog::debug("RecipeEditModel::cancelNewRecipe");
    m_ingredientsUnderConstruction.clear();
    m_ingredientsOriginal.clear();
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
    spdlog::info("RecipeEditModel::saveRecipe size: {}", m_ingredientsUnderConstruction.size());
    m_recipeCommonModel->setInEditMode(false);
    if (r.id == NEW_RECIPE_ID)
    {
        m_dbRecipe->saveRecipe(r, m_ingredientsUnderConstruction);
    }
    else
    {
        // Delete and then add due to ingredients
        for (auto i : m_ingredientsOriginal) {
            m_dbRecipe->deleteIngredient(r.id, i.food.id);
        }
        m_dbRecipe->deleteRecipe(r.id);

        m_dbRecipe->saveRecipe(r, m_ingredientsUnderConstruction);
    }
    m_ingredientsUnderConstruction.clear();
}

void RecipeEditModel::deleteIngredient()
{
    spdlog::debug("RecipeEditModel::deleteIngredient {}", m_selectedIngredient);
    std::vector<Ingredient>::iterator it;
    for (it = m_ingredientsUnderConstruction.begin(); it != m_ingredientsUnderConstruction.end(); it++)
    {
        if (it->food.id == m_selectedIngredient)
        {
            m_ingredientsUnderConstruction.erase(it);
            break;
        }
    }
}

void RecipeEditModel::setSelectIngredient(int id)
{
    spdlog::debug("RecipeEditModel::setSelectIngredient");
    m_selectedIngredient = id;
}