#ifndef MY_MACRO_TYPES_H
#define MY_MACRO_TYPES_H

#include <string>


struct Unit
{
    int id;
    std::string name;
};

struct Food
{
    int id;
    std::string name;
    int fat;
    int protein;
    int carb;
    int calories;
    double quantity;
    int unit_id;
    int popularity;
};

struct Recipe
{
    int id;
    std::string name;
    std::string description;
    std::string instructions;
    std::string url;
    int servings;
};

struct Ingredient
{
    Food food;
    double unitMultiplier;
    Unit unit;
};

struct XrefRecipeFood
{
    int recipeId;
    int foodId;
    int amount;
    int unitId;
};

struct DailyFood
{
    int id;
    std::string date;
    int dailyActivityBonusCalories;
};

struct XrefDailyFood
{
    int id;
    int dailyFoodId;
    std::string name;
    int fat;
    int protein;
    int carb;
    int calories;
};

#endif // MY_MACRO_TYPES_H