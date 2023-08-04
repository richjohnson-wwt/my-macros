#ifndef FOOD_LIST_MODEL_H
#define FOOD_LIST_MODEL_H

#include "Db.h"
#include "MyMacroTypes.h"
#include <vector>

class IFoodListModel {
public:
    virtual std::vector<Food> getFoods() = 0;
    virtual void setSelectedId(int id) = 0;
    virtual int getSelectedId() = 0;
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
    Db m_db;
    int m_selectedId;
    std::vector<IFoodListObserver*> m_observers;

public:
    FoodListModel();
    std::vector<Food> getFoods() override;
    void setSelectedId(int idx) override;
    int getSelectedId() override;

    void attach(IFoodListObserver* observer) override;
    void notify() override;
};


#endif // FOOD_LIST_MODEL_H