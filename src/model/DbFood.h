#ifndef DB_FOOD_H
#define DB_FOOD_H

#include "DbBase.h"

class DbFood : public DbBase {
public:
    DbFood(const std::string& dbfile);
    Food getFood(int id);
    std::vector<Food> getFoods();

    void addFood(const Food& f);
};


#endif // DB_FOOD_H