#ifndef OUTLOOK_PRESENTER_H
#define OUTLOOK_PRESENTER_H

#include "TimeHelper.h"
#include "../model/db/DbDaily.h"

class IOutlookModel;
class IOutlookView;
class TimeHelper;

class OutlookPresenter : public IDbDailyObserver {
private:
    IOutlookModel *m_outlookModel;
    IOutlookView *m_outlookView;
    TimeHelper *m_timeHelper;

    void refresh();

public:
    OutlookPresenter(IOutlookView *view, 
        IOutlookModel *model, 
        TimeHelper *timeHelper, 
        IDbDailySubject *dbDailySubject);

    void update() override;

    void postInit();

    void populateCalorieSection();
    void populateProgressWeightSection();
    void populateGoalWeightSection();
    void populateActualWeightLostLastWeek();
};

#endif // OUTLOOK_PRESENTER_H