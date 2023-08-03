#ifndef RECIPE_MODEL_H
#define RECIPE_MODEL_H

#include "Db.h"
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
    virtual std::vector<Recipe> getRecipes() = 0;
    virtual void setSelectedId(int idx) = 0;
    virtual int getSelectedId() = 0;
    virtual Recipe getRecipeById(int id) = 0;
};

class RecipeModel : public IRecipeModel, public IRecipeSubject {
private:
    Db m_db;
    int m_selectedId;
    std::vector<IRecipeObserver*> m_observers;

public:
    RecipeModel();

    std::vector<Recipe> getRecipes() override;
    void setSelectedId(int idx) override;
    int getSelectedId() override;
    Recipe getRecipeById(int id) override;

    void attach(IRecipeObserver* observer) override;
    void notify() override;
};

#endif // RECIPE_MODEL_H