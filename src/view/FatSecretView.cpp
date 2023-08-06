#include "FatSecretView.h"
#include "../presenter/FatSecretPresenter.h"

#include <spdlog/spdlog.h>

FatSecretView::FatSecretView(IFatSecretCallback *callback) : m_fatSecretCallback(callback)
{
}

wxPanel *FatSecretView::createPanel(wxNotebook *parent)
{
    spdlog::debug("FatSecretView::createPanel");
    wxPanel *panel = new wxPanel(parent);
    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

    m_refreshTokenButton = new wxButton(panel, wxID_ANY, _T("Refresh Token"), wxDefaultPosition, wxDefaultSize, 0);
    m_refreshTokenButton->Bind(wxEVT_BUTTON, &FatSecretView::onRefreshToken, this);
    topsizer->Add(m_refreshTokenButton, 0, wxALL, 10);

    // Search section
    m_searchText = new wxSearchCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 20), wxHORIZONTAL);
    m_searchText->ShowCancelButton(1);
    m_searchText->Bind(wxEVT_SEARCHCTRL_SEARCH_BTN, &FatSecretView::onSearch, this);
    m_searchText->Bind(wxEVT_SEARCHCTRL_CANCEL_BTN, &FatSecretView::onSearchCancel, this);
    topsizer->Add(m_searchText, 0, wxALL, 10);

    m_searchListView = new wxListView(panel);
    m_searchListView->Bind(wxEVT_LIST_ITEM_SELECTED, &FatSecretView::onGetResult, this);
    m_searchListView->AppendColumn("Food ID", wxLIST_FORMAT_LEFT, 100);
    m_searchListView->AppendColumn("Food Name", wxLIST_FORMAT_LEFT, 200);
    m_searchListView->AppendColumn("Food Description", wxLIST_FORMAT_LEFT, 500);
    m_searchListView->SetColumnWidth(0, 100);
    m_searchListView->SetColumnWidth(1, 200);
    m_searchListView->SetColumnWidth(2, 500);
    topsizer->Add(m_searchListView, 5, wxEXPAND | wxALL, 10); // 5!!!! Greater proportion than the rest
    
    // Get section
    wxBoxSizer *boxSectionSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *getRowSizer1 = new wxBoxSizer(wxHORIZONTAL);

    m_getFoodName = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 20), 0);
    getRowSizer1->Add(CreateTextWithLabelSizer(panel, _T("Food Name: "), m_getFoodName), 0, wxALL, 5);

    m_getFoodBrand = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 20), 0);
    getRowSizer1->Add(CreateTextWithLabelSizer(panel, _T("Brand: "), m_getFoodBrand), 0, wxALL, 5);

    boxSectionSizer->Add(getRowSizer1, 0, wxALL, 5);

    wxBoxSizer *getRowSizer2 = new wxBoxSizer(wxHORIZONTAL);
    m_getFoodCalories = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 20), 0);
    getRowSizer2->Add(CreateTextWithLabelSizer(panel, _T("Calories: "), m_getFoodCalories), 0, wxALL, 5);

    m_getFoodCarb = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 20), 0);
    getRowSizer2->Add(CreateTextWithLabelSizer(panel, _T("Carb: "), m_getFoodCarb), 0, wxALL, 5);

    boxSectionSizer->Add(getRowSizer2, 0, wxALL, 5);

    wxBoxSizer *getRowSizer3 = new wxBoxSizer(wxHORIZONTAL);
    m_getFoodProtein = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 20), 0);
    getRowSizer3->Add(CreateTextWithLabelSizer(panel, _T("Protein: "), m_getFoodProtein), 0, wxALL, 5);

    m_getFoodFat = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 20), 0);
    getRowSizer3->Add(CreateTextWithLabelSizer(panel, _T("Fat: "), m_getFoodFat), 0, wxALL, 5);

    boxSectionSizer->Add(getRowSizer3, 0, wxALL, 5);

    wxBoxSizer *getRowSizer4 = new wxBoxSizer(wxHORIZONTAL);
    m_getFoodMetricServingUnit = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 20), 0);
    getRowSizer4->Add(CreateTextWithLabelSizer(panel, _T("Metric Serving Unit: "), m_getFoodMetricServingUnit), 0, wxALL, 5);

    m_getFoodMetricServingAmount = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 20), 0);
    getRowSizer4->Add(CreateTextWithLabelSizer(panel, _T("Metric Serving Amount: "), m_getFoodMetricServingAmount), 0, wxALL, 5);

    boxSectionSizer->Add(getRowSizer4, 0, wxALL, 5);

    wxBoxSizer *getRowSizer5 = new wxBoxSizer(wxHORIZONTAL);
    m_getFoodServingDescription = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 20), 0);
    getRowSizer5->Add(CreateTextWithLabelSizer(panel, _T("Serving Description: "), m_getFoodServingDescription), 0, wxALL, 5);

    m_getFoodFiber = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 20), 0);
    getRowSizer5->Add(CreateTextWithLabelSizer(panel, _T("Fiber: "), m_getFoodFiber), 0, wxALL, 5);

    boxSectionSizer->Add(getRowSizer5, 0, wxALL, 5);

    topsizer->Add(boxSectionSizer, 1, wxALL, 5);

    m_addToMyDatabase = new wxButton(panel, wxID_ANY, _T("Add To My Database"), wxDefaultPosition, wxDefaultSize, 0);
    m_addToMyDatabase->Bind(wxEVT_BUTTON, &FatSecretView::onAddFoodToMyDatabase, this);
    topsizer->Add(m_addToMyDatabase, 0, wxALL, 10);

    panel->SetSizer(topsizer);

    return panel;
}

wxSizer *FatSecretView::CreateTextWithLabelSizer(wxPanel *panel, const wxString &label, wxTextCtrl *text)
{
    wxSizer *sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(new wxStaticText(panel, wxID_ANY, label, wxDefaultPosition, wxSize(100, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
    sizerRow->Add(text, 0, wxALIGN_LEFT);
    return sizerRow;
}

void FatSecretView::onAddFoodToMyDatabase(wxCommandEvent &event)
{
    spdlog::debug("onAddFoodToMyDatabase");
    m_fatSecretCallback->onAddFoodToMyDatabase();
}

void FatSecretView::setSearchResults(const FatSecret::SearchFoods &searchFoods)
{
    for (int i = 0; i < searchFoods.food.size(); i++)
    {
        int imageIndex = 0;
        long list_index = m_searchListView->InsertItem(i, searchFoods.food[i].food_id, imageIndex);
        m_searchListView->SetItem(list_index, 1, searchFoods.food[i].food_name);
        m_searchListView->SetItem(list_index, 2, searchFoods.food[i].food_description);
    }
    m_searchListView->Show();
}

void FatSecretView::setGetFoodName(const std::string &name)
{
    m_getFoodName->SetValue(name);
}

void FatSecretView::setGetFoodBrand(const std::string &brand)
{
    m_getFoodBrand->SetValue(brand);
}

void FatSecretView::setGetFoodCalories(const std::string &calories)
{
    m_getFoodCalories->SetValue(calories);
}

void FatSecretView::setGetFoodCarb(const std::string &carb)
{
    m_getFoodCarb->SetValue(carb);
}

void FatSecretView::setGetFoodProtein(const std::string &protein)
{
    m_getFoodProtein->SetValue(protein);
}

void FatSecretView::setGetFoodFat(const std::string &fat)
{
    m_getFoodFat->SetValue(fat);
}

void FatSecretView::setGetFoodMetricServingUnit(const std::string &metricServingUnit)
{
    m_getFoodMetricServingUnit->SetValue(metricServingUnit);
}

void FatSecretView::setGetFoodMetricServingAmount(const std::string &metricServingAmount)
{
    m_getFoodMetricServingAmount->SetValue(metricServingAmount);
}

void FatSecretView::setGetFoodServingDescription(const std::string &servingDescription)
{
    m_getFoodServingDescription->SetValue(servingDescription);
}

void FatSecretView::setGetFoodFiber(const std::string &fiber)
{
    m_getFoodFiber->SetValue(fiber);
}

void FatSecretView::onRefreshToken(wxCommandEvent &event)
{
    spdlog::debug("onRefreshToken");
    m_fatSecretCallback->onRefreshToken();
}

void FatSecretView::onAddFood(wxCommandEvent &event)
{
    spdlog::debug("onAddFood");
}

void FatSecretView::onSearch(wxCommandEvent &event)
{
    spdlog::debug("onSearch");
    const wxString searchText = m_searchText->GetValue();
    wxLogMessage("FatSecretPanel::onSearch: %s", searchText);
    auto stdStringSearchText = std::string(searchText);
    m_fatSecretCallback->onSearch(stdStringSearchText);
}

void FatSecretView::onSearchCancel(wxCommandEvent &event)
{
    spdlog::debug("onSearchCancel");
}

void FatSecretView::onGetResult(wxCommandEvent &event)
{
    spdlog::debug("FatSecretView::onGetResult");
    long item = m_searchListView->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (item == -1)
    {
        return;
    }
    else
    {
        auto foodId = m_searchListView->GetItemText(item, 0);
        wxString number(foodId);
        long value;
        if (!number.ToLong(&value))
        {
            wxLogMessage("Unable to convert string to long {}", number);
            return;
        }
        wxLogMessage("Food ID: %s", foodId);
        m_fatSecretCallback->onGetResult(std::string(foodId));
    }
}
