#ifndef RECIPE_LIST_PRESENTER_H
#define RECIPE_LIST_PRESENTER_H

#include "../model/RecipeModel.h"
#include "../view/RecipeListView.h"

class IRecipeListCallback {
public:
    virtual void onRecipeSelected(int id) = 0;
    virtual void onRecipeBookPageChanged() = 0;
};

class RecipeListPresenter : public IRecipeListCallback {
private:
    IRecipeModel *m_recipeModel;
    IRecipeListView *m_recipeListView;

public:
    RecipeListPresenter(RecipeListView *view, IRecipeModel *model);

    void setActive();

    void onRecipeSelected(int id) override;
    void onRecipeBookPageChanged() override;

};

#endif // RECIPE_LIST_PRESENTER_H