#include "FoodListPresenter.h"

#include <spdlog/spdlog.h>

FoodListPresenter::FoodListPresenter(IFoodListView *view, IFoodModel *model)
: m_foodModel(model), m_foodListView(view)
{
}

void FoodListPresenter::onFoodSelected(int id)
{
    spdlog::debug("FoodListPresenter::onFoodSelected({})", id);
    m_foodModel->setSelectedId(id);
}

void FoodListPresenter::setActive()
{
    spdlog::debug("FoodListPresenter::setActive with id({})", m_foodModel->getSelectedId());
    m_foodListView->setFoods(m_foodModel->getFoods());
    m_foodListView->setSelected(m_foodModel->getSelectedId());
}
