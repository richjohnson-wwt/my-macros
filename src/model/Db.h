#ifndef DB_H
#define DB_H

#include "MyMacroTypes.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>

class Db {
private:
    SQLite::Database  m_db;

public:
    Db(const std::string& dbfile);
    ~Db();

    SQLite::Database *getDatabase();

    std::vector<Food> getFoods();
    std::vector<Recipe> getRecipes();
    Food getFoodById(int id);
    Recipe getRecipeById(int id);

    Unit getUnit(int id);
    Unit getUnit(const std::string& name);

    void addFood(const Food& f);
};

#endif // DB_H