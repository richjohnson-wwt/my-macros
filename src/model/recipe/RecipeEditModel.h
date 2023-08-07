#ifndef RECIPE_EDIT_MODEL_H
#define RECIPE_EDIT_MODEL_H

#include "RecipeListModel.h"
#include "RecipeCommonModel.h"
#include "../food/FoodListModel.h"
#include "../db/DbRecipe.h"
#include <vector>

class IRecipeEditModel {
public:
    virtual Recipe getEditRecipe() = 0;
    virtual Recipe getNewRecipe() = 0;
    virtual std::vector<Ingredient> getEditIngredients() = 0;
    virtual std::vector<Ingredient> getNewIngredients() = 0;

    virtual void cancelNewRecipe() = 0;
    virtual void addIngredient(double unitMultiplier) = 0;
    virtual void deleteIngredient() = 0;
    virtual void saveRecipe() = 0;
};

class RecipeEditModel : public IRecipeEditModel {
private:
    DbRecipe *m_dbRecipe;

    RecipeListModel *m_recipeListModel;
    FoodListModel *m_foodListModel;
    RecipeCommonModel *m_recipeCommonModel;

    const int NEW_RECIPE_ID = -1;

public:
    RecipeEditModel(DbRecipe *db, RecipeListModel *recipeListModel, FoodListModel *foodListModel, RecipeCommonModel *recipeCommonModel);

    Recipe getEditRecipe() override;
    Recipe getNewRecipe() override;
    std::vector<Ingredient> getEditIngredients() override;
    std::vector<Ingredient> getNewIngredients() override;

    void cancelNewRecipe() override;
    void addIngredient(double unitMultiplier) override;
    void deleteIngredient() override;
    void saveRecipe() override;
};

#endif // RECIPE_EDIT_MODEL_H