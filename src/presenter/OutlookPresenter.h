#ifndef OUTLOOK_PRESENTER_H
#define OUTLOOK_PRESENTER_H

#include "TimeHelper.h"

class IOutlookModel;
class IOutlookView;

class IOutlookCallback {
public:

};

class OutlookPresenter : public IOutlookCallback {
private:
    IOutlookModel *m_outlookModel;
    IOutlookView *m_outlookView;
    TimeHelper m_timeHelper;

    void populateCalorieSection();
    void populateProgressWeightSection();
    void populateGoalWeightSection();
    void populateActualWeightLostLastWeek();

public:
    OutlookPresenter(IOutlookView *view, IOutlookModel *model);

    void postInit();
};

#endif // OUTLOOK_PRESENTER_H