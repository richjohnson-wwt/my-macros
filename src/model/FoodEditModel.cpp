#include "FoodEditModel.h"
#include <spdlog/spdlog.h>

FoodEditModel::FoodEditModel(DbFood *db, FoodListModel *foodListModel)
:m_dbFood(db), m_foodListModel(foodListModel)
{
    
}

Food FoodEditModel::getNewFood()
{

    spdlog::info("FoodEditModel::getNewFood");
    return Food{NEW_FOOD_ID, "", 0, 0, 0, 0, 0, 0};
   
}

Food FoodEditModel::getEditFood()
{
    spdlog::info("FoodEditModel::getEditFood under construction");
    return m_dbFood->getFood(m_foodListModel->getSelectedId());
}

Unit FoodEditModel::getUnit(const std::string &name)
{
    return m_dbFood->getUnit(name);
}

Unit FoodEditModel::getFoodUnit()
{
    return m_dbFood->getUnit(m_foodUnderConstruction.unit_id);
}

std::vector<Unit> FoodEditModel::getUnits()
{
    return m_dbFood->getUnits();
}

void FoodEditModel::saveFood(const Food &f)
{
    spdlog::info("FoodEditModel::saveFood");
    m_dbFood->saveFood(f);
}

void FoodEditModel::newFoodCancel()
{

}