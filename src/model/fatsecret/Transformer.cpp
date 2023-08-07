#include "Transformer.h"

#include <sstream>
#include <iostream>

Food Transformer::convert(const FatSecret::GetFood &getFood, Unit unit)
{
    Food f;
    f.id = std::stoi(getFood.food_id);
    f.name = getFood.brand_name + " " + getFood.food_name + " " + getFood.servings.serving[0].serving_description;
    auto serving = getFood.servings.serving[0];
    f.fat = std::rint(std::stod(serving.fat));
    f.carb = std::rint(std::stod(serving.carbohydrate) - std::stod(serving.fiber)); // BOOM take that mfp
    f.protein = std::rint(std::stod(serving.protein));
    f.calories = std::stoi(serving.calories);
    f.quantity = static_cast<double>(std::stod(serving.metric_serving_amount));
    f.popularity = 0;
    f.unit_id = unit.id;
    return f;
}
