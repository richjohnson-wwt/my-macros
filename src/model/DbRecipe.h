#ifndef DB_RECIPE_H
#define DB_RECIPE_H

#include "DbBase.h"
#include "DbFood.h"

class DbRecipe : public DbBase {
private:
    DbFood *m_dbFood;
public:
    DbRecipe(const std::string& dbfile, DbFood *dbFood);
    std::vector<Recipe> getRecipes();
    Recipe getRecipeById(int id);
    std::vector<Ingredient> getIngredients(const Recipe& r);
};

#endif // DB_RECIPE_H