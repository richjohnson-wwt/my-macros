#ifndef FOOD_H
#define FOOD_H

#include "FoodListModel.h"
#include "FoodCommonModel.h"
#include "../db/DbFood.h"
#include "../MyMacroTypes.h"
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
    virtual Unit getFoodUnit() = 0;
    virtual Unit getUnit(const std::string& name) = 0;
    virtual std::vector<Unit> getUnits() = 0;;
    virtual void deleteFood() = 0;
    virtual bool isInEditMode() = 0;
    virtual void setInEditMode(bool inEditMode) = 0;

};

class FoodModel : public IFoodModel, public IFoodSubject {
private:
    DbFood *m_dbFood;
    FoodListModel *m_foodListModel;
    FoodCommonModel *m_foodCommonModel;
    
    std::vector<IFoodObserver*> m_observers;

public:
    FoodModel(DbFood *db, FoodListModel *foodListModel, FoodCommonModel *foodCommonModel);
    
    Food getFood() override;
    Unit getFoodUnit() override;
    Unit getUnit(const std::string& name) override;
    std::vector<Unit> getUnits() override;

    void attach(IFoodObserver* observer) override;
    void notify() override;

    void deleteFood() override;
    bool isInEditMode() override;
    void setInEditMode(bool inEditMode) override;

};

#endif // FOOD_H