#include "FoodPresenter.h"

#include <spdlog/spdlog.h>

FoodPresenter::FoodPresenter(ITopFoodView *view, IFoodModel *model): m_foodModel(model), m_topFoodView(view)
{
}

void FoodPresenter::setActive()
{
    spdlog::info("FoodPresenter::setActive");
    
}
