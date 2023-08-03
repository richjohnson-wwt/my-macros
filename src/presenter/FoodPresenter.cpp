#include "FoodPresenter.h"


#include <spdlog/spdlog.h>

FoodPresenter::FoodPresenter(ITopFoodView *view, IFoodModel *model, IFoodSubject *foodSubject)
: m_foodModel(model), m_topFoodView(view), m_foodSubject(foodSubject)
{

}

void FoodPresenter::postInit() {
    m_foodSubject->attach(this);
}

void FoodPresenter::update()
{
    spdlog::debug("FoodPresenter::update");
    int id = m_foodModel->getSelectedId();
    Food food = m_foodModel->getFoodById(id);
    m_topFoodView->setFoodId(std::to_string(food.id));
}
