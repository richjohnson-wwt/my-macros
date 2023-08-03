#ifndef FOOD_H
#define FOOD_H

#include "Db.h"
#include "MyMacroTypes.h"
#include <vector>

class IFoodObserver {
public:
    virtual void update() = 0;
};


class IFoodSubject {
public:
    virtual void attach(IFoodObserver* observer) = 0;
    virtual void notify() = 0;

};

class IFoodModel {
public:
    virtual void setSelectedId(int id) = 0;
    virtual int getSelectedId() = 0;
    virtual std::vector<Food> getFoods() = 0;
    virtual Food getFoodById(int id) = 0;
};

class FoodModel : public IFoodModel, public IFoodSubject {
private:
    Db m_db;
    int m_selectedId;
    std::vector<IFoodObserver*> m_observers;

public:
    FoodModel();

    void setSelectedId(int idx) override;
    int getSelectedId() override;
    std::vector<Food> getFoods() override;
    Food getFoodById(int id) override;

    void attach(IFoodObserver* observer) override;
    void notify() override;

};

#endif // FOOD_H