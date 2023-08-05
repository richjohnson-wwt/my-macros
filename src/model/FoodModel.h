#ifndef FOOD_H
#define FOOD_H

#include "FoodListModel.h"
#include "DbFood.h"
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
    
    virtual Food getFood() = 0;
    virtual std::vector<Unit> getUnits() = 0;
};

class FoodModel : public IFoodModel, public IFoodSubject {
private:
    DbFood *m_dbFood;
    FoodListModel *m_foodListModel;
    
    std::vector<IFoodObserver*> m_observers;

public:
    FoodModel(DbFood *db, FoodListModel *foodListModel);
    
    Food getFood() override;
    std::vector<Unit> getUnits() override;

    void attach(IFoodObserver* observer) override;
    void notify() override;

};

#endif // FOOD_H