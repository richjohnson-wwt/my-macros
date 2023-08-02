#ifndef DAILY_MODEL_H
#define DAILY_MODEL_H

#include "Db.h"
#include "MyMacroTypes.h"
#include <vector>

class IDailyModel {
public:
    virtual void setFoodSource() = 0;
    virtual void setRecipeSource() = 0;
    virtual std::vector<Food> getFoods() = 0;
    virtual std::vector<Recipe> getRecipes() = 0;
    virtual void setFoodSelectedId(int id) = 0;
    virtual void setRecipeSelectedId(int id) = 0;
};

class DailyModel : public IDailyModel {
private:
    Db m_db;
    int m_selectedFoodId;
    int m_selectedRecipeId;

public:
    DailyModel();
    void setFoodSource() override {}
    void setRecipeSource() override {}
    std::vector<Food> getFoods() override;
    std::vector<Recipe> getRecipes() override;
    void setFoodSelectedId(int idx) override;
    void setRecipeSelectedId(int idx) override;
};

#endif // DAILY_MODEL_H