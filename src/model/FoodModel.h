#ifndef FOOD_H
#define FOOD_H

#include "Db.h"
#include "MyMacroTypes.h"
#include <vector>


class IFoodModel {
public:
    virtual void setSelectedId(int id) = 0;
    virtual int getSelectedId() = 0;
    virtual std::vector<Food> getFoods() = 0;
};

class FoodModel : public IFoodModel {
private:
    Db m_db;
    int m_selectedId;

public:
    FoodModel();

    void setSelectedId(int idx) override;
    int getSelectedId() override;
    std::vector<Food> getFoods() override;

};

#endif // FOOD_H