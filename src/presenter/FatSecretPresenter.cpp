#include "FatSecretPresenter.h"

#include <spdlog/spdlog.h>

FatSecretPresenter::FatSecretPresenter(IFatSecretView *view, FatSecretWrapper *wrapper): m_fatSecretView(view), m_fatSecretWrapper(wrapper)
{
}

void FatSecretPresenter::onRefreshToken()
{
    spdlog::debug("FatSecretPresenter::onRefreshToken");
    m_fatSecretWrapper->refreshToken();
}

void FatSecretPresenter::onSearch(std::string& searchText)
{
    spdlog::debug("FatSecretPresenter::onSearch");
    FatSecret::SearchFoods searchFoods = m_fatSecretWrapper->searchFoods(searchText);
    m_fatSecretView->setSearchResults(searchFoods);
}

void FatSecretPresenter::onGetResult(const std::string& id)
{
    spdlog::debug("FatSecretPresenter::onGetResult");
    FatSecret::GetFood getFood = m_fatSecretWrapper->getFood(id);
    m_fatSecretView->setGetFoodName(getFood.food_name);
    m_fatSecretView->setGetFoodBrand(getFood.brand_name);
    m_fatSecretView->setGetFoodCalories(getFood.servings.serving[0].calories);
    m_fatSecretView->setGetFoodCarb(getFood.servings.serving[0].carbohydrate);
    m_fatSecretView->setGetFoodProtein(getFood.servings.serving[0].protein);
    m_fatSecretView->setGetFoodFat(getFood.servings.serving[0].fat);
    m_fatSecretView->setGetFoodMetricServingUnit(getFood.servings.serving[0].metric_serving_unit);
    m_fatSecretView->setGetFoodMetricServingAmount(getFood.servings.serving[0].metric_serving_amount);
    m_fatSecretView->setGetFoodServingDescription(getFood.servings.serving[0].serving_description);
    m_fatSecretView->setGetFoodFiber(getFood.servings.serving[0].fiber);
    
}

void FatSecretPresenter::onAddFoodToMyDatabase()
{
    spdlog::debug("FatSecretPresenter::onAddFoodToMyDatabase");
    m_fatSecretWrapper->addGetFoodToDb();
}