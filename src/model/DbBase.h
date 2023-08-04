#ifndef DB_H
#define DB_H

#include "MyMacroTypes.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>

class DbBase {
protected:
    SQLite::Database  m_db;

    Food foodHelper(SQLite::Statement &query);
    
public:
    DbBase(const std::string& dbfile);
    ~DbBase();

    Unit getUnit(int id);
    Unit getUnit(const std::string& name);

};

#endif // DB_H