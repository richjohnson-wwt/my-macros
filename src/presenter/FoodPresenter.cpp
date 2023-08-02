#include "FoodPresenter.h"

#include <spdlog/spdlog.h>

FoodPresenter::FoodPresenter(IFoodView *view, IFoodModel *model): m_foodModel(model), m_foodView(view)
{
}

void FoodPresenter::onFoodSelected(int id)
{
    spdlog::info("FoodPresenter::onFoodSelected({})", id);
    m_foodModel->setSelectedId(id);
}

void FoodPresenter::setActive()
{
    spdlog::info("FoodPresenter::setActive");
    m_foodView->setFoods(m_foodModel->getFoods());
    m_foodView->setSelected(0);
}
