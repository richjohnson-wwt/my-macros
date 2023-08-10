#ifndef OUTLOOK_PRESENTER_H
#define OUTLOOK_PRESENTER_H

#include "TimeHelper.h"

class IOutlookModel;
class IOutlookView;
class TimeHelper;

class OutlookPresenter {
private:
    IOutlookModel *m_outlookModel;
    IOutlookView *m_outlookView;
    TimeHelper *m_timeHelper;

    

public:
    OutlookPresenter(IOutlookView *view, IOutlookModel *model, TimeHelper *timeHelper);

    void postInit();

    void populateCalorieSection();
    void populateProgressWeightSection();
    void populateGoalWeightSection();
    void populateActualWeightLostLastWeek();
};

#endif // OUTLOOK_PRESENTER_H