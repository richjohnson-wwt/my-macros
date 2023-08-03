#ifndef RECIPE_LIST_PRESENTER_H
#define RECIPE_LIST_PRESENTER_H

#include "../model/RecipeModel.h"
#include "../view/RecipeListView.h"

class IRecipeListCallback {
public:
    virtual void onRecipeSelected(int id) = 0;

    virtual void setActive() = 0;
};

class RecipeListPresenter : public IRecipeListCallback {
private:
    IRecipeModel *m_recipeModel;
    IRecipeListView *m_recipeListView;

public:
    RecipeListPresenter(RecipeListView *view, IRecipeModel *model);

    void setActive() override;

    void onRecipeSelected(int id) override;

};

#endif // RECIPE_LIST_PRESENTER_H