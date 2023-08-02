#ifndef DAILY_PRESENTER_H
#define DAILY_PRESENTER_H

#include "../model/DailyModel.h"
#include "../view/DailyView.h"

enum class DailyPage {
    FoodBook,
    RecipeBook
};

class IDailyCallback {
public:
    virtual void onFoodRecipeBookPageChanged(int bookPageIndex) = 0;
    virtual void onFoodSelected(int id) = 0;
    virtual void onRecipeSelected(int id) = 0;
};

class DailyPresenter : public IDailyCallback {
private:
    IDailyModel *m_dailyModel;
    IDailyView *m_dailyView;

public:
    DailyPresenter(IDailyView *view, IDailyModel *model);

    void setActive();

    void onFoodRecipeBookPageChanged(int bookPageIndex) override;
    void onFoodSelected(int id) override;
    void onRecipeSelected(int id) override;

};


#endif // DAILY_PRESENTER_H