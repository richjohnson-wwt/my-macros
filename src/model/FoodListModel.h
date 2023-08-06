#ifndef FOOD_LIST_MODEL_H
#define FOOD_LIST_MODEL_H

#include "DbFood.h"
#include "MyMacroTypes.h"
#include <vector>

class IFoodListModel {
public:
    virtual std::vector<Food> getFoods() = 0;
    virtual void setSelectedId(int id) = 0;
    virtual int getSelectedId() = 0;
    virtual Food getSelectedFood() = 0;
    
};

class IFoodListObserver {
public:
    virtual void update() = 0;
};

class IFoodListSubject {
public:
    virtual void attach(IFoodListObserver* observer) = 0;
    virtual void notify() = 0;
};

class FoodListModel : public IFoodListModel, public IFoodListSubject {
private:
    DbFood *m_dbFood;
    int m_selectedId;
    std::vector<IFoodListObserver*> m_observers;

public:
    FoodListModel(DbFood *db);
    std::vector<Food> getFoods() override;
    void setSelectedId(int idx) override;
    int getSelectedId() override;
    Food getSelectedFood() override;
    

    void attach(IFoodListObserver* observer) override;
    void notify() override;
};


#endif // FOOD_LIST_MODEL_H