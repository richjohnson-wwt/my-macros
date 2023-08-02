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

#endif // MY_MACRO_TYPES_H