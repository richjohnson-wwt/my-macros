#include "FoodPresenter.h"
#include "../model/food/FoodModel.h"

#include "../view/FoodItemView.h"

#include <spdlog/spdlog.h>

FoodPresenter::FoodPresenter(IFoodItemView *view, IFoodModel *model, IFoodListSubject *foodListSubject)
: m_foodModel(model), m_foodListSubject(foodListSubject), m_foodItemView(view)
{

}

void FoodPresenter::postInit() {
    m_foodListSubject->attach(this);
}

void FoodPresenter::update()
{
    spdlog::debug("FoodPresenter::update");
    Food food = m_foodModel->getFood();
    std::vector<Unit> units = m_foodModel->getUnits();
    m_foodItemView->setFoodId(std::to_string(food.id));
    m_foodItemView->setFoodName(food.name);
    m_foodItemView->setFoodFat(std::to_string(food.fat));
    m_foodItemView->setFoodProtein(std::to_string(food.protein));
    m_foodItemView->setFoodCarb(std::to_string(food.carb));
    m_foodItemView->setFoodCalories(std::to_string(food.calories));
    m_foodItemView->setFoodQuantity(std::to_string(food.quantity));
    m_foodItemView->setFoodUnit(food.unit_id, units);
}

void FoodPresenter::onFocus()
{
    spdlog::debug("FoodPresenter::onFocus");
    m_foodItemView->setButtonStatus(m_foodModel->isInEditMode());
}

void FoodPresenter::onDeleteFood()
{
    spdlog::debug("FoodPresenter::onDeleteFood");
    m_foodModel->deleteFood();
    m_foodListSubject->notify();
}

void FoodPresenter::onNewFood()
{
    spdlog::debug("FoodPresenter::onNewFood");
    m_foodModel->setInEditMode(true);
    m_foodItemView->insertNewPage(true);
}

void FoodPresenter::onEditFood()
{
    m_foodModel->setInEditMode(true);
    m_foodItemView->insertNewPage(false);
    
}