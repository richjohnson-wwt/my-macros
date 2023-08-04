#include "FoodPresenter.h"


#include <spdlog/spdlog.h>

FoodPresenter::FoodPresenter(IFoodItemView *view, IFoodModel *model, IFoodListSubject *foodListSubject)
: m_foodModel(model), m_foodItemView(view), m_foodListSubject(foodListSubject)
{

}

void FoodPresenter::postInit() {
    m_foodListSubject->attach(this);
}

void FoodPresenter::update()
{
    spdlog::debug("FoodPresenter::update");
    int id = m_foodModel->getSelectedId();
    Food food = m_foodModel->getFoodById(id);
    m_foodItemView->setFoodId(std::to_string(food.id));
}
