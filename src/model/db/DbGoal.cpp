#include "DbGoal.h"

#include "../MyMacroTypes.h"
#include <spdlog/spdlog.h>
#include <iostream>

DbGoal::DbGoal(const std::string& dbfile) : DbBase(dbfile)
{
}

Goal DbGoal::getGoal() {
    Goal goal;
    try
    {
        SQLite::Statement query(m_db, "SELECT * FROM Goal");
        while (query.executeStep())
        {
            goal.id = query.getColumn(0);
            goal.startDate = std::string(query.getColumn(1));
            goal.targetWeight = query.getColumn(2);
            goal.bmrCalories = query.getColumn(3);
            goal.fatPercent = query.getColumn(4);
            goal.proteinPercent = query.getColumn(5);
            goal.carbPercent = query.getColumn(6);
        }
    }
    catch (SQLite::Exception &e)
    {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    return goal;
}