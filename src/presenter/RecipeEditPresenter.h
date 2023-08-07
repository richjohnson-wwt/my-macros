#ifndef RECIPE_EDIT_PRESENTER_H
#define RECIPE_EDIT_PRESENTER_H

#include "../model/recipe/RecipeEditModel.h"
#include "../model/recipe/RecipeListModel.h"
#include "../view/RecipeItemView.h"
#include "RecipePresenter.h"

class IRecipeEditModel;
class IRecipeListSubject;
class IRecipeEditView;

class IRecipeEditCallback {
public:
    virtual void onCancelNewRecipe() = 0;
    virtual void onAddIngredient(double unitMultiplier) = 0;
    virtual void onDeleteIngredient() = 0;
    virtual void onSaveRecipe() = 0;
    virtual void onSelectIngredient(int id) = 0;

    virtual void initNewPage() = 0;
    virtual void initEditPage() = 0;
};


class RecipeEditPresenter : public IRecipeEditCallback {
private:
    IRecipeEditModel *m_recipeEditModel;
    IRecipeEditView *m_recipeEditView;
    IRecipeListSubject *m_recipeListSubject;
    RecipePresenter *m_recipePresenter;

    
public:
    RecipeEditPresenter(IRecipeEditView *view, 
        IRecipeEditModel *model, 
        IRecipeListSubject *recipeListSubject, 
        RecipePresenter *recipePresenter);

    void initNewPage() override;
    void initEditPage() override;

    void onCancelNewRecipe() override;
    void onAddIngredient(double unitMultiplier) override;
    void onDeleteIngredient() override;
    void onSaveRecipe() override;
    void onSelectIngredient(int id) override;
};

#endif // RECIPE_EDIT_PRESENTER_H