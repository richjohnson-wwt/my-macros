#include "DailyPresenter.h"

#include <spdlog/spdlog.h>

DailyPresenter::DailyPresenter(IDailyView *view, IDailyModel *model, IRecipeModel *recipeModel)
: m_dailyModel(model), m_dailyView(view), m_recipeModel(recipeModel)
{
}

void DailyPresenter::setActive()
{
    spdlog::info("DailyPresenter::setActive");

}

void DailyPresenter::onRecipeSelected(int id)
{
    spdlog::info("DailyPresenter::onRecipeSelected({})", id);
    m_recipeModel->setSelectedId(id);
}

void DailyPresenter::onRecipeBookPageChanged()
{
    spdlog::info("DailyPresenter::onFoodRecipeBookPageChanged()");
    m_dailyView->setRecipes(m_recipeModel->getRecipes());
}
