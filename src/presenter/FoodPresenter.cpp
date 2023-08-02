#include "FoodPresenter.h"

#include <spdlog/spdlog.h>

FoodPresenter::FoodPresenter(IFoodView *view, IFoodModel *model): m_foodModel(model), m_foodView(view)
{
}

void FoodPresenter::setActive()
{
    spdlog::info("FoodPresenter::setActive");
}
