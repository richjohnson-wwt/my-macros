#ifndef RECIPE_PRESENTER_H
#define RECIPE_PRESENTER_H

#include "../model/RecipeModel.h"
#include "../view/TopRecipeView.h"

class IRecipeCallback {
public:

};


class RecipePresenter : public IRecipeCallback {
private:
    IRecipeModel *m_recipeModel;
    ITopRecipeView *m_topRecipeView;
    
public:
    RecipePresenter(ITopRecipeView *view, IRecipeModel *model);

    void setActive();
};

#endif // RECIPE_PRESENTER_H