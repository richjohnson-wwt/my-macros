#ifndef DB_RECIPE_H
#define DB_RECIPE_H

#include "DbBase.h"
#include "DbFood.h"

class IDbRecipeObserver {
public:
    virtual void update() = 0;
};

class IDbRecipeSubject {
public:
    virtual void attach(IDbRecipeObserver* observer) = 0;
    virtual void notify() = 0;
};

class DbRecipe : public DbBase, public IDbRecipeSubject {
private:
    DbFood *m_dbFood;
    std::vector<IDbRecipeObserver*> m_observers;

    void notify();

    Recipe recipeHelper(SQLite::Statement &query);
    
public:
    DbRecipe(const std::string& dbfile, DbFood *dbFood);

    void attach(IDbRecipeObserver* observer);

    // Read
    std::vector<Recipe> getRecipes();
    Recipe getRecipe(const std::string& name);
    Recipe getRecipeById(int id);
    std::vector<Ingredient> getIngredients(const Recipe& r);
    Food getFoodById(int id);

    // Inserts
    void saveRecipe(const Recipe& r, std::vector<Ingredient> foods);


    // Deletes
    void deleteRecipe(int id);
    void deleteIngredient(int recipeId, int foodId);

    // Updates
    void updateRecipe(const Recipe& r);
};

#endif // DB_RECIPE_H