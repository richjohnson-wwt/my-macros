#include "DbRecipe.h"
#include <spdlog/spdlog.h>
#include <iostream>

DbRecipe::DbRecipe(const std::string &dbfile, DbFood *dbFood): DbBase(dbfile), m_dbFood(dbFood)
{
}

Recipe DbRecipe::recipeHelper(SQLite::Statement &query)
{
    Recipe r;
    while (query.executeStep())
    {
        r.id = query.getColumn(0);
        r.name = std::string(query.getColumn(1));
        r.description = std::string(query.getColumn(2));
        r.instructions = std::string(query.getColumn(3));
        r.url = std::string(query.getColumn(4));
        r.servings = query.getColumn(5);
    }
    return r;
}

std::vector<Recipe> DbRecipe::getRecipes()
{
    spdlog::debug("DbRecipe::getRecipes");
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
    spdlog::debug("DbRecipe::getRecipeById({})", id);
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

Recipe DbRecipe::getRecipe(const std::string& name) {
    spdlog::debug("DbRecipe::getRecipe by name");
    Recipe r;
    try
    {
        auto formattedName = "%" + name + "%";
        SQLite::Statement query(m_db, "SELECT * FROM Recipes where name LIKE ?");
        query.bind(1, formattedName);
        r = recipeHelper(query);
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    return r;
}

std::vector<Ingredient> DbRecipe::getIngredients(const Recipe& r) {
    spdlog::debug("DbRecipe::getIngredients");
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

Food DbRecipe::getFoodById(int id)
{
    return m_dbFood->getFood(id);
}

void DbRecipe::saveRecipe(const Recipe &r, std::vector<Ingredient> foods)
{
    spdlog::debug("DbRecipe::addRecipe");
    try
    {
        SQLite::Transaction transaction(m_db);

        SQLite::Statement query(m_db, "INSERT INTO Recipes (name, description, instructions, url, servings) VALUES (?, ?, ?, ?, ?)");
        query.bind(1, r.name);
        query.bind(2, r.description);
        query.bind(3, r.instructions);
        query.bind(4, r.url);
        query.bind(5, r.servings);
        query.exec();

        Recipe newRecipe = getRecipe(r.name);
        int newRecipeId = newRecipe.id;
        
        for (const auto &f : foods)
        {
            SQLite::Statement query2(m_db, "INSERT INTO xref_recipe_foods (recipe_id, food_id, amount, unit_id) VALUES (?, ?, ?, ?)");
            query2.bind(1, newRecipeId);
            query2.bind(2, f.food.id);
            query2.bind(3, f.unitMultiplier);
            query2.bind(4, f.unit.id);
            query2.exec();
        }
        transaction.commit();
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
}
