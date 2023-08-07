#ifndef DB_FOOD_H
#define DB_FOOD_H

#include "DbBase.h"

class DbFood : public DbBase {
public:
    DbFood(const std::string& dbfile);
    Food getFood(int id);
    std::vector<Food> getFoods();

    void addNewFood(const Food& f);
    std::vector<Unit> getUnits();
    Unit getUnit(const std::string& name);
    Unit getUnit(int id);

    void updateFood(const Food& f);

    void deleteFood(int id);
};


#endif // DB_FOOD_H