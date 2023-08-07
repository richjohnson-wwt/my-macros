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

    // virtual void setRecipeName(const std::string& name) = 0;
    // virtual void setRecipeDescription(const std::string& description) = 0;
    // virtual void setRecipeUrl(const std::string& url) = 0;
    // virtual void setRecipeServings(const std::string& servings) = 0;
    // virtual void setRecipeInstructions(const std::string& instructions) = 0;
    // virtual void selectIngredient(int id) = 0;
};

class RecipeModel : public IRecipeModel, public IRecipeSubject {
private:
    DbRecipe *m_dbRecipe;
    RecipeCommonModel *m_commonModel;
    std::vector<IRecipeObserver*> m_observers;

    RecipeListModel *m_recipeListModel;
    FoodListModel *m_foodListModel;

    // Recipe m_recipeUnderConstruction;
    // std::vector<Ingredient> m_ingredientsUnderConstruction;
    // const int NEW_RECIPE_ID = -1;
    // int m_selectedIngredient;

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

    // void setRecipeName(const std::string& name) override;
    // void setRecipeDescription(const std::string& description) override;
    // void setRecipeUrl(const std::string& url) override;
    // void setRecipeServings(const std::string& servings) override;
    // void setRecipeInstructions(const std::string& instructions) override;

    // void selectIngredient(int id) override;
};

#endif // RECIPE_MODEL_H