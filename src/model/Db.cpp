#include "Db.h"
#include <spdlog/spdlog.h>
#include <iostream>

Db::Db(const std::string &dbfile): m_db(dbfile, SQLite::OPEN_READWRITE)
{
}

Db::~Db()
{
}

std::vector<Food> Db::getFoods()
{
    spdlog::debug("Db::getFoods");
    std::vector<Food> foods;
    try
    {
        SQLite::Statement query(m_db, "SELECT * FROM Foods");
        while (query.executeStep())
        {
            Food f;
            f.id = query.getColumn(0);
            f.name = std::string(query.getColumn(1));
            f.fat = query.getColumn(2);
            f.protein = query.getColumn(3);
            f.carb = query.getColumn(4);
            f.calories = query.getColumn(5);
            f.quantity = query.getColumn(6);
            f.unit_id = query.getColumn(7);
            foods.push_back(f);
        }
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    return foods;
}

std::vector<Recipe> Db::getRecipes()
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

Food Db::getFoodById(int id)
{
    spdlog::debug("Db::getFoodById({})", id);
    Food food;
    try
    {
        SQLite::Statement query(m_db, "SELECT * FROM Foods WHERE food_id = ?");
        query.bind(1, id);
        while (query.executeStep())
        {
            food.id = query.getColumn(0);
            food.name = std::string(query.getColumn(1));
            food.fat = query.getColumn(2);
            food.protein = query.getColumn(3);
            food.carb = query.getColumn(4);
            food.calories = query.getColumn(5);
            food.quantity = query.getColumn(6);
            food.unit_id = query.getColumn(7);
        }
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    return food;
}

Recipe Db::getRecipeById(int id)
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

Unit Db::getUnit(int id)
{
    spdlog::debug("DbConnection::getUnit");
    Unit u;
    try
    {
        SQLite::Statement query(m_db, "SELECT * FROM Units where unit_id = ?");
        query.bind(1, id);
        while (query.executeStep())
        {
            u.id = query.getColumn(0);
            u.name = std::string(query.getColumn(1));
        }
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    return u;
}

Unit Db::getUnit(const std::string &name)
{
    spdlog::debug("DbConnection::getUnit");
    Unit u{0, "NONE"};
    try
    {
        // auto formattedName = "%" + name + "%";
        SQLite::Statement query(m_db, "SELECT * FROM Units where name LIKE ?");
        query.bind(1, name);
        while (query.executeStep())
        {
            u.id = query.getColumn(0);
            u.name = std::string(query.getColumn(1));
        }
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    return u;
}

void Db::addFood(const Food &f) {
    spdlog::debug("DbConnection::addFood");
    try
    {
        SQLite::Statement query(m_db, "INSERT INTO Foods (name, fat, protein, carb, calories, quantity, unit_id) VALUES (?, ?, ?, ?, ?, ?, ?)");
        query.bind(1, f.name);
        query.bind(2, f.fat);
        query.bind(3, f.protein);
        query.bind(4, f.carb);
        query.bind(5, f.calories);
        query.bind(6, f.quantity);
        query.bind(7, f.unit_id);
        query.exec();
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
}