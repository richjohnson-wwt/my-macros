#ifndef DAILY_MODEL_H
#define DAILY_MODEL_H

#include "db/DbDaily.h"
#include "db/DbGoal.h"
#include "recipe/RecipeModel.h"
#include "recipe/RecipeListModel.h"
#include "food/FoodListModel.h"
#include "MyMacroTypes.h"
#include <vector>

class IDailyModel {
public:
    virtual void createDailyFood(const DailyFood& df) = 0;
    virtual void setSelectedDate(const std::string& date) = 0;
    virtual DailyFood getDailyFood() = 0;
    virtual std::vector<XrefDailyFood> getXrefDailyFoods(const DailyFood& df) = 0;
    virtual void addExercise(int exerciseCalories) = 0;
    virtual void addWeight(double weight) = 0;
    virtual void addXrefDailyFood(const XrefDailyFood &XrefDailyFood, int foodId = -1) = 0;
    virtual Food getFood() = 0;
    virtual Recipe getRecipe() = 0;
    virtual std::vector<Ingredient> getIngredients() = 0;
    virtual void setSelectedDailyFoodId(int id) = 0;
    virtual void deleteXrefDailyFood() = 0;
    virtual int getGoalFatGrams(int activityBonus) = 0;
    virtual int getGoalProteinGrams(int activityBonus) = 0;
    virtual int getGoalCarbGrams(int activityBonus) = 0;
    virtual int getGoalCalories(int activityBonus) = 0;
    virtual void loadGoal() = 0;
    virtual bool doesDateExist(const std::string& date) = 0;
    virtual std::vector<std::string> getDailyFoodServingIncrements() = 0;

};

class DailyModel : public IDailyModel {
private:
    DbDaily *m_dbDaily;
    DbGoal *m_dbGoal;
    DbFood *m_dbFood;
    IFoodListModel *m_foodListModel;
    IRecipeListModel *m_recipeListModel;
    IRecipeModel *m_recipeModel;
    std::string m_dateString;
    int m_selectedDailyFoodId;
    Goal m_goal;
    std::vector<std::string> m_dailyFoodServingIncrements;

public:
    DailyModel(DbDaily *dbDaily, DbGoal *dbGoal, DbFood* dbFood, IFoodListModel *foodListModel, IRecipeListModel *recipeListModel, IRecipeModel *recipeModel);

    void setSelectedDate(const std::string& date) override;
    void createDailyFood(const DailyFood& df) override;

    DailyFood getDailyFood() override;
    std::vector<XrefDailyFood> getXrefDailyFoods(const DailyFood& df) override;
    void addExercise(int exerciseCalories) override;
    void addWeight(double weight) override;

    void addXrefDailyFood(const XrefDailyFood &XrefDailyFood, int foodId) override;

    Food getFood() override;
    Recipe getRecipe() override;
    std::vector<Ingredient> getIngredients() override;
    void setSelectedDailyFoodId(int id) override;
    void deleteXrefDailyFood() override;

    int getGoalFatGrams(int activityBonus) override;
    int getGoalProteinGrams(int activityBonus) override;
    int getGoalCarbGrams(int activityBonus) override;
    int getGoalCalories(int activityBonus) override;

    void loadGoal() override;
    bool doesDateExist(const std::string& date) override;
    std::vector<std::string> getDailyFoodServingIncrements() override;


};

#endif // DAILY_MODEL_H