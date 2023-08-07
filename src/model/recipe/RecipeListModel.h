#ifndef RECIPE_LIST_MODEL_H
#define RECIPE_LIST_MODEL_H

#include "../db/DbRecipe.h"
#include "../MyMacroTypes.h"
#include <vector>

class IRecipeListModel {
public:
    virtual void setSelectedId(int idx) = 0;
    virtual int getSelectedId() = 0;
    virtual std::vector<Recipe> getRecipes() = 0;
    virtual Recipe getSelectedRecipe() = 0;
};

class IRecipeListObserver {
public:
    virtual void update() = 0;
};

class IRecipeListSubject {
public:
    virtual void attach(IRecipeListObserver* observer) = 0;
    virtual void notify() = 0;
};

class RecipeListModel : public IRecipeListModel, public IRecipeListSubject {
private:
    DbRecipe *m_dbRecipe;
    int m_selectedId;
    std::vector<IRecipeListObserver*> m_observers;

public:
    RecipeListModel(DbRecipe *db);
    std::vector<Recipe> getRecipes() override;
    void setSelectedId(int idx) override;
    int getSelectedId() override;
    Recipe getSelectedRecipe() override;

    void attach(IRecipeListObserver* observer) override;
    void notify() override;
};


#endif // RECIPE_LIST_MODEL_H