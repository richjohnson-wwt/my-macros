#include "FoodModel.h"
#include <spdlog/spdlog.h>

FoodModel::FoodModel(DbFood *db, FoodListModel *foodListModel):m_dbFood(db), m_foodListModel(foodListModel)
{
    
}

void FoodModel::attach(IFoodObserver *observer)
{
    spdlog::debug("FoodModel::attach");
    m_observers.push_back(observer);
}

void FoodModel::notify()
{
    spdlog::info("FoodModel::notify");
    for (auto observer : m_observers)
    {
        observer->update();
    }
}

Food FoodModel::getFood()
{
    if (m_buildingFood){
        spdlog::info("FoodModel::getFood under construction");
        return m_foodUnderConstruction;
    } else {
        spdlog::info("FoodModel::getFood and selected is: {}", m_foodListModel->getSelectedId());
        return m_dbFood->getFood(m_foodListModel->getSelectedId());
    }
}

std::vector<Unit> FoodModel::getUnits()
{
    return m_dbFood->getUnits();
}

void FoodModel::saveFood(const Food &f)
{
    spdlog::info("FoodModel::saveFood");
    m_buildingFood = false;
    m_dbFood->saveFood(f);
    m_foodUnderConstruction = Food{NEW_FOOD_ID, "", 0, 0, 0, 0, 0, 0};
    notify();
}

void FoodModel::deleteFood()
{
    m_dbFood->deleteFood(m_foodListModel->getSelectedId());
    notify();
}

void FoodModel::newFood()
{
    m_buildingFood = true;
    m_foodUnderConstruction = Food{NEW_FOOD_ID, "", 0, 0, 0, 0, 0, 0};
    notify();
}

void FoodModel::newFoodCancel()
{
    m_buildingFood = false;
    m_foodUnderConstruction = Food{NEW_FOOD_ID, "", 0, 0, 0, 0, 0, 0};
    notify();
}