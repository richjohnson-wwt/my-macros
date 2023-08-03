#include "FoodModel.h"
#include <spdlog/spdlog.h>

FoodModel::FoodModel():m_db("../db/my-macro.sqlite3"), m_selectedId(0)
{
    
}

void FoodModel::setSelectedId(int id)
{
    spdlog::debug("FoodModel::setSelectedId({})", id);
    m_selectedId = id;
    notify();
}

int FoodModel::getSelectedId()
{
    spdlog::debug("FoodModel::getSelectedId({})", m_selectedId);
    return m_selectedId;
}

std::vector<Food> FoodModel::getFoods()
{
    return m_db.getFoods();
}

Food FoodModel::getFoodById(int id)
{
    return m_db.getFoodById(id);
}

void FoodModel::attach(IFoodObserver *observer)
{
    spdlog::debug("FoodModel::attach");
    m_observers.push_back(observer);
}

void FoodModel::notify()
{
    for (auto observer : m_observers)
    {
        observer->update();
    }
}
