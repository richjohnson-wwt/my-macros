#include "FoodListPresenter.h"

#include <spdlog/spdlog.h>

FoodListPresenter::FoodListPresenter(IFoodListView *view, IFoodModel *model): m_foodModel(model), m_foodListView(view)
{
}

void FoodListPresenter::onFoodSelected(int id)
{
    spdlog::info("FoodListPresenter::onFoodSelected({})", id);
    m_foodModel->setSelectedId(id);
}

void FoodListPresenter::setActive()
{
    spdlog::info("FoodListPresenter::setActive");
    m_foodListView->setFoods(m_foodModel->getFoods());
    m_foodListView->setSelected(0);
}

void FoodListPresenter::onFoodBookPageChanged()
{
    spdlog::info("FoodListPresenter::onFoodBookPageChanged()");
    m_foodListView->setFoods(m_foodModel->getFoods());
}