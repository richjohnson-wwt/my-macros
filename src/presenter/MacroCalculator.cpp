#include "MacroCalculator.h"
#include <spdlog/spdlog.h>

double MacroCalculator::calculateFatPercent(double fatGrams, int totalCalories) {
    double percentFat = 0.0;
    if (fatGrams > 0) {
        auto fatCal = totalCalories - (totalCalories - (fatGrams * 9));
        percentFat = ((static_cast<double>(fatCal)) / totalCalories) * 100;
    }
    return percentFat;
}

double MacroCalculator::calculateProteinPercent(double proteinGrams, int totalCalories) {
    double percentProtein = 0.0;
    if (proteinGrams > 0) {
        auto proteinCal = totalCalories - (totalCalories - (proteinGrams * 9));
        percentProtein = ((static_cast<double>(proteinCal)) / totalCalories) * 100;
    }
    return percentProtein;
}

double MacroCalculator::calculateCarbPercent(double carbGrams, int totalCalories) {
    double percentCarb = 0.0;
    if (carbGrams > 0) {
        auto carbCal = totalCalories - (totalCalories - (carbGrams * 9));
        percentCarb = ((static_cast<double>(carbCal)) / totalCalories) * 100;
    }
    return percentCarb;
}

CalculatedMacros MacroCalculator::calculateFoodMacros(const Food &food, double multiplier)
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


CalculatedMacros MacroCalculator::calculateRecipeMacros(int servings, const std::vector<Ingredient> &ingredients, double multiplier)
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

double MacroCalculator::calculateTotalFatGrams(const std::vector<Ingredient> &ingredients)
{
    double totalFatGrams = 0;
    for (auto ingredient : ingredients)
    {
        if (ingredient.food.unit_id == ingredient.unit.id) {
            totalFatGrams += ingredient.food.fat * ingredient.unitMultiplier;
        } else {
            spdlog::warn("MacroCalculator::calculateTotalFatGrams DEV ERROR: {} unit mismatch {} {}", ingredient.food.name, ingredient.food.unit_id, ingredient.unit.id);
        }
    }
    return totalFatGrams;
}

double MacroCalculator::calculateTotalProteinGrams(const std::vector<Ingredient> &ingredients)
{
    double totalProteinGrams = 0;
    for (auto ingredient : ingredients)
    {
        if (ingredient.food.unit_id == ingredient.unit.id) {
            totalProteinGrams += ingredient.food.protein * ingredient.unitMultiplier;
        } else {
            spdlog::warn("MacroCalculator::calculateTotalProteinGrams DEV ERROR: {} unit mismatch {} {}", ingredient.food.name, ingredient.food.unit_id, ingredient.unit.id);
        }
    }
    return totalProteinGrams;
}

double MacroCalculator::calculateTotalCarbGrams(const std::vector<Ingredient> &ingredients)
{
    double totalCarbGrams = 0;
    for (auto ingredient : ingredients)
    {
        if (ingredient.food.unit_id == ingredient.unit.id) {
            totalCarbGrams += ingredient.food.carb * ingredient.unitMultiplier;
        } else {
            spdlog::warn("MacroCalculator::calculateTotalCarbGrams DEV ERROR: {} unit mismatch {} {}", ingredient.food.name, ingredient.food.unit_id, ingredient.unit.id);
        }
    }
    return totalCarbGrams;
}
