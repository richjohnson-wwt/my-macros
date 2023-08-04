#ifndef RECIPE_MODEL_H
#define RECIPE_MODEL_H

#include "RecipeListModel.h"
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
    virtual int getSelectedId() = 0;
    virtual Recipe getRecipeById(int id) = 0;
};

class RecipeModel : public IRecipeModel, public IRecipeSubject {
private:
    Db m_db;
    int m_selectedId;
    std::vector<IRecipeObserver*> m_observers;
    RecipeListModel *m_recipeListModel;

public:
    RecipeModel(RecipeListModel *recipeListModel);

    int getSelectedId() override;
    Recipe getRecipeById(int id) override;

    void attach(IRecipeObserver* observer) override;
    void notify() override;
};

#endif // RECIPE_MODEL_H