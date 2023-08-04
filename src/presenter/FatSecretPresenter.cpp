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

// void FatSecretPresenter::onGetResult(const std::string& id)
// {
//     spdlog::debug("FatSecretPresenter::onGetResult");
//     FatSecret::GetFood getFood = m_fatSecretWrapper->getFood(id);
//     // m_fatSecretView->setGetResult(getFood);
// }
