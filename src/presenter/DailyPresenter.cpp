#include "DailyPresenter.h"

#include <spdlog/spdlog.h>

DailyPresenter::DailyPresenter(IDailyView *view, IDailyModel *model): m_dailyModel(model), m_dailyView(view)
{
}

void DailyPresenter::setActive()
{
    spdlog::info("DailyPresenter::setActive");
    m_dailyView->setFoods(m_dailyModel->getFoods());
    m_dailyView->setFoodSelected(0);
}

void DailyPresenter::onFoodSelected(int id)
{
    spdlog::info("DailyPresenter::onFoodSelected({})", id);
    m_dailyModel->setFoodSelectedId(id);
}

void DailyPresenter::onRecipeSelected(int id)
{
    spdlog::info("DailyPresenter::onRecipeSelected({})", id);
    m_dailyModel->setRecipeSelectedId(id);
}

void DailyPresenter::onFoodRecipeBookPageChanged(int bookPageIndex)
{
    spdlog::info("DailyPresenter::onFoodRecipeBookPageChanged({})", static_cast<int>(bookPageIndex));
    if (bookPageIndex == 0) {
        m_dailyView->setFoods(m_dailyModel->getFoods());
        m_dailyView->setFoodSelected(0);
    } else {
        m_dailyView->setRecipes(m_dailyModel->getRecipes());
        m_dailyView->setRecipeSelected(0);
    }
}
