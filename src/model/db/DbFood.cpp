#include "DbFood.h"
#include <spdlog/spdlog.h>
#include <iostream>

DbFood::DbFood(const std::string &dbfile): DbBase(dbfile)
{
}

void DbFood::attach(IDbFoodObserver *observer)
{
    spdlog::debug("DbFood::attach");
    m_observers.push_back(observer);
}

void DbFood::notify()
{
    spdlog::debug("DbFood::notify");
    for (auto observer : m_observers)
    {
        observer->update();
    }
}

std::vector<Food> DbFood::getFoods()
{
    spdlog::debug("Db::getFoods");
    std::vector<Food> foods;
    try
    {
        SQLite::Statement query(m_db, "SELECT * FROM Foods ORDER BY popularity DESC");
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
            f.popularity = query.getColumn(8);
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

void DbFood::addNewFood(const Food &f) {
    spdlog::debug("DbConnection::addFood");
    try
    {
        SQLite::Statement query(m_db, "INSERT INTO Foods (name, fat, protein, carb, calories, quantity, unit_id, popularity) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        query.bind(1, f.name);
        query.bind(2, f.fat);
        query.bind(3, f.protein);
        query.bind(4, f.carb);
        query.bind(5, f.calories);
        query.bind(6, f.quantity);
        query.bind(7, f.unit_id);
        query.bind(8, f.popularity);
        query.exec();
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    notify();
}

std::vector<Unit> DbFood::getUnits()
{
    return DbBase::getUnits();
}

Unit DbFood::getUnit(const std::string &name)
{
    return DbBase::getUnit(name);
}

Unit DbFood::getUnit(int id)
{
    return DbBase::getUnit(id);
}

void DbFood::deleteFood(int foodId) {
    spdlog::debug("DbFood::deleteFood");
    try
    {
        SQLite::Statement query(m_db, "DELETE FROM Foods WHERE food_id = ?");
        query.bind(1, foodId);
        query.exec();
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    notify();
}

void DbFood::updatePopularity(int foodId, int newPopularity)
{
    spdlog::info("DbFood::updatePopularity {} {}", foodId, newPopularity);
    try
    {
        SQLite::Statement query(m_db, "UPDATE Foods SET popularity = ? WHERE food_id = ?");
        query.bind(1, newPopularity);
        query.bind(2, foodId);
        query.exec();
    } catch (SQLite::Exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void DbFood::updateFood(const Food &f) {
    spdlog::info("DbFood::updateFood {}", f.popularity);
    try
    {
        SQLite::Statement query(m_db, "UPDATE Foods SET name = ?, fat = ?, protein = ?, carb = ?, calories = ?, quantity = ?, unit_id = ?, popularity = ? WHERE food_id = ?");
        query.bind(1, f.name);
        query.bind(2, f.fat);
        query.bind(3, f.protein);
        query.bind(4, f.carb);
        query.bind(5, f.calories);
        query.bind(6, f.quantity);
        query.bind(7, f.unit_id);
        query.bind(8, f.popularity);
        query.bind(9, f.id);
        query.exec();
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    notify();
    
}