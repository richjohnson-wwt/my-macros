#ifndef RECIPE_MODEL_H
#define RECIPE_MODEL_H

#include "RecipeListModel.h"
#include "RecipeCommonModel.h"
#include "../food/FoodListModel.h"
#include "../db/DbRecipe.h"
#include <vector>

class IRecipeObserver {
public:
    virtual void update() = 0;
};

class IRecipeSubject {
public:
    virtual void attach(IRecipeObserver* observer) = 0;
    virtual void notify() = 0;
};

class IRecipeModel {
public:
    virtual Recipe getRecipe() = 0;
    virtual std::vector<Ingredient> getIngredients() = 0;
    virtual void newRecipe() = 0;
    virtual void cancelNewRecipe() = 0;
    virtual void addIngredient(double unitMultiplier) = 0;
    virtual void deleteIngredient() = 0;
    virtual void saveRecipe() = 0;
    virtual void deleteRecipe() = 0;
    virtual bool isInEditMode() = 0;
    virtual void setInEditMode(bool inEditMode) = 0;
};

class RecipeModel : public IRecipeModel, public IRecipeSubject {
private:
    DbRecipe *m_dbRecipe;
    RecipeCommonModel *m_commonModel;
    std::vector<IRecipeObserver*> m_observers;

    RecipeListModel *m_recipeListModel;
    FoodListModel *m_foodListModel;

public:
    RecipeModel(DbRecipe *db, RecipeListModel *recipeListModel, RecipeCommonModel *commonModel);

    Recipe getRecipe() override;
    std::vector<Ingredient> getIngredients() override;

    void attach(IRecipeObserver* observer) override;
    void notify() override;

    void newRecipe() override;
    void cancelNewRecipe() override;
    void addIngredient(double unitMultiplier) override;
    void deleteIngredient() override;
    void saveRecipe() override;
    void deleteRecipe() override;
    bool isInEditMode() override;
    void setInEditMode(bool inEditMode) override;
};

#endif // RECIPE_MODEL_H