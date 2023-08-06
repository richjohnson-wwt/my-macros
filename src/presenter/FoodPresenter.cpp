#include "FoodPresenter.h"


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

void FoodPresenter::onDeleteFood()
{
    spdlog::debug("FoodPresenter::onDeleteFood");
    m_foodModel->deleteFood();
    m_foodListSubject->notify();
}

// void FoodPresenter::onSaveFood()
// {
//     spdlog::debug("FoodPresenter::onSaveFood");
//     // Food food;
//     // food.id = std::stoi(m_foodItemView->getFoodId());
//     // food.name = m_foodItemView->getFoodName();
//     // food.fat = std::stoi(m_foodItemView->getFoodFat());
//     // food.protein = std::stoi(m_foodItemView->getFoodProtein());
//     // food.carb = std::stoi(m_foodItemView->getFoodCarb());
//     // food.calories = std::stoi(m_foodItemView->getFoodCalories());
//     // food.quantity = std::stoi(m_foodItemView->getFoodQuantity());
//     // food.unit_id = m_foodItemView->getFoodUnitId();
//     // m_foodModel->saveFood(food);
//     // m_foodListSubject->notify();
// }

void FoodPresenter::onNewFood()
{
    spdlog::debug("FoodPresenter::onNewFood");
    m_foodItemView->insertNewPage(true);
}

// void FoodPresenter::onNewFoodCancel()
// {
//     spdlog::debug("FoodPresenter::onNewFoodCancel");
//     m_foodModel->newFoodCancel();
// }

void FoodPresenter::onEditFood()
{
    m_foodItemView->insertNewPage(false);
    
}