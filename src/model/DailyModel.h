#ifndef DAILY_MODEL_H
#define DAILY_MODEL_H

#include "DbDaily.h"
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

};

class DailyModel : public IDailyModel {
private:
    DbDaily *m_dbDaily;
    IFoodListModel *m_foodListModel;
    IRecipeListModel *m_recipeListModel;
    std::string m_dateString;

public:
    DailyModel(DbDaily *dbDaily, IFoodListModel *foodListModel, IRecipeListModel *recipeListModel);

    void setSelectedDate(const std::string& date) override;

    DailyFood getDailyFood() override;
    std::vector<XrefDailyFood> getXrefDailyFoods(const DailyFood& df) override;
    void addExercise(int exerciseCalories) override;

    void addXrefDailyFood(const XrefDailyFood &XrefDailyFood) override;


};

#endif // DAILY_MODEL_H