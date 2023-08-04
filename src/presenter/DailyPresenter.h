#ifndef DAILY_PRESENTER_H
#define DAILY_PRESENTER_H

#include "../model/DailyModel.h"
#include "../view/TopDailyView.h"

enum class DailyPage {
    FoodBook,
    RecipeBook
};

class IDailyCallback {
public:
    virtual void onDateChanged(const std::string& date) = 0;
};

class DailyPresenter : public IDailyCallback {
private:
    IDailyModel *m_dailyModel;
    IDailyView *m_dailyView;

    void populateView();

public:
    DailyPresenter(IDailyView *view, IDailyModel *model);

    void postInit();

    void onDateChanged(const std::string& date) override;
};


#endif // DAILY_PRESENTER_H