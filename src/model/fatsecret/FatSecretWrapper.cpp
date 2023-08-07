#include "FatSecretWrapper.h"

#include "TokenJson.h"

#include <spdlog/spdlog.h>
#include <fstream>
#include <iostream>

FatSecretWrapper::FatSecretWrapper(IFatSecretModel *fatSecretModel)
    : m_fatSecretModel(fatSecretModel) {

}

void FatSecretWrapper::refreshToken()
{
    spdlog::info("FatSecretWrapper::refreshToken");
    auto token = m_curlWrapper.executeCurl(CurlWrapper::TOKEN_FETCH_COMMAND);
    writeTokenToFile(token);
    spdlog::info("Token written: {}", token);
}

void FatSecretWrapper::writeTokenToFile(const std::string &token)
{
    std::ofstream file("../src/data/token.json", std::ios::out | std::ios::trunc);
    file << token;
    file.close();
}

FatSecret::SearchFoods FatSecretWrapper::searchFoods(std::string &name)
{
    spdlog::info("FatSecretWrapper::searchFoods fetched {}", name);
    FatSecret::TokenJson tokenJson;
    auto token = tokenJson.parseToken();

    auto command = m_curlWrapper.assembleFoodSearchCommand(token, name);
    const std::string response = m_curlWrapper.executeCurl(command);

    auto searchFoods = m_fatSecretJson.handleSearchResponse(response);
    return searchFoods;
    
}

FatSecret::GetFood FatSecretWrapper::getFood(const std::string& id)
{
    spdlog::info("FatSecretWrapper::getFood: {}", id);
    FatSecret::TokenJson tokenJson;
    auto token = tokenJson.parseToken();

    FatSecret::SearchFood searchFood = m_fatSecretJson.retrieveFoodById(id);
    spdlog::debug("getFood from searchFood {}", searchFood.food_name);

    auto command = m_curlWrapper.assembleGetFoodCommand(token, searchFood.food_id);
    spdlog::debug("Curl Command for get food {}", command);

    const std::string response = m_curlWrapper.executeCurl(command);
    
    FatSecret::GetFood getFood = m_fatSecretJson.handleGetResponse(response);

    return getFood;
}

void FatSecretWrapper::addGetFoodToDb()
{
    spdlog::info("FatSecretWrapper::addGetFoodToDb");
    FatSecret::GetFood getFoodWithServingIndex = m_fatSecretJson.retrieveGetFood(0);

    Unit u = m_fatSecretModel->getUnit(getFoodWithServingIndex.servings.serving[0].metric_serving_unit);
    if (u.name == "NONE")
    {
        spdlog::error("Unit not found {}", getFoodWithServingIndex.servings.serving[0].metric_serving_unit);
    }
    Food f = m_transformer.convert(getFoodWithServingIndex, u);

    m_fatSecretModel->saveFood(f);
}
