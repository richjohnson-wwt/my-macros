#ifndef RECIPE_LIST_PRESENTER_H
#define RECIPE_LIST_PRESENTER_H

#include "../model/recipe/RecipeListModel.h"
#include "../model/recipe/RecipeModel.h"
#include "../view/RecipeListView.h"

class IDbRecipeSubject;

class IRecipeListCallback {
public:
    virtual void onRecipeSelected(int id) = 0;
};

class RecipeListPresenter : public IRecipeListCallback , IDbRecipeObserver {
private:
    IRecipeListModel *m_recipeListModel;
    IDbRecipeSubject *m_dbRecipeSubject;
    IRecipeListView *m_recipeListView;

public:
    RecipeListPresenter(RecipeListView *view, IRecipeListModel *model, IDbRecipeSubject *recipeSubject);

    void postInit();

    void onRecipeSelected(int id) override;

    void update() override;

};

#endif // RECIPE_LIST_PRESENTER_H