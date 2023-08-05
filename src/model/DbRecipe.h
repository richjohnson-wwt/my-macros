#ifndef DB_RECIPE_H
#define DB_RECIPE_H

#include "DbBase.h"
#include "DbFood.h"

class DbRecipe : public DbBase {
private:
    DbFood *m_dbFood;

    Recipe recipeHelper(SQLite::Statement &query);
    
public:
    DbRecipe(const std::string& dbfile, DbFood *dbFood);

    // Read
    std::vector<Recipe> getRecipes();
    Recipe getRecipe(const std::string& name);
    Recipe getRecipeById(int id);
    std::vector<Ingredient> getIngredients(const Recipe& r);
    Food getFoodById(int id);

    // Inserts
    void saveRecipe(const Recipe& r, std::vector<Ingredient> foods);
};

#endif // DB_RECIPE_H