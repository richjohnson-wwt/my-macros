#ifndef FOOD_H
#define FOOD_H

#include "FoodListModel.h"
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
    
    virtual Food getFoodById(int id) = 0;
    virtual int getSelectedId() = 0;
};

class FoodModel : public IFoodModel, public IFoodSubject {
private:
    Db m_db;
    FoodListModel *m_foodListModel;
    
    std::vector<IFoodObserver*> m_observers;

public:
    FoodModel(FoodListModel *foodListModel);

    
    Food getFoodById(int id) override;
    int getSelectedId() override;

    void attach(IFoodObserver* observer) override;
    void notify() override;

};

#endif // FOOD_H