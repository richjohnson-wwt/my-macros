#ifndef RECIPE_PRESENTER_H
#define RECIPE_PRESENTER_H

#include "../model/RecipeModel.h"
#include "../model/RecipeListModel.h"
#include "../view/TopRecipeView.h"

class IRecipeCallback {
public:
    virtual void onNewRecipe() = 0;
    virtual void onCancelNewRecipe() = 0;
    virtual void onAddIngredient(double unitMultiplier) = 0;
    virtual void onSaveRecipe() = 0;
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

    void onNewRecipe() override;
    void onCancelNewRecipe() override;
    void onAddIngredient(double unitMultiplier) override;
    void onSaveRecipe() override;
};

#endif // RECIPE_PRESENTER_H