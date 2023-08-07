#ifndef FOOD_EDIT_MODEL_H
#define FOOD_EDIT_MODEL_H

#include "FoodListModel.h"
#include "FoodCommonModel.h"
#include "DbFood.h"
#include "MyMacroTypes.h"
#include <vector>

class IFoodEditModel {
public:
    
    virtual Food getNewFood() = 0;
    virtual Food getEditFood() = 0;
    virtual Unit getUnit(const std::string& name) = 0;
    virtual std::vector<Unit> getUnits() = 0;
    virtual void saveFood(const Food& f) = 0;
    virtual void newFoodCancel() = 0;
};

class FoodEditModel : public IFoodEditModel {
private:
    DbFood *m_dbFood;
    FoodListModel *m_foodListModel;
    FoodCommonModel *m_foodCommonModel;
    
    const int NEW_FOOD_ID = -1;

public:
    FoodEditModel(DbFood *db, FoodListModel *foodListModel, FoodCommonModel *foodCommonModel);
    
    Food getNewFood() override;
    Food getEditFood() override;
    Unit getUnit(const std::string& name) override;
    std::vector<Unit> getUnits() override;

    void saveFood(const Food& f) override;
    void newFoodCancel() override;

};

#endif // FOOD_EDIT_MODEL_H