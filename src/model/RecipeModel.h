#ifndef RECIPE_MODEL_H
#define RECIPE_MODEL_H

#include "Db.h"
#include "MyMacroTypes.h"
#include <vector>

class IRecipeModel {
public:
    virtual std::vector<Recipe> getRecipes() = 0;
    virtual void setSelectedId(int idx) = 0;
    virtual int getSelectedId() = 0;

};

class RecipeModel : public IRecipeModel {
private:
    Db m_db;
    int m_selectedId;

public:
    RecipeModel();

    std::vector<Recipe> getRecipes() override;
    void setSelectedId(int idx) override;
    int getSelectedId() override;
};

#endif // RECIPE_MODEL_H