#include "DailyPresenter.h"
#include "TimeHelper.h"

#include <spdlog/spdlog.h>
#include <chrono>
#include <iomanip>
#include <sstream>

DailyPresenter::DailyPresenter(IDailyView *view, IDailyModel *model, TimeHelper *timeHelper)
: m_dailyModel(model), m_dailyView(view), m_timeHelper(timeHelper) {
}

void DailyPresenter::postInit()
{
    spdlog::debug("DailyPresenter::postInit() Populate today");
    m_dailyModel->loadGoal();

    auto today = m_timeHelper->getNow();
    spdlog::info("DailyPresenter::postInit() today {}", today);
    onDateChanged(today);
    m_dailyModel->setSelectedDate(today);
    refresh();
}

void DailyPresenter::onDateChanged(const std::string& date)
{
    spdlog::debug("DailyPresenter::onDateChanged() {}", date);
    m_dailyModel->setSelectedDate(date);
    if (m_dailyModel->doesDateExist(date)) {
        spdlog::info("DailyPresenter::onDateChanged() {} does exist", date);
    } else {
        spdlog::info("DailyPresenter::onDateChanged() {} does not exist", date);
        if (m_timeHelper->isDateInFuture(date)) {
            spdlog::info("DailyPresenter::onDateChanged() {} is in the future", date);
            m_dailyView->warnFutureDate();
            return;
        } else {
            spdlog::info("DailyPresenter::onDateChanged() {} is NOT in the future", date);
            DailyFood df = DailyFood{0, date, 0};
            m_dailyModel->createDailyFood(df);
        }
    }
    refresh();
}

void DailyPresenter::onDeleteDailyFood()
{
    spdlog::debug("DailyPresenter::onDeleteDailyFood");
    m_dailyModel->deleteXrefDailyFood();
    refresh();
}

void DailyPresenter::refresh() {
    spdlog::debug("DailyPresenter::refresh()");
    DailyFood df = m_dailyModel->getDailyFood();
    std::vector<XrefDailyFood> xdfVector = m_dailyModel->getXrefDailyFoods(df);
    populateDailyFood(df, xdfVector);
    populateTotals(xdfVector);

    updateDailyFoodServingIncrements();
}

void DailyPresenter::populateDailyFood(const DailyFood &df, const std::vector<XrefDailyFood>& xdfVector)
{
    spdlog::debug("DailyPresenter::populateView");
    
    m_dailyView->setDailyActivityBonus(std::to_string(df.dailyActivityBonusCalories));
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << df.weight;
    m_dailyView->setDailyWeight(ss.str());
    
    m_dailyView->setDailyFoodList(xdfVector);


}

void DailyPresenter::populateTotals(const std::vector<XrefDailyFood>& xdfVector)
{
    spdlog::debug("DailyPresenter::populateTotals");

    auto bonusCalories = m_dailyView->getActivityBonus();

    int goalFat = m_dailyModel->getGoalFatGrams(bonusCalories);
    int goalProtein = m_dailyModel->getGoalProteinGrams(bonusCalories);
    int goalCarb = m_dailyModel->getGoalCarbGrams(bonusCalories);
    int goalCalories = m_dailyModel->getGoalCalories(bonusCalories);

    int totalCalories = 0;
    int totalFat = 0;
    int totalProtein = 0;
    int totalCarb = 0;
    for (auto xdf : xdfVector) {

        totalCalories += xdf.calories;
        totalFat += xdf.fat;
        totalProtein += xdf.protein;
        totalCarb += xdf.carb;
    }
    std::vector<XrefDailyFood> totalsXdf;
    XrefDailyFood remaining;
    remaining.name = "Remaining";
    remaining.calories = goalCalories - totalCalories;
    remaining.carb = goalCarb - totalCarb;
    remaining.fat = goalFat - totalFat;
    remaining.protein = goalProtein - totalProtein;

    XrefDailyFood goal;
    goal.name = "Your daily goal";
    goal.calories = goalCalories;
    goal.carb = goalCarb;
    goal.fat = goalFat;
    goal.protein = goalProtein;

    XrefDailyFood totals;
    totals.name = "Totals";
    totals.calories = totalCalories;
    totals.carb = totalCarb;
    totals.fat = totalFat;
    totals.protein = totalProtein;

    totalsXdf.push_back(totals);
    totalsXdf.push_back(goal);
    totalsXdf.push_back(remaining);

    double percentFat = m_macroCalculator.calculateFatPercent(totalFat, totalCalories);
    double percentProtein = m_macroCalculator.calculateProteinPercent(totalProtein, totalCalories);
    double percentCarb = m_macroCalculator.calculateCarbPercent(totalCarb, totalCalories);
    
    spdlog::debug("DailyPresenter::populateTotals percentFat:{} percentProtein: {}, percentCarb: {}", percentFat, percentProtein, percentCarb);
    m_dailyView->setTotalsList(totalsXdf, percentFat, percentProtein, percentCarb);
}

void DailyPresenter::onAddExercise()
{
    spdlog::debug("DailyPresenter::onAddExercise");
    m_dailyModel->addExercise(m_dailyView->getActivityBonus());
    refresh();
}

void DailyPresenter::onAddWeight()
{
    spdlog::debug("DailyPresenter::onAddWeight");
    m_dailyModel->addWeight(m_dailyView->getWeight());
    refresh();
}

void DailyPresenter::onAddDailyFood()
{
    spdlog::debug("DailyPresenter::onAddDailyFood");
    DailyFood df = m_dailyModel->getDailyFood();
    Food food = m_dailyModel->getFood();
    double multiplier = getServingMultiplier(m_dailyView->getDailyMultiplier());

    CalculatedMacros cm = m_macroCalculator.calculateFoodMacros(food, multiplier);
    std::stringstream ss;
    ss << food.name << " x " << multiplier;
    XrefDailyFood xdf;
    xdf.id = 0;
    xdf.dailyFoodId = df.id;
    xdf.name = ss.str();
    xdf.fat = cm.fatGrams;
    xdf.protein = cm.proteinGrams;
    xdf.carb = cm.carbGrams;
    xdf.calories = cm.calories;

    xdf.dailyFoodId = df.id;
    
    m_dailyModel->addXrefDailyFood(xdf, food.id);

    updateDailyFoodServingIncrements();

    refresh();
}

void DailyPresenter::updateDailyFoodServingIncrements() {
    spdlog::debug("DailyPresenter::updateDailyFoodServingIncrements");
    m_dailyView->resetDailyMultiplier(m_dailyModel->getDailyFoodServingIncrements(), 5);
}

double DailyPresenter::getServingMultiplier(int multiplierIndex) {
    spdlog::debug("DailyPresenter::getServingMultiplier");
    return std::stod(m_dailyModel->getDailyFoodServingIncrements()[multiplierIndex]);
}

void DailyPresenter::onAddDailyRecipe()
{
    spdlog::debug("DailyPresenter::onAddDailyRecipe");
    DailyFood df = m_dailyModel->getDailyFood();
    std::vector<Ingredient> ingredients = m_dailyModel->getIngredients();
    Recipe recipe = m_dailyModel->getRecipe();
    double multiplier = getServingMultiplier(m_dailyView->getDailyMultiplier());
    std::vector<XrefDailyFood> xdfVector = m_dailyModel->getXrefDailyFoods(df);

    CalculatedMacros cm = m_macroCalculator.calculateRecipeMacros(recipe.servings, ingredients, multiplier);
    std::stringstream ss;
    ss << recipe.name << " x " << multiplier;
    XrefDailyFood xdf;
    xdf.id = 0;
    xdf.dailyFoodId = df.id;
    xdf.name = ss.str();
    xdf.fat = cm.fatGrams;
    xdf.protein = cm.proteinGrams;
    xdf.carb = cm.carbGrams;
    xdf.calories = cm.calories;
    xdfVector.push_back(xdf);

    m_dailyModel->addXrefDailyFood(xdf);

    refresh();
}

void DailyPresenter::onOneOff() {
    XrefDailyFood xdf = m_dailyView->promptUserForOneOff();
    if (xdf.name == "") {
        spdlog::info("DailyPresenter::onOneOff action cancelled");
        return;
    }
    spdlog::info("DailyPresenter::onOneOff");
    DailyFood df = m_dailyModel->getDailyFood();

    xdf.dailyFoodId = df.id;
    m_dailyModel->addXrefDailyFood(xdf);
    refresh();

}

void DailyPresenter::onSelectedDailyFoodChanged(int id)
{
    spdlog::debug("DailyPresenter::onSelectedDailyFoodChanged {}", id);
    m_dailyModel->setSelectedDailyFoodId(id);
}

