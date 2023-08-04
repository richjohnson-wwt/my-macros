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
    return m_dbFood->getFood(m_foodListModel->getSelectedId());
}
