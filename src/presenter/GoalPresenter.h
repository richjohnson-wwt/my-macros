#ifndef GOAL_PRESENTER_H
#define GOAL_PRESENTER_H

#include "../model/db/DbGoal.h"

class IGoalView;

class GoalPresenter {
private:
    DbGoal *m_dbGoal;
    IGoalView *m_view;
public:
    GoalPresenter(DbGoal *dbGoal, IGoalView *view);
    void postInit();
};

#endif // GOAL_PRESENTER_H