#include "FatSecretView.h"
#include "../presenter/FatSecretPresenter.h"

#include <spdlog/spdlog.h>

FatSecretView::FatSecretView(IFatSecretCallback *callback): m_fatSecretCallback(callback)
{
}

wxPanel *FatSecretView::createPanel(wxBookCtrlBase *parent)
{
    spdlog::debug("FatSecretView::createPanel");
    wxPanel *panel = new wxPanel(parent);
    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
    m_refreshTokenButton = new wxButton(panel, wxID_ANY, _T("Refresh Token"), wxDefaultPosition, wxDefaultSize, 0);
    m_refreshTokenButton->Bind(wxEVT_BUTTON, &FatSecretView::onRefreshToken, this);
    topsizer->Add(m_refreshTokenButton, wxSizerFlags().Align(wxALIGN_RIGHT).Border(wxALL & ~wxBOTTOM, 5));

    wxBoxSizer *searchSizer = new wxBoxSizer(wxHORIZONTAL);
    m_searchText = new wxSearchCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHORIZONTAL);
    m_searchText->ShowCancelButton(1);
    m_searchText->Bind(wxEVT_SEARCHCTRL_SEARCH_BTN, &FatSecretView::onSearch, this);
    m_searchText->Bind(wxEVT_SEARCHCTRL_CANCEL_BTN, &FatSecretView::onSearchCancel, this);
    searchSizer->Add(m_searchText, 0, wxALL, 10);

    wxBoxSizer *listSizer = new wxBoxSizer(wxVERTICAL);
    m_searchListCtrl = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT);
    wxListItem itemCol;
    itemCol.SetId(0);
    itemCol.SetColumn(0);
    m_searchListCtrl->InsertColumn(0, "Food ID", itemCol, 100);
    m_searchListCtrl->InsertColumn(1, "Food Name", itemCol, 200);
    m_searchListCtrl->InsertColumn(2, "Food Description", itemCol, 500);
    listSizer->Add(m_searchListCtrl, 1, wxEXPAND | wxALL, 10);

    m_getResultButton = new wxButton(panel, wxID_ANY, _T("Get Result"), wxDefaultPosition, wxDefaultSize, 0);
    m_getResultButton->Bind(wxEVT_BUTTON, &FatSecretView::onGetResult, this);
    topsizer->Add(m_getResultButton, wxSizerFlags().Align(wxALIGN_RIGHT).Border(wxALL & ~wxBOTTOM, 5));

    topsizer->Add(searchSizer, wxSizerFlags().Proportion(0).Expand().Border(wxALL, 10));
    topsizer->Add(listSizer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 10));

    panel->SetSizer(topsizer);

    return panel;
}

void FatSecretView::setSearchResults(const FatSecret::SearchFoods &searchFoods)
{
    for (int i = 0; i < searchFoods.food.size(); i++)
    {
        int imageIndex = 0;
        long list_index = m_searchListCtrl->InsertItem(i, searchFoods.food[i].food_id, imageIndex);
        m_searchListCtrl->SetItem(list_index, 1, searchFoods.food[i].food_name);
        m_searchListCtrl->SetItem(list_index, 2, searchFoods.food[i].food_description);
    }
    m_searchListCtrl->Show();
}

// void FatSecretView::setGetResult(const FatSecret::GetFood &getFood)
// {
//     m_foodIdSelected = number;
//       FatSecret::GetFood getFood = m_fatSecretWrapper.getFood(std::string(foodId));
//       m_getFoodName->SetValue(getFood.food_name);
//       m_getFoodBrand->SetValue(getFood.brand_name);
//       m_getFoodCalories->SetValue(getFood.servings.serving[0].calories);
//       m_getFoodCarb->SetValue(getFood.servings.serving[0].carbohydrate);
//       m_getFoodFat->SetValue(getFood.servings.serving[0].fat);
//       m_getFoodProtein->SetValue(getFood.servings.serving[0].protein);
//       m_getFoodMetricServingUnit->SetValue(getFood.servings.serving[0].metric_serving_unit);
//       m_getFoodMetricServingAmount->SetValue(getFood.servings.serving[0].metric_serving_amount);
//       m_getFoodServingDescription->SetValue(getFood.servings.serving[0].serving_description);
//       m_getFoodFiber->SetValue(getFood.servings.serving[0].fiber);
// }

void FatSecretView::onRefreshToken(wxCommandEvent &event) {
    spdlog::debug("onRefreshToken");
    m_fatSecretCallback->onRefreshToken();
}

void FatSecretView::onAddFood(wxCommandEvent &event) {
    spdlog::debug("onAddFood");
}

void FatSecretView::onSearch(wxCommandEvent& event) {
    spdlog::debug("onSearch");
    const wxString searchText = m_searchText->GetValue();
    wxLogMessage("FatSecretPanel::onSearch: %s", searchText);
    auto stdStringSearchText = std::string(searchText);
    m_fatSecretCallback->onSearch(stdStringSearchText);
}

void FatSecretView::onSearchCancel(wxCommandEvent& event) {
    spdlog::debug("onSearchCancel");
}

void FatSecretView::onGetResult(wxCommandEvent &event)
{
    spdlog::debug("FatSecretView::onGetResult");
    long item = m_searchListCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (item == -1)
    {
        return;
    }
    else
    {
        auto foodId = m_searchListCtrl->GetItemText(item, 0);
        wxString number(foodId);
        long value;
        if (!number.ToLong(&value))
        {
            wxLogMessage("Unable to convert string to long {}", number);
            return;
        }
        wxLogMessage("Food ID: %s", foodId);
        // m_fatSecretCallback->onGetResult(foodId);
    }
}
