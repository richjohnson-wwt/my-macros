#include "FoodListPresenter.h"

#include <spdlog/spdlog.h>

FoodListPresenter::FoodListPresenter(IFoodListView *view, IFoodListModel *model, IFoodSubject *foodSubject)
: m_foodListModel(model), m_foodListView(view), m_foodSubject(foodSubject)
{
}

void FoodListPresenter::postInit()
{
    spdlog::debug("FoodListPresenter::postInit");
    m_foodSubject->attach(this);
    update();
}

void FoodListPresenter::onFoodSelected(int id)
{
    spdlog::debug("FoodListPresenter::onFoodSelected({})", id);
    m_foodListModel->setSelectedId(id);
}

void FoodListPresenter::update()
{
    spdlog::debug("FoodListPresenter::update");
    m_foodListView->setFoods(m_foodListModel->getFoods());
    m_foodListView->setSelected(m_foodListModel->getSelectedId());
}