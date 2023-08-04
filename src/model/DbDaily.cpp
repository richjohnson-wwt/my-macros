#include "DbDaily.h"

#include <spdlog/spdlog.h>
#include <iostream>

DbDaily::DbDaily(const std::string &dbfile): DbBase(dbfile)
{
}

DailyFood DbDaily::getDailyFood(const std::string& date) {
    DailyFood dailyFood;
    try {
        SQLite::Statement query(m_db, "SELECT * FROM daily_food where date = ?");
        query.bind(1, date);
        while (query.executeStep()) {
            dailyFood.id = query.getColumn(0);
            dailyFood.date = std::string(query.getColumn(1));
            dailyFood.dailyActivityBonusCalories = query.getColumn(2);
        }
    } catch (SQLite::Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return dailyFood;
}

std::vector<XrefDailyFood> DbDaily::getXrefDailyFoods(const DailyFood &df)
{
    std::vector<XrefDailyFood> xrefDailyFoods;
    try {
        SQLite::Statement query(m_db, "SELECT * FROM xref_daily_foods where daily_food_id = ?");
        query.bind(1, df.id);
        while (query.executeStep()) {
            XrefDailyFood xdf;
            xdf.id = query.getColumn(0);
            xdf.dailyFoodId = query.getColumn(1);
            xdf.name = std::string(query.getColumn(2));
            xdf.fat = query.getColumn(3);
            xdf.protein = query.getColumn(4);
            xdf.carb = query.getColumn(5);
            xdf.calories = query.getColumn(6);
            xrefDailyFoods.push_back(xdf);
        }
    } catch (SQLite::Exception &e) {
        std::cerr << e.what() << std::endl;
        spdlog::error(e.what());
    }
    return xrefDailyFoods;
}