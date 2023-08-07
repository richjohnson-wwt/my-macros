#include "FoodListPresenter.h"

#include "../model/food/FoodListModel.h"
#include "../view/FoodListView.h"
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

void FoodListPresenter::onSearch(const std::string &searchText)
{
    spdlog::debug("FoodListPresenter::onSearch({})", searchText);
    std::vector<Food> foods = m_foodListModel->getFoods();
    std::vector<Food> filteredFoods;
    
    for (auto food : foods)
    {
        std::string foodName = food.name;
        std::transform(foodName.begin(), foodName.end(), foodName.begin(), ::tolower);
        int index;
        int pos = 0;
        while((index = foodName.find(std::string(searchText), pos)) != std::string::npos) {
            filteredFoods.push_back(food);
            break;
        }
    }
    m_foodListView->setFoods(filteredFoods);
}

void FoodListPresenter::onSearchCancel()
{
    spdlog::debug("FoodListPresenter::onSearchCancel");
    m_foodListView->setFoods(m_foodListModel->getFoods());
}