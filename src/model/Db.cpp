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