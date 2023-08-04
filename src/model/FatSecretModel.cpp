#include "FatSecretModel.h"

#include <spdlog/spdlog.h>
#include <iostream>
#include <sstream>

using json = nlohmann::json;

namespace FatSecret
{
    // BEGIN SEARCH JSON
    void to_json(json &j, const SearchFood &food)
    {
        j = json{
            {"food_description", food.food_description},
            {"food_id", food.food_id},
            {"food_name", food.food_name},
            {"food_type", food.food_type},
            {"food_url", food.food_url}};
    }

    void from_json(const json &j, SearchFood &food)
    {
        food.food_id = j.at("food_id").get<std::string>();
        food.food_description = j.at("food_description").get<std::string>();
        food.food_name = j.at("food_name").get<std::string>();
        food.food_type = j.at("food_type").get<std::string>();
        food.food_url = j.at("food_url").get<std::string>();
    }

    void to_json(json &j, const SearchFoods &foods)
    {
        j = json{
            {"food", foods.food},
            {"max_results", foods.max_results},
            {"page_number", foods.page_number},
            {"total_results", foods.total_results}};
    }

    void from_json(const json &j, SearchFoods &foods)
    {

        foods.food = j.at("food").get<vector<SearchFood>>();
        foods.max_results = j.at("max_results").get<std::string>();
        foods.page_number = j.at("page_number").get<std::string>();
        foods.total_results = j.at("total_results").get<std::string>();
    }

    // END SEARCH JSON

    // BEGIN GET JSON
    void to_json(json &j, const Serving &food)
    {
        j = json{
            {"food_description", food.calories},
            {"food_id", food.carbohydrate},
            {"food_name", food.fat},
            {"food_type", food.protein},
            {"food_url", food.metric_serving_unit},
            {"food_url", food.metric_serving_amount},
            {"food_url", food.fiber},
            {"serving_description", food.serving_description}};

    }

    void from_json(const json &j, Serving &food)
    {
        food.calories = j.at("calories").get<std::string>();
        food.carbohydrate = j.at("carbohydrate").get<std::string>();
        food.fat = j.at("fat").get<std::string>();
        food.protein = j.at("protein").get<std::string>();
        food.metric_serving_unit = j.at("metric_serving_unit").get<std::string>();
        food.metric_serving_amount = j.at("metric_serving_amount").get<std::string>();
        food.fiber = j.value("fiber", std::string("0"));
        food.serving_description = j.at("serving_description").get<std::string>();
    }

    void to_json(json &j, const Servings &servings)
    {
        j = json{
            {"serving", servings.serving}
        };
    }

    void from_json(const json &j, Servings &servings)
    {
        servings.serving = j.at("serving").get<vector<Serving>>();
    }

    void to_json(json &j, const GetFood &foods)
    {
        j = json{
            {"servings", foods.servings},
            {"food_id", foods.food_id},
            {"food_name", foods.food_name},
            {"brand_name", foods.brand_name}};
    }

    void from_json(const json &j, GetFood &food)
    {
        food.servings = j.at("servings").get<Servings>();
        food.food_id = j.at("food_id").get<std::string>();
        food.food_name = j.at("food_name").get<std::string>();
        food.brand_name = j.value("brand_name", std::string("Generic"));
    }

    // END GET JSON



    SearchFoods FatSecretModel::handleSearchResponse(const std::string &response)
    {
        // write response to ../src/data/search_food.json
        // std::ofstream ofs("../src/data/search_food.json", std::ios::out | std::ios::trunc);
        try {
            json j = json::parse(response);
            m_searchFoodsResponse = j["foods"];
            // ofs << j;
            // ofs.close();
        } catch (nlohmann::json_abi_v3_11_2::detail::type_error& e) {
            spdlog::error(e.what());
            spdlog::error("Error response: {}", response);
        }

        return m_searchFoodsResponse;
    }

    SearchFood FatSecretModel::retrieveFoodById(std::string foodId)
    {
        spdlog::debug("SearchResultJson::retrieveFoodById {}", foodId);
        // std::ifstream ifs(foodJsonFile);
        // json j = json::parse(ifs);
        // m_searchFoodsResponse = j["foods"];
        for (auto food : m_searchFoodsResponse.food)
        {
            if (food.food_id == foodId)
            {
                return food;
            }
        }
        spdlog::error("SearchResultJson::retrieveFoodById Food not found");
        return FatSecret::SearchFood();
    }

    GetFood FatSecretModel::handleGetResponse(const string &response)
    {
        // std::ofstream ofs("../src/data/get_food.json", std::ios::out | std::ios::trunc);
        json j = json::parse(response);
        m_getFoodResponse = j["food"];
        // ofs << j;
        // ofs.close();
        return m_getFoodResponse;
    }

    GetFood FatSecretModel::retrieveGetFood(int servingIndex)
    {
        // std::ifstream ifs(getFoodJsonFile);
        // json j = json::parse(ifs);
        // GetFood food = j["food"];
        // auto serving = m_getFoodResponse.servings.serving[servingIndex];

        // GetFood newFood;
        // newFood.brand_name = food.brand_name;
        // newFood.food_id = food.food_id;
        // newFood.food_name = food.food_name;
        // newFood.servings.serving.push_back(serving);
        
        return m_getFoodResponse;
    }

} // namespace Macro