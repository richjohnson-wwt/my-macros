#ifndef RECIPE_PRESENTER_H
#define RECIPE_PRESENTER_H

#include "../model/RecipeModel.h"
#include "../view/TopRecipeView.h"

class IRecipeSubject;

class IRecipeCallback {
public:
    virtual void setActive() = 0;
};


class RecipePresenter : public IRecipeCallback, public IRecipeObserver {
private:
    IRecipeModel *m_recipeModel;
    ITopRecipeView *m_topRecipeView;
    IRecipeSubject *m_recipeSubject;
    
public:
    RecipePresenter(ITopRecipeView *view, IRecipeModel *model, IRecipeSubject *recipeSubject);

    void postInit();

    void setActive() override;

    void update() override;
};

#endif // RECIPE_PRESENTER_H