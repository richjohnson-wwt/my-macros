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
            dailyFood.weight = query.getColumn(3);
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

std::vector<DailyFood> DbDaily::getDailyFoodByRange(const std::string& startDate, const std::string& endDate) {
   std::vector<DailyFood> dailyFoods;
    try {
        SQLite::Statement query(m_db, "SELECT * FROM daily_food where date between ? and ?");
        query.bind(1, startDate);
        query.bind(2, endDate);
        while (query.executeStep()) {
            DailyFood dailyFood;
            dailyFood.id = query.getColumn(0);
            dailyFood.date = std::string(query.getColumn(1));
            dailyFood.dailyActivityBonusCalories = query.getColumn(2);
            dailyFood.weight = query.getColumn(3);
            dailyFoods.push_back(dailyFood);
        }
    } catch (SQLite::Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return dailyFoods;

}

std::vector<XrefDailyFood> DbDaily::getXrefDailyFoodByDailyFood(const DailyFood& df) {
    std::vector<XrefDailyFood> xrefDailyFoods;
    try {
        SQLite::Statement query(m_db, "select * from xref_daily_foods where daily_food_id = ?");
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

bool DbDaily::doesDateExist(const std::string& today)
{
    bool exists = false;
    try {
        SQLite::Statement query(m_db, "SELECT * FROM daily_food where date = ?");
        query.bind(1, today);
        while (query.executeStep()) {
            exists = true;
        }
    } catch (SQLite::Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return exists;
}

void DbDaily::saveDailyFood(const DailyFood& df)
{
    try {
        SQLite::Statement query(m_db, "INSERT INTO daily_food (date, exercise_calorie_bonus, weight) VALUES (?, ?, ?)");
        query.bind(1, df.date);
        query.bind(2, df.dailyActivityBonusCalories);
        query.bind(3, df.weight);
        query.exec();
    } catch (SQLite::Exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void DbDaily::updateDailyFood(const DailyFood& df)
{
    try {
        SQLite::Statement query(m_db, "UPDATE daily_food SET exercise_calorie_bonus = ?, weight = ? WHERE id = ?");
        query.bind(1, df.dailyActivityBonusCalories);
        query.bind(2, df.weight);
        query.bind(3, df.id);
        query.exec();
    } catch (SQLite::Exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void DbDaily::addXrefDailyFood(const XrefDailyFood& xdf)
{
    try {
        SQLite::Statement query(m_db, "INSERT INTO xref_daily_foods (daily_food_id, name, fat, protein, carb, calories) VALUES (?, ?, ?, ?, ?, ?)");
        query.bind(1, xdf.dailyFoodId);
        query.bind(2, xdf.name);
        query.bind(3, xdf.fat);
        query.bind(4, xdf.protein);
        query.bind(5, xdf.carb);
        query.bind(6, xdf.calories);
        query.exec();
    } catch (SQLite::Exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void DbDaily::deleteXrefDailyFood(int id)
{
    try {
        SQLite::Statement query(m_db, "DELETE FROM xref_daily_foods WHERE id = ?");
        query.bind(1, id);
        query.exec();
    } catch (SQLite::Exception &e) {
        std::cerr << e.what() << std::endl;
    }
}