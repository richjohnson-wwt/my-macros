#include "DbFood.h"
#include <spdlog/spdlog.h>
#include <iostream>

DbFood::DbFood(const std::string &dbfile): DbBase(dbfile)
{
}

std::vector<Food> DbFood::getFoods()
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

Food DbFood::getFood(int id)
{
    spdlog::debug("Db::getFood");
    Food f;
    try
    {
        SQLite::Statement query(m_db, "SELECT * FROM Foods where food_id = ?");
        query.bind(1, id);
        f = foodHelper(query);
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    return f;
}

void DbFood::addFood(const Food &f) {
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
