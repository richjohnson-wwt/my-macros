#include "FoodModel.h"

#include <spdlog/spdlog.h>

FoodModel::FoodModel():m_db("../db/my-macro.sqlite3"), m_selectedId(0)
{
    
}

void FoodModel::setSelectedId(int id)
{
    spdlog::info("FoodModel::setSelectedId({})", id);
    m_selectedId = id;
}

int FoodModel::getSelectedId()
{
    spdlog::info("FoodModel::getSelectedId({})", m_selectedId);
    return m_selectedId;
}

std::vector<Food> FoodModel::getFoods()
{
    return m_db.getFoods();
}

