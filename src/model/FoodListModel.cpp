#include "FoodListModel.h"

#include <spdlog/spdlog.h>

FoodListModel::FoodListModel():m_db("../db/my-macro.sqlite3"), m_selectedId(1)
{
    spdlog::debug("FoodListModel::FoodListModel");
}

void FoodListModel::attach(IFoodListObserver *observer)
{
    spdlog::debug("FoodListModel::attach");
    m_observers.push_back(observer);
}

void FoodListModel::notify()
{
    spdlog::info("FoodListModel::notify");
    for (auto observer : m_observers)
    {
        observer->update();
    }
}

std::vector<Food> FoodListModel::getFoods()
{
    return m_db.getFoods();
}

void FoodListModel::setSelectedId(int id)
{
    spdlog::debug("FoodListModel::setSelectedId({})", id);
    m_selectedId = id;
    notify();
}

int FoodListModel::getSelectedId()
{
    spdlog::debug("FoodListModel::getSelectedId({})", m_selectedId);
    return m_selectedId;
}