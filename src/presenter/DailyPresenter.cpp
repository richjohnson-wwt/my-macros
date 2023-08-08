#include "DailyPresenter.h"

#include <spdlog/spdlog.h>
#include <chrono>
#include <iomanip>
#include <sstream>

DailyPresenter::DailyPresenter(IDailyView *view, IDailyModel *model)
: m_dailyModel(model), m_dailyView(view)
{
}

void DailyPresenter::postInit()
{
    spdlog::debug("DailyPresenter::postInit() Populate today");

    // Get todays date in iso format yyyy-mm-dd using std::chrono
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    std::string today = ss.str();
    spdlog::info("DailyPresenter::postInit() today {}", today);
    m_dailyModel->setSelectedDate(today);
    refresh();
}

void DailyPresenter::onDateChanged(const std::string& date)
{
    spdlog::debug("DailyPresenter::onDateChanged() {}", date);
    m_dailyModel->setSelectedDate(date);
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

    int goalFat = m_dailyModel->getGoalFatGrams();
    int goalProtein = m_dailyModel->getGoalProteinGrams();
    int goalCarb = m_dailyModel->getGoalCarbGrams();
    int goalCalories = m_dailyModel->getGoalCalories() + m_dailyView->getActivityBonus();

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

    double percentFat = 0.0;
    if (totalFat > 0) {
        percentFat = ((static_cast<double>(totalFat) * 9) / totalCalories) * 100;
    }
    double percentProtein = 0.0;
    if (totalProtein > 0) {
        percentProtein = ((static_cast<double>(totalProtein) * 4) / totalCalories) * 100;
    }
    double percentCarb = 0.0;
    if (totalCarb > 0) {
        percentCarb = ((static_cast<double>(totalCarb) * 4) / totalCalories) * 100;
    }
    
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
    double multiplier = m_dailyView->getDailyMultiplier();
    std::vector<XrefDailyFood> xdfVector = m_dailyModel->getXrefDailyFoods(df);

    CalculatedMacros cm = calculateFoodMacros(food, multiplier);
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
    xdfVector.push_back(xdf);
    
    m_dailyModel->addXrefDailyFood(xdf);

    refresh();
}

void DailyPresenter::onAddDailyRecipe()
{
    spdlog::debug("DailyPresenter::onAddDailyRecipe");
    DailyFood df = m_dailyModel->getDailyFood();
    std::vector<Ingredient> ingredients = m_dailyModel->getIngredients();
    Recipe recipe = m_dailyModel->getRecipe();
    double multiplier = m_dailyView->getDailyMultiplier();
    std::vector<XrefDailyFood> xdfVector = m_dailyModel->getXrefDailyFoods(df);

    CalculatedMacros cm = calculateRecipeMacros(recipe.servings, ingredients, multiplier);
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

CalculatedMacros DailyPresenter::calculateFoodMacros(const Food &food, double multiplier)
{
    CalculatedMacros m{0, 0, 0, 0};
    double fatCalories = (food.fat * 9) * multiplier;
    double proteinCalories = (food.protein * 4) * multiplier;
    double carbCalories = (food.carb * 4) * multiplier;
    m.calories = fatCalories + proteinCalories + carbCalories;

    m.fatGrams = food.fat * multiplier;
    m.proteinGrams = food.protein * multiplier;
    m.carbGrams = food.carb * multiplier;

    return m;
}

CalculatedMacros DailyPresenter::calculateRecipeMacros(int servings, const std::vector<Ingredient> &ingredients, double multiplier)
{
    CalculatedMacros m{0, 0, 0, 0};
    auto totalFatGrams = calculateTotalFatGrams(ingredients);
    auto totalProteinGrams = calculateTotalProteinGrams(ingredients);
    auto totalCarbGrams = calculateTotalCarbGrams(ingredients);

    m.fatGrams = (totalFatGrams / servings) * multiplier;
    m.proteinGrams = (totalProteinGrams / servings) * multiplier;
    m.carbGrams = (totalCarbGrams / servings) * multiplier;

    auto fatCalories = (m.fatGrams * 9);
    auto proteinCalories = (m.proteinGrams * 4);
    auto carbCalories = (m.carbGrams * 4);
    m.calories = fatCalories + proteinCalories + carbCalories;

    return m;
}

double DailyPresenter::calculateTotalFatGrams(const std::vector<Ingredient> &ingredients)
{
    double totalFatGrams = 0;
    for (auto ingredient : ingredients)
    {
        if (ingredient.food.unit_id == ingredient.unit.id) {
            totalFatGrams += ingredient.food.fat * ingredient.unitMultiplier;
        } else {
            spdlog::warn("DEV ERROR: {} unit mismatch {} {}", ingredient.food.name, ingredient.food.unit_id, ingredient.unit.id);
        }
    }
    return totalFatGrams;
}

double DailyPresenter::calculateTotalProteinGrams(const std::vector<Ingredient> &ingredients)
{
    double totalProteinGrams = 0;
    for (auto ingredient : ingredients)
    {
        if (ingredient.food.unit_id == ingredient.unit.id) {
            totalProteinGrams += ingredient.food.protein * ingredient.unitMultiplier;
        } else {
            spdlog::warn("DEV ERROR: {} unit mismatch {} {}", ingredient.food.name, ingredient.food.unit_id, ingredient.unit.id);
        }
    }
    return totalProteinGrams;
}

double DailyPresenter::calculateTotalCarbGrams(const std::vector<Ingredient> &ingredients)
{
    double totalCarbGrams = 0;
    for (auto ingredient : ingredients)
    {
        if (ingredient.food.unit_id == ingredient.unit.id) {
            totalCarbGrams += ingredient.food.carb * ingredient.unitMultiplier;
        } else {
            spdlog::warn("DEV ERROR: {} unit mismatch {} {}", ingredient.food.name, ingredient.food.unit_id, ingredient.unit.id);
        }
    }
    return totalCarbGrams;
}

void DailyPresenter::onSelectedDailyFoodChanged(int id)
{
    spdlog::debug("DailyPresenter::onSelectedDailyFoodChanged {}", id);
    m_dailyModel->setSelectedDailyFoodId(id);
}

