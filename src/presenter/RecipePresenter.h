#ifndef RECIPE_PRESENTER_H
#define RECIPE_PRESENTER_H

#include "MacroCalculator.h"
#include "../model/recipe/RecipeModel.h"
#include "../model/recipe/RecipeListModel.h"
#include "../view/RecipeItemView.h"

class IRecipeCallback {
public:
    virtual void onNewRecipe() = 0;
    virtual void onEditRecipe() = 0;
    virtual void onDeleteRecipe() = 0;
    virtual void onFocus() = 0;
};


class RecipePresenter : public IRecipeCallback, public IRecipeListObserver {
private:
    IRecipeModel *m_recipeModel;
    IRecipeItemView *m_recipeItemView;
    IRecipeListSubject *m_recipeListSubject;
    MacroCalculator m_macroCalculator;

    std::string getFormattedValue(double v);
    
public:
    RecipePresenter(IRecipeItemView *view, IRecipeModel *model, IRecipeListSubject *recipeListSubject);

    void postInit();

    void update() override;

    void onNewRecipe() override;
    void onEditRecipe() override;
    void onDeleteRecipe() override;
    void onFocus() override;
};

#endif // RECIPE_PRESENTER_H