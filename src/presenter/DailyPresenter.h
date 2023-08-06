#ifndef DAILY_PRESENTER_H
#define DAILY_PRESENTER_H

#include "../model/DailyModel.h"
#include "../view/TopDailyView.h"

enum class DailyPage {
    FoodBook,
    RecipeBook
};

class IDailyCallback {
public:
    virtual void onDateChanged(const std::string& date) = 0;
    virtual void onAddExercise() = 0;
    virtual void onAddDailyFood() = 0;
    virtual void onAddDailyRecipe() = 0;
    virtual void onDeleteDailyFood() = 0;
    virtual void onSelectedDailyFoodChanged(int id) = 0;
};

class DailyPresenter : public IDailyCallback {
private:
    IDailyModel *m_dailyModel;
    IDailyView *m_dailyView;

    void refresh();

    void populateDailyFood(const DailyFood &df, const std::vector<XrefDailyFood>& xdfVector);
    void populateTotals(const std::vector<XrefDailyFood>& xdfVector);

    double calculateTotalFatGrams(const std::vector<Ingredient> &ingredients);
    double calculateTotalProteinGrams(const std::vector<Ingredient> &ingredients);
    double calculateTotalCarbGrams(const std::vector<Ingredient> &ingredients);
    CalculatedMacros calculateFoodMacros(const Food &food, double multiplier = 1.0);
    CalculatedMacros calculateRecipeMacros(
            int servings,
            const std::vector<Ingredient> &ingredients, 
            double multiplier = 1.0);

public:
    DailyPresenter(IDailyView *view, IDailyModel *model);

    void postInit();

    void onDateChanged(const std::string& date) override;
    void onAddExercise() override;
    void onAddDailyFood() override;
    void onAddDailyRecipe() override;
    void onDeleteDailyFood() override;
    void onSelectedDailyFoodChanged(int id) override;
};


#endif // DAILY_PRESENTER_H