#include "DbBase.h"
#include <spdlog/spdlog.h>
#include <iostream>

DbBase::DbBase(const std::string &dbfile): m_db(dbfile, SQLite::OPEN_READWRITE)
{
}

DbBase::~DbBase()
{
}

Food DbBase::foodHelper(SQLite::Statement &query)
{
    Food f;
    while (query.executeStep())
    {
        f.id = query.getColumn(0);
        f.name = std::string(query.getColumn(1));
        f.fat = query.getColumn(2);
        f.protein = query.getColumn(3);
        f.carb = query.getColumn(4);
        f.calories = query.getColumn(5);
        f.quantity = query.getColumn(6);
        f.unit_id = query.getColumn(7);
    }
    return f;
}

Unit DbBase::getUnit(int id)
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

Unit DbBase::getUnit(const std::string &name)
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

