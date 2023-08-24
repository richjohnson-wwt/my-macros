#ifndef MACRO_CALCULATOR_H
#define MACRO_CALCULATOR_H

#include "../model/MyMacroTypes.h"

class MacroCalculator {
public:
    double calculateFatPercent(double fatGrams, int totalCalories);
    double calculateProteinPercent(double proteinGrams, int totalCalories);
    double calculateCarbPercent(double carbGrams, int totalCalories);
    double calculateTotalFatGrams(const std::vector<Ingredient> &ingredients);
    double calculateTotalProteinGrams(const std::vector<Ingredient> &ingredients);
    double calculateTotalCarbGrams(const std::vector<Ingredient> &ingredients);
    CalculatedMacros calculateFoodMacros(const Food &food, double multiplier = 1.0);
    CalculatedMacros calculateRecipeMacros(
        int servings,
        const std::vector<Ingredient> &ingredients,
        double multiplier = 1.0);

};


#endif // MACRO_CALCULATOR_H