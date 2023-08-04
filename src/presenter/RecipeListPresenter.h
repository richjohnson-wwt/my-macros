#ifndef RECIPE_LIST_PRESENTER_H
#define RECIPE_LIST_PRESENTER_H

#include "../model/RecipeListModel.h"
#include "../model/RecipeModel.h"
#include "../view/RecipeListView.h"

class IRecipeListCallback {
public:
    virtual void onRecipeSelected(int id) = 0;
};

class RecipeListPresenter : public IRecipeListCallback , IRecipeObserver {
private:
    IRecipeListModel *m_recipeListModel;
    IRecipeSubject *m_recipeSubject;
    IRecipeListView *m_recipeListView;

public:
    RecipeListPresenter(RecipeListView *view, IRecipeListModel *model, IRecipeSubject *recipeSubject);

    void postInit();

    void onRecipeSelected(int id) override;

    void update() override;

};

#endif // RECIPE_LIST_PRESENTER_H