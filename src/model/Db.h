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
};

#endif // DB_H