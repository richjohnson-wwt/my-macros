#ifndef DB_H
#define DB_H

#include "MyMacroTypes.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>

class Db {
private:
    SQLite::Database  m_db;

    Food foodHelper(SQLite::Statement &query);

public:
    Db(const std::string& dbfile);
    ~Db();

    SQLite::Database *getDatabase();

    Food getFood(int id);
    std::vector<Food> getFoods();
    std::vector<Recipe> getRecipes();

    Food getFoodById(int id);
    Recipe getRecipeById(int id);

    std::vector<Ingredient> getIngredients(const Recipe& r);

    Unit getUnit(int id);
    Unit getUnit(const std::string& name);

    void addFood(const Food& f);
};

#endif // DB_H