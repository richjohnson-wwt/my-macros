#include "DbRecipe.h"
#include <spdlog/spdlog.h>
#include <iostream>

DbRecipe::DbRecipe(const std::string &dbfile, DbFood *dbFood): DbBase(dbfile), m_dbFood(dbFood)
{
}

std::vector<Recipe> DbRecipe::getRecipes()
{
    spdlog::debug("Db::getRecipes");
    std::vector<Recipe> recipes;
    try
    {
        SQLite::Statement query(m_db, "SELECT * FROM Recipes");
        while (query.executeStep())
        {
            Recipe r;
            r.id = query.getColumn(0);
            r.name = std::string(query.getColumn(1));
            r.description = std::string(query.getColumn(2));
            r.instructions = std::string(query.getColumn(3));
            r.url = std::string(query.getColumn(4));
            r.servings = query.getColumn(5);
            recipes.push_back(r);
        }
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    return recipes;
}

Recipe DbRecipe::getRecipeById(int id)
{
    spdlog::debug("Db::getRecipeById({})", id);
    Recipe recipe;
    try
    {
        SQLite::Statement query(m_db, "SELECT * FROM Recipes WHERE recipe_id = ?");
        query.bind(1, id);
        while (query.executeStep())
        {
            recipe.id = query.getColumn(0);
            recipe.name = std::string(query.getColumn(1));
            recipe.description = std::string(query.getColumn(2));
            recipe.instructions = std::string(query.getColumn(3));
            recipe.url = std::string(query.getColumn(4));
            recipe.servings = query.getColumn(5);
        }
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    return recipe;
}

std::vector<Ingredient> DbRecipe::getIngredients(const Recipe& r) {
    spdlog::debug("Db::getIngredients");
    std::vector<Ingredient> ingredients;
    try
    {
        SQLite::Statement query(m_db, "SELECT * FROM xref_recipe_foods WHERE recipe_id = ?");
        query.bind(1, r.id);
        while (query.executeStep())
        {
            Food f = m_dbFood->getFood(static_cast<int>(query.getColumn(1)));
            Ingredient i{f, query.getColumn(2), getUnit(static_cast<int>(query.getColumn(3)))};
            ingredients.push_back(i);
        }
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    return ingredients;

}
