#include "FoodModel.h"
#include <spdlog/spdlog.h>

FoodModel::FoodModel(FoodListModel *foodListModel):m_db("../db/my-macro.sqlite3"), m_foodListModel(foodListModel)
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
    return m_db.getFoodById(m_foodListModel->getSelectedId());
}
