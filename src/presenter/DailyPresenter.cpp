#include "DailyPresenter.h"

#include <spdlog/spdlog.h>

DailyPresenter::DailyPresenter(IDailyView *view, IDailyModel *model): m_dailyModel(model), m_dailyView(view)
{
}

void DailyPresenter::setActive()
{
    spdlog::info("DailyPresenter::setActive");

}

void DailyPresenter::onRecipeSelected(int id)
{
    spdlog::info("DailyPresenter::onRecipeSelected({})", id);
    m_dailyModel->setRecipeSelectedId(id);
}

void DailyPresenter::onRecipeBookPageChanged()
{
    spdlog::info("DailyPresenter::onFoodRecipeBookPageChanged()");
    m_dailyView->setRecipes(m_dailyModel->getRecipes());
    m_dailyView->setRecipeSelected(0);
}
