#ifndef DAILY_MODEL_H
#define DAILY_MODEL_H

#include "DbDaily.h"
#include "RecipeModel.h"
#include "FoodListModel.h"
#include "RecipeListModel.h"
#include "MyMacroTypes.h"
#include <vector>

class IDailyModel {
public:
    virtual void setSelectedDate(const std::string& date) = 0;
    virtual DailyFood getDailyFood() = 0;
    virtual std::vector<XrefDailyFood> getXrefDailyFoods(const DailyFood& df) = 0;
    virtual void addExercise(int exerciseCalories) = 0;
    virtual void addXrefDailyFood(const XrefDailyFood &XrefDailyFood) = 0;
    virtual Food getFood() = 0;
    virtual Recipe getRecipe() = 0;
    virtual std::vector<Ingredient> getIngredients() = 0;
    virtual void setSelectedDailyFoodId(int id) = 0;
    virtual void deleteXrefDailyFood() = 0;
    virtual int getGoalFatGrams() = 0;
    virtual int getGoalProteinGrams() = 0;
    virtual int getGoalCarbGrams() = 0;
    virtual int getGoalCalories() = 0;

};

class DailyModel : public IDailyModel {
private:
    DbDaily *m_dbDaily;
    IFoodListModel *m_foodListModel;
    IRecipeListModel *m_recipeListModel;
    IRecipeModel *m_recipeModel;
    std::string m_dateString;
    int m_selectedDailyFoodId;

    const int FAT_GRAMS = 168;
    const int PROTEIN_GRAMS = 101;
    const int CARB_GRAMS = 25;
    const int TOTAL_CALORIES = 2010;

public:
    DailyModel(DbDaily *dbDaily, IFoodListModel *foodListModel, IRecipeListModel *recipeListModel, IRecipeModel *recipeModel);

    void setSelectedDate(const std::string& date) override;

    DailyFood getDailyFood() override;
    std::vector<XrefDailyFood> getXrefDailyFoods(const DailyFood& df) override;
    void addExercise(int exerciseCalories) override;

    void addXrefDailyFood(const XrefDailyFood &XrefDailyFood) override;

    Food getFood() override;
    Recipe getRecipe() override;
    std::vector<Ingredient> getIngredients() override;
    void setSelectedDailyFoodId(int id) override;
    void deleteXrefDailyFood() override;

    int getGoalFatGrams() override;
    int getGoalProteinGrams() override;
    int getGoalCarbGrams() override;
    int getGoalCalories() override;


};

#endif // DAILY_MODEL_H