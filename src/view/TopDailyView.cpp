#include "TopDailyView.h"
#include "../presenter/DailyPresenter.h"
// #include "../presenter/FoodListPresenter.h"
// #include "../presenter/RecipeListPresenter.h"
#include <spdlog/spdlog.h>

DailyView::DailyView(IDailyCallback *callback) 
: m_dailyCallback(callback)
{
}

wxPanel *DailyView::createDailyPanel(wxNotebook *parent)
{
    spdlog::debug("DailyView::createDailyPanel");
    wxPanel *panel = new wxPanel(parent);
    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

    topsizer->Add(new wxStaticText(panel, wxID_ANY, "Daily Food Diary"), 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, 5);
    m_datePicker = new wxDatePickerCtrl(panel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize(200, 20));
    m_datePicker->Bind(wxEVT_DATE_CHANGED, &DailyView::onDateChanged, this);
    topsizer->Add(m_datePicker, 0, wxALL, 10);

    wxBoxSizer *activitySizer = new wxBoxSizer(wxHORIZONTAL);
    activitySizer->Add(new wxStaticText(panel, wxID_ANY, "Activity Bonus"), 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    m_dailyActivityBonusTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    activitySizer->Add(m_dailyActivityBonusTextCtrl, 0, wxALL, 10);
    m_addActivityBonusButton = new wxButton(panel, -1, _T("Add"), wxDefaultPosition, wxDefaultSize, 0);
    m_addActivityBonusButton->Bind(wxEVT_BUTTON, &DailyView::onAddActivityBonus, this);
    activitySizer->Add(m_addActivityBonusButton, 0, wxALL, 10);
    topsizer->Add(activitySizer, 0, wxALL, 10);

    wxBoxSizer *addFoodSizer = new wxBoxSizer(wxHORIZONTAL);
    addFoodSizer->Add(new wxStaticText(panel, wxID_ANY, "Multiplier"), 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    m_foodMultiplierTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    addFoodSizer->Add(m_foodMultiplierTextCtrl, 0, wxALL, 10);
    m_addDailyFoodButton = new wxButton(panel, -1, _T("Add Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_addDailyFoodButton->Bind(wxEVT_BUTTON, &DailyView::onAddDailyFood, this);
    addFoodSizer->Add(m_addDailyFoodButton, 0, wxALL, 10);
    topsizer->Add(addFoodSizer, 0, wxALL, 10);

    m_dailyFoodListView = new wxListView(panel);
    m_dailyFoodListView->AppendColumn("Food Name");
    m_dailyFoodListView->AppendColumn("Calories");
    m_dailyFoodListView->AppendColumn("Fat");
    m_dailyFoodListView->AppendColumn("Protein");
    m_dailyFoodListView->AppendColumn("Carb");
    m_dailyFoodListView->SetColumnWidth(0, 320);
    m_dailyFoodListView->SetColumnWidth(1, 100);
    m_dailyFoodListView->SetColumnWidth(2, 100);
    m_dailyFoodListView->SetColumnWidth(3, 100);
    m_dailyFoodListView->SetColumnWidth(4, 100);
    topsizer->Add(m_dailyFoodListView, 1, wxEXPAND | wxALL, 10);

    m_deleteDailyFoodButton = new wxButton(panel, -1, _T("Delete Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_deleteDailyFoodButton->Bind(wxEVT_BUTTON, &DailyView::onDeleteDailyFood, this);
    topsizer->Add(m_deleteDailyFoodButton, 0, wxALL, 10);

    m_totalsListView = new wxListView(panel);
    m_totalsListView->AppendColumn("Food Name");
    m_totalsListView->AppendColumn("Calories");
    m_totalsListView->AppendColumn("Fat");
    m_totalsListView->AppendColumn("Protein");
    m_totalsListView->AppendColumn("Carb");
    m_totalsListView->SetColumnWidth(0, 320);
    m_totalsListView->SetColumnWidth(1, 100);
    m_totalsListView->SetColumnWidth(2, 100);
    m_totalsListView->SetColumnWidth(3, 100);
    m_totalsListView->SetColumnWidth(4, 100);
    topsizer->Add(m_totalsListView, 1, wxEXPAND | wxALL, 10);

    panel->SetSizer(topsizer);

    return panel;
}

void DailyView::postInit() {
}

void DailyView::onDateChanged(wxDateEvent& event) {
    spdlog::debug("DailyView::onDateChanged");
    // get the date from the event argument
    wxDateTime date = event.GetDate();
    // get the date as string in format &Y-&m-&d
    std::string dateStr = date.FormatISODate().ToStdString();
    spdlog::info("DailyView::onDateChanged {}", dateStr);
    
    m_dailyCallback->onDateChanged(dateStr);
}

void DailyView::onAddDailyFood(wxCommandEvent& event) {
    spdlog::debug("DailyView::onAddDailyFood");
}

void DailyView::onDeleteDailyFood(wxCommandEvent& event) {
    spdlog::debug("DailyView::onDeleteDailyFood");
}

void DailyView::onAddActivityBonus(wxCommandEvent& event) {
    spdlog::debug("DailyView::onAddActivityBonus");
}

void DailyView::setDailyActivityBonus(const std::string& bonus) {
    spdlog::debug("DailyView::setDailyActivityBonus");
    m_dailyActivityBonusTextCtrl->SetValue(bonus);
}

void DailyView::setDailyFoodList(const std::vector<XrefDailyFood> &xrefDailyFoods) {
    spdlog::debug("DailyView::setDailyFoodList");

    m_dailyFoodListView->DeleteAllItems();

    for (int i = 0; i < xrefDailyFoods.size(); i++) {
        m_dailyFoodListView->InsertItem(i, xrefDailyFoods[i].name);
        m_dailyFoodListView->SetItem(i, 1, std::to_string(xrefDailyFoods[i].calories));
        m_dailyFoodListView->SetItem(i, 2, std::to_string(xrefDailyFoods[i].fat));
        m_dailyFoodListView->SetItem(i, 3, std::to_string(xrefDailyFoods[i].protein));
        m_dailyFoodListView->SetItem(i, 4, std::to_string(xrefDailyFoods[i].carb));
    }
}

void DailyView::setTotalsList(const std::vector<XrefDailyFood> &totals) {
    spdlog::info("DailyView::setTotalsList size: {}", totals.size());

    m_totalsListView->DeleteAllItems();

    for (int i = 0; i < totals.size(); i++) {
        m_totalsListView->InsertItem(i, totals[i].name);
        m_totalsListView->SetItem(i, 1, std::to_string(totals[i].calories));
        m_totalsListView->SetItem(i, 2, std::to_string(totals[i].fat));
        m_totalsListView->SetItem(i, 3, std::to_string(totals[i].protein));
        m_totalsListView->SetItem(i, 4, std::to_string(totals[i].carb));
    }
}