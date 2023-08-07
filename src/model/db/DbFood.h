#ifndef DB_FOOD_H
#define DB_FOOD_H

#include "DbBase.h"



class IDbFoodObserver {
public:
    virtual void update() = 0;
};

class IDbFoodSubject {
public:
    virtual void attach(IDbFoodObserver* observer) = 0;
    virtual void notify() = 0;
};

class DbFood : public DbBase, public IDbFoodSubject {
private:
    std::vector<IDbFoodObserver*> m_observers;

    void notify();

public:
    DbFood(const std::string& dbfile);

    void attach(IDbFoodObserver* observer);

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