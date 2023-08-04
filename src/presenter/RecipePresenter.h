#ifndef RECIPE_PRESENTER_H
#define RECIPE_PRESENTER_H

#include "../model/RecipeModel.h"
#include "../model/RecipeListModel.h"
#include "../view/TopRecipeView.h"

class IRecipeCallback {
public:
};


class RecipePresenter : public IRecipeCallback, public IRecipeListObserver {
private:
    IRecipeModel *m_recipeModel;
    ITopRecipeView *m_topRecipeView;
    IRecipeListSubject *m_recipeListSubject;
    
public:
    RecipePresenter(ITopRecipeView *view, IRecipeModel *model, IRecipeListSubject *recipeListSubject);

    void postInit();

    void update() override;
};

#endif // RECIPE_PRESENTER_H