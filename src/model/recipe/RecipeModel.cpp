
#include "RecipeModel.h"

#include <spdlog/spdlog.h>

RecipeModel::RecipeModel(DbRecipe *db, RecipeListModel *recipeListModel, FoodListModel *foodListModel)
:m_dbRecipe(db), m_recipeListModel(recipeListModel), m_buildingRecipe(false), m_foodListModel(foodListModel)
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

Recipe RecipeModel::getRecipe()
{
    if (m_buildingRecipe){
        spdlog::info("RecipeModel::getRecipe under construction");
        return m_recipeUnderConstruction;
    } else {
        spdlog::info("RecipeModel::getRecipe and selected is: {}", m_recipeListModel->getSelectedId());
        return m_dbRecipe->getRecipeById(m_recipeListModel->getSelectedId());
    }
}

std::vector<Ingredient> RecipeModel::getIngredients()
{
    if (m_buildingRecipe){
        spdlog::debug("RecipeModel::getIngredients under construction");
        return m_ingredientsUnderConstruction;
    } else {
        Recipe r = getRecipe();
        return m_dbRecipe->getIngredients(r);
    }
}

void RecipeModel::newRecipe()
{
    spdlog::debug("RecipeModel::newRecipe");
    m_buildingRecipe = true;
    m_recipeUnderConstruction = Recipe{NEW_RECIPE_ID, "", "", "", "", 0};
    notify();
}

void RecipeModel::cancelNewRecipe()
{
    spdlog::debug("RecipeModel::cancelNewRecipe");
    m_buildingRecipe = false;
    m_recipeUnderConstruction = Recipe{NEW_RECIPE_ID, "", "", "", "", 0};
    m_ingredientsUnderConstruction.clear();
    notify();
}

void RecipeModel::addIngredient(double unitMultiplier)
{
    spdlog::debug("RecipeModel::addIngredient");
    int foodId = m_foodListModel->getSelectedId();
    Food f = m_dbRecipe->getFoodById(foodId);
    Unit u = m_dbRecipe->getUnit(f.unit_id);
    Ingredient i = Ingredient{f, unitMultiplier, u};
    m_ingredientsUnderConstruction.push_back(i);
    notify();
}

void RecipeModel::saveRecipe()
{
    spdlog::debug("RecipeModel::saveRecipe");
    m_buildingRecipe = false;
    m_dbRecipe->saveRecipe(m_recipeUnderConstruction, m_ingredientsUnderConstruction);
    m_recipeUnderConstruction = Recipe{NEW_RECIPE_ID, "", "", "", "", 0};
    m_ingredientsUnderConstruction.clear();
    notify();
}

void RecipeModel::deleteRecipe()
{
    spdlog::debug("RecipeModel::deleteRecipe");
    m_dbRecipe->deleteRecipe(m_recipeListModel->getSelectedId());
    notify();
}

void RecipeModel::setRecipeName(const std::string &name)
{
    m_recipeUnderConstruction.name = name;
}

void RecipeModel::setRecipeDescription(const std::string &description)
{
    m_recipeUnderConstruction.description = description;
}

void RecipeModel::setRecipeUrl(const std::string &url)
{
    m_recipeUnderConstruction.url = url;
}

void RecipeModel::setRecipeServings(const std::string &servings)
{
    m_recipeUnderConstruction.servings = std::stoi(servings);
}

void RecipeModel::setRecipeInstructions(const std::string &instructions)
{
    m_recipeUnderConstruction.instructions = instructions;
}

void RecipeModel::selectIngredient(int id)
{
    m_selectedIngredient = id;
}

void RecipeModel::deleteIngredient()
{
    spdlog::debug("RecipeModel::deleteIngredient");
    if (m_buildingRecipe){
        m_ingredientsUnderConstruction.erase(m_ingredientsUnderConstruction.begin() + m_selectedIngredient);
    } else {
        // TODO updating still needs to be done correctly
        m_dbRecipe->deleteIngredient(m_recipeListModel->getSelectedId(), m_selectedIngredient);
    }
    
    notify();
}