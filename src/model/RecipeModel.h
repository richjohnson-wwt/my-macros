#ifndef RECIPE_MODEL_H
#define RECIPE_MODEL_H

#include "RecipeListModel.h"
#include "FoodListModel.h"
#include "DbRecipe.h"
#include "MyMacroTypes.h"
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
    virtual void saveRecipe() = 0;

    virtual void setRecipeName(const std::string& name) = 0;
    virtual void setRecipeDescription(const std::string& description) = 0;
    virtual void setRecipeUrl(const std::string& url) = 0;
    virtual void setRecipeServings(const std::string& servings) = 0;
    virtual void setRecipeInstructions(const std::string& instructions) = 0;
};

class RecipeModel : public IRecipeModel, public IRecipeSubject {
private:
    DbRecipe *m_dbRecipe;
    std::vector<IRecipeObserver*> m_observers;

    RecipeListModel *m_recipeListModel;
    FoodListModel *m_foodListModel;

    bool m_buildingRecipe;
    Recipe m_recipeUnderConstruction;
    std::vector<Ingredient> m_ingredientsUnderConstruction;
    const int NEW_RECIPE_ID = -1;

public:
    RecipeModel(DbRecipe *db, RecipeListModel *recipeListModel, FoodListModel *foodListModel);

    Recipe getRecipe() override;
    std::vector<Ingredient> getIngredients() override;

    void attach(IRecipeObserver* observer) override;
    void notify() override;

    void newRecipe() override;
    void cancelNewRecipe() override;
    void addIngredient(double unitMultiplier) override;
    void saveRecipe() override;

    void setRecipeName(const std::string& name) override;
    void setRecipeDescription(const std::string& description) override;
    void setRecipeUrl(const std::string& url) override;
    void setRecipeServings(const std::string& servings) override;
    void setRecipeInstructions(const std::string& instructions) override;
};

#endif // RECIPE_MODEL_H