#include "FoodModel.h"
#include <spdlog/spdlog.h>

FoodModel::FoodModel(DbFood *db, FoodListModel *foodListModel)
:m_dbFood(db), m_foodListModel(foodListModel)
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
    spdlog::info("FoodModel::getFood and selected is: {}", m_foodListModel->getSelectedId());
    return m_dbFood->getFood(m_foodListModel->getSelectedId());
}

Unit FoodModel::getUnit(const std::string &name)
{
    return m_dbFood->getUnit(name);
}

Unit FoodModel::getFoodUnit()
{
    return m_dbFood->getUnit(m_dbFood->getFood(m_foodListModel->getSelectedId()).unit_id);
}

std::vector<Unit> FoodModel::getUnits()
{
    return m_dbFood->getUnits();
}

void FoodModel::deleteFood()
{
    m_dbFood->deleteFood(m_foodListModel->getSelectedId());
    notify();
}
