#include "FoodEditModel.h"
#include <spdlog/spdlog.h>

FoodEditModel::FoodEditModel(DbFood *db, FoodListModel *foodListModel, FoodCommonModel *foodCommonModel)
:m_dbFood(db), m_foodListModel(foodListModel), m_foodCommonModel(foodCommonModel)
{
    
}

Food FoodEditModel::getNewFood()
{

    spdlog::info("FoodEditModel::getNewFood");
    return Food{NEW_FOOD_ID, "", 0, 0, 0, 0, 0, 0};
   
}

Food FoodEditModel::getEditFood()
{
    spdlog::info("FoodEditModel::getEditFood");
    return m_dbFood->getFood(m_foodListModel->getSelectedId());
}

Unit FoodEditModel::getUnit(const std::string &name)
{
    return m_dbFood->getUnit(name);
}

std::vector<Unit> FoodEditModel::getUnits()
{
    return m_dbFood->getUnits();
}

void FoodEditModel::saveFood(const Food &f)
{
    spdlog::debug("FoodEditModel::saveFood");
    m_foodCommonModel->setInEditMode(false);
    if (f.id == NEW_FOOD_ID)
    {
        m_dbFood->addNewFood(f);
    }
    else
    {
        m_dbFood->updateFood(f);
    }
}

void FoodEditModel::newFoodCancel()
{
    m_foodCommonModel->setInEditMode(false);

}