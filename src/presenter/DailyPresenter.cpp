#include "DailyPresenter.h"

#include <spdlog/spdlog.h>

DailyPresenter::DailyPresenter(IDailyView *view, IDailyModel *model, IRecipeModel *recipeModel)
: m_dailyModel(model), m_dailyView(view), m_recipeModel(recipeModel)
{
}

void DailyPresenter::setActive()
{
    spdlog::debug("DailyPresenter::setActive");

}
