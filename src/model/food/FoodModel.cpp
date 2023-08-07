#include "FoodModel.h"
#include <spdlog/spdlog.h>

FoodModel::FoodModel(DbFood *db, FoodListModel *foodListModel, FoodCommonModel *foodCommonModel)
:m_dbFood(db), m_foodListModel(foodListModel), m_foodCommonModel(foodCommonModel)
{
    
}

void FoodModel::attach(IFoodObserver *observer)
{
    spdlog::debug("FoodModel::attach");
    m_observers.push_back(observer);
}

void FoodModel::notify()
{
    spdlog::debug("FoodModel::notify");
    for (auto observer : m_observers)
    {
        observer->update();
    }
}

void FoodModel::setInEditMode(bool inEditMode)
{
    spdlog::debug("FoodModel::setInEditMode {}", inEditMode);
    m_foodCommonModel->setInEditMode(inEditMode);
}

bool FoodModel::isInEditMode()
{
    return m_foodCommonModel->isInEditMode();
}

Food FoodModel::getFood()
{
    spdlog::debug("FoodModel::getFood and selected is: {}", m_foodListModel->getSelectedId());
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
