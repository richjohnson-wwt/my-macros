#ifndef DAILY_PRESENTER_H
#define DAILY_PRESENTER_H

#include "../model/DailyModel.h"
#include "../model/RecipeModel.h"
#include "../view/TopDailyView.h"

enum class DailyPage {
    FoodBook,
    RecipeBook
};

class IDailyCallback {
public:
    // virtual void onRecipeBookPageChanged() = 0;
    // virtual void onRecipeSelected(int id) = 0;
};

class DailyPresenter : public IDailyCallback {
private:
    IDailyModel *m_dailyModel;
    IDailyView *m_dailyView;
    IRecipeModel *m_recipeModel;

public:
    DailyPresenter(IDailyView *view, IDailyModel *model, IRecipeModel *recipeModel);

    void setActive();

    // void onRecipeBookPageChanged() override;
    // void onRecipeSelected(int id) override;

};


#endif // DAILY_PRESENTER_H