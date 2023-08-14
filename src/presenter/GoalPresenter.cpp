#include "GoalPresenter.h"

#include <spdlog/spdlog.h>
#include "../view/GoalView.h"

#include <spdlog/spdlog.h>
#include <sstream>

GoalPresenter::GoalPresenter(DbGoal *dbGoal, IGoalView *view): m_dbGoal(dbGoal), m_view(view)
{
}

void GoalPresenter::postInit()
{
    spdlog::debug("GoalPresenter::postInit");
    Goal g = m_dbGoal->getGoal();
    m_view->setStartDate(g.startDate);
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << g.targetWeight;
    m_view->setTargetWeight(ss.str());
    m_view->setBmrCalories(std::to_string(g.bmrCalories));
    m_view->setFatPercent(std::to_string(g.fatPercent));
    m_view->setProteinPercent(std::to_string(g.proteinPercent));
    m_view->setCarbPercent(std::to_string(g.carbPercent));
}