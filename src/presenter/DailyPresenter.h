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

};

class DailyPresenter : public IDailyCallback {
private:
    IDailyModel *m_dailyModel;
    IDailyView *m_dailyView;
    IRecipeModel *m_recipeModel;

public:
    DailyPresenter(IDailyView *view, IDailyModel *model, IRecipeModel *recipeModel);

    void setActive();

};


#endif // DAILY_PRESENTER_H