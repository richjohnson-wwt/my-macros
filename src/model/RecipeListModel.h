#ifndef RECIPE_LIST_MODEL_H
#define RECIPE_LIST_MODEL_H

#include "Db.h"
#include "MyMacroTypes.h"
#include <vector>

class IRecipeListModel {
public:
    virtual void setSelectedId(int idx) = 0;
    virtual int getSelectedId() = 0;
    virtual std::vector<Recipe> getRecipes() = 0;
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
    Db m_db;
    int m_selectedId;
    std::vector<IRecipeListObserver*> m_observers;

public:
    RecipeListModel();
    std::vector<Recipe> getRecipes() override;
    void setSelectedId(int idx) override;
    int getSelectedId() override;

    void attach(IRecipeListObserver* observer) override;
    void notify() override;
};


#endif // RECIPE_LIST_MODEL_H