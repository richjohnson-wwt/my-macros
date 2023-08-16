#include "FoodEditPresenter.h"
#include "../model/food/FoodEditModel.h"
#include "../model/food/FoodListModel.h"

#include <spdlog/spdlog.h>

FoodEditPresenter::FoodEditPresenter(IFoodItemEditView *view, IFoodEditModel *model, IFoodListSubject *foodListSubject)
: m_foodModel(model), m_foodListSubject(foodListSubject), m_foodItemEditView(view)
{

}

void FoodEditPresenter::onSaveFood()
{
    spdlog::debug("FoodEditPresenter::onSaveFood");
    Food food;
    food.id = std::stoi(m_foodItemEditView->getFoodId());
    food.name = m_foodItemEditView->getFoodName();
    food.fat = std::stoi(m_foodItemEditView->getFoodFat());
    food.protein = std::stoi(m_foodItemEditView->getFoodProtein());
    food.carb = std::stoi(m_foodItemEditView->getFoodCarb());
    food.calories = std::stoi(m_foodItemEditView->getFoodCalories());
    food.quantity = std::stoi(m_foodItemEditView->getFoodQuantity());
    food.unit_id = m_foodItemEditView->getFoodUnitId();
    food.popularity = 1;
    m_foodModel->saveFood(food);
    m_foodListSubject->notify();
}

void FoodEditPresenter::onNewFoodCancel()
{
    spdlog::debug("FoodEditPresenter::onNewFoodCancel");
    m_foodModel->newFoodCancel();
}

void FoodEditPresenter::initNewPage()
{
    spdlog::debug("FoodEditPresenter::initNewPage");
    Food food = m_foodModel->getNewFood();
    std::vector<Unit> units = m_foodModel->getUnits();
    m_foodItemEditView->setFoodId(std::to_string(food.id));
    m_foodItemEditView->setFoodName(food.name);
    m_foodItemEditView->setFoodFat(std::to_string(food.fat));
    m_foodItemEditView->setFoodProtein(std::to_string(food.protein));
    m_foodItemEditView->setFoodCarb(std::to_string(food.carb));
    m_foodItemEditView->setFoodCalories(std::to_string(food.calories));
    m_foodItemEditView->setFoodQuantity(std::to_string(food.quantity));
    m_foodItemEditView->setFoodUnit(food.unit_id, units);
}

void FoodEditPresenter::initEditPage()
{
    spdlog::debug("FoodEditPresenter::initEditPage");
    Food food = m_foodModel->getEditFood();
    std::vector<Unit> units = m_foodModel->getUnits();
    m_foodItemEditView->setFoodId(std::to_string(food.id));
    m_foodItemEditView->setFoodName(food.name);
    m_foodItemEditView->setFoodFat(std::to_string(food.fat));
    m_foodItemEditView->setFoodProtein(std::to_string(food.protein));
    m_foodItemEditView->setFoodCarb(std::to_string(food.carb));
    m_foodItemEditView->setFoodCalories(std::to_string(food.calories));
    m_foodItemEditView->setFoodQuantity(std::to_string(food.quantity));
    m_foodItemEditView->setFoodUnit(food.unit_id, units);
}