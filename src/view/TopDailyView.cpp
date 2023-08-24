#include "TopDailyView.h"
#include "../presenter/DailyPresenter.h"
#include "OneOffDialog.h"
#include <spdlog/spdlog.h>

DailyView::DailyView(IDailyCallback *callback) 
: m_dailyCallback(callback)
{
}

wxPanel *DailyView::createDailyPanel(wxNotebook *parent)
{
    spdlog::debug("DailyView::createDailyPanel");
    m_parent = parent;
    wxPanel *panel = new wxPanel(parent);
    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

    topsizer->Add(new wxStaticText(panel, wxID_ANY, "Daily Food Diary"), 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, 5);
    m_datePicker = new wxDatePickerCtrl(panel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxSize(100, 20));
    m_datePicker->Bind(wxEVT_DATE_CHANGED, &DailyView::onDateChanged, this);
    topsizer->Add(m_datePicker, 0, wxALL, 10);

    wxBoxSizer *activitySizer = new wxBoxSizer(wxHORIZONTAL);
    activitySizer->Add(new wxStaticText(panel, wxID_ANY, "Activity Bonus"), 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    m_dailyActivityBonusTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(75, 20));
    activitySizer->Add(m_dailyActivityBonusTextCtrl, 0, wxALL, 10);
    m_addActivityBonusButton = new wxButton(panel, -1, _T("Add Exercise"), wxDefaultPosition, wxDefaultSize, 0);
    m_addActivityBonusButton->Bind(wxEVT_BUTTON, &DailyView::onAddActivityBonus, this);
    activitySizer->Add(m_addActivityBonusButton, 0, wxALL, 10);
    activitySizer->Add(new wxStaticText(panel, wxID_ANY, "Weight"), 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    m_dailyWeightTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(75, 20));
    activitySizer->Add(m_dailyWeightTextCtrl, 0, wxALL, 10);
    m_addWeightButton = new wxButton(panel, -1, _T("Add Weight"), wxDefaultPosition, wxDefaultSize, 0);
    m_addWeightButton->Bind(wxEVT_BUTTON, &DailyView::onAddWeight, this);
    activitySizer->Add(m_addWeightButton, 0, wxALL, 10);
    topsizer->Add(activitySizer, 0, wxALL, 10);

    wxBoxSizer *addFoodSizer = new wxBoxSizer(wxHORIZONTAL);
    addFoodSizer->Add(new wxStaticText(panel, wxID_ANY, "Multiplier"), 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    m_multiplierUnitComboBox = new wxComboBox(panel, wxID_ANY, "", wxDefaultPosition, wxSize(75, 20));
    addFoodSizer->Add(m_multiplierUnitComboBox, 0, wxALL, 10);
    m_addDailyFoodButton = new wxButton(panel, -1, _T("Add Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_addDailyFoodButton->Bind(wxEVT_BUTTON, &DailyView::onAddDailyFood, this);
    m_addDailyRecipeButton = new wxButton(panel, -1, _T("Add Recipe"), wxDefaultPosition, wxDefaultSize, 0);
    m_addDailyRecipeButton->Bind(wxEVT_BUTTON, &DailyView::onAddDailyRecipe, this);
    m_oneOffButton = new wxButton(panel, -1, _T("One Off"), wxDefaultPosition, wxDefaultSize, 0);
    m_oneOffButton->Bind(wxEVT_BUTTON, &DailyView::onOneOff, this);

    addFoodSizer->Add(m_addDailyFoodButton, 0, wxALL, 10);
    addFoodSizer->Add(m_addDailyRecipeButton, 0, wxALL, 10);
    addFoodSizer->Add(m_oneOffButton, 0, wxALL, 10);
    topsizer->Add(addFoodSizer, 0, wxALL, 10);

    m_dailyFoodListView = new wxListView(panel);
    m_dailyFoodListView->AppendColumn("Id");
    m_dailyFoodListView->AppendColumn("Food Name");
    m_dailyFoodListView->AppendColumn("Calories");
    m_dailyFoodListView->AppendColumn("Fat g");
    m_dailyFoodListView->AppendColumn("Protein g");
    m_dailyFoodListView->AppendColumn("Carb g");
    m_dailyFoodListView->SetColumnWidth(0, 100);
    m_dailyFoodListView->SetColumnWidth(1, 320);
    m_dailyFoodListView->SetColumnWidth(2, 100);
    m_dailyFoodListView->SetColumnWidth(3, 100);
    m_dailyFoodListView->SetColumnWidth(4, 100);
    m_dailyFoodListView->SetColumnWidth(5, 100);
    m_dailyFoodListView->Bind(wxEVT_LIST_ITEM_SELECTED, &DailyView::onSelectDailyFood, this);
    topsizer->Add(m_dailyFoodListView, 1, wxEXPAND | wxALL, 10);

    m_deleteDailyFoodButton = new wxButton(panel, -1, _T("Delete Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_deleteDailyFoodButton->Bind(wxEVT_BUTTON, &DailyView::onDeleteDailyFood, this);
    topsizer->Add(m_deleteDailyFoodButton, 0, wxALL, 10);

    m_totalsListView = new wxListView(panel);
    m_totalsListView->SetMaxSize(wxSize(2000, 100));
    m_totalsListView->AppendColumn("Food Name");
    m_totalsListView->AppendColumn("Calories");
    m_totalsListView->AppendColumn("Fat g");
    m_totalsListView->AppendColumn("Protein g");
    m_totalsListView->AppendColumn("Carb g");
    m_totalsListView->SetColumnWidth(0, 320);
    m_totalsListView->SetColumnWidth(1, 100);
    m_totalsListView->SetColumnWidth(2, 100);
    m_totalsListView->SetColumnWidth(3, 100);
    m_totalsListView->SetColumnWidth(4, 100);
    topsizer->Add(m_totalsListView, 1, wxEXPAND | wxRIGHT, 10);

    wxBoxSizer *percentsSizer = new wxBoxSizer(wxHORIZONTAL);
    percentsSizer->Add(new wxStaticText(panel, wxID_ANY, "Percent Fat"), 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    m_fatPercent = new wxStaticText(panel, wxID_ANY, "0%", wxDefaultPosition, wxSize(200, 20));
    percentsSizer->Add(m_fatPercent, 0, wxALL, 10);
    percentsSizer->Add(new wxStaticText(panel, wxID_ANY, "Percent Protein"), 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    m_proteinPercent = new wxStaticText(panel, wxID_ANY, "0%", wxDefaultPosition, wxSize(200, 20));
    percentsSizer->Add(m_proteinPercent, 0, wxALL, 10);
    percentsSizer->Add(new wxStaticText(panel, wxID_ANY, "Percent Carb"), 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    m_carbPercent = new wxStaticText(panel, wxID_ANY, "0%", wxDefaultPosition, wxSize(200, 20));
    percentsSizer->Add(m_carbPercent, 0, wxALL, 10);
    topsizer->Add(percentsSizer, 0, wxALL, 10);

    panel->SetSizer(topsizer);

    return panel;
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
    m_dailyCallback->onAddDailyFood();
}

void DailyView::onAddDailyRecipe(wxCommandEvent& event) {
    spdlog::debug("DailyView::onAddDailyRecipe");
    m_dailyCallback->onAddDailyRecipe();
}

void DailyView::onOneOff(wxCommandEvent &event)
{
    spdlog::debug("DailyView::onOneOff");
    m_dailyCallback->onOneOff();
}

void DailyView::onDeleteDailyFood(wxCommandEvent& event) {
    spdlog::debug("DailyView::onDeleteDailyFood");
    m_dailyCallback->onDeleteDailyFood();
}

void DailyView::onAddActivityBonus(wxCommandEvent& event) {
    spdlog::debug("DailyView::onAddActivityBonus");
    m_dailyCallback->onAddExercise();
}

void DailyView::onAddWeight(wxCommandEvent& event) {
    spdlog::debug("DailyView::onAddWeight");
    m_dailyCallback->onAddWeight();
}

void DailyView::onSelectDailyFood(wxListEvent& event) {
    wxListItem item = event.GetItem();
    int id = wxAtoi(item.GetText());
    spdlog::info("DailyView::onSelectDailyFood {}", id);
    m_dailyCallback->onSelectedDailyFoodChanged(id);
}

void DailyView::setDailyActivityBonus(const std::string& bonus) {
    spdlog::debug("DailyView::setDailyActivityBonus");
    m_dailyActivityBonusTextCtrl->SetValue(bonus);
}

void DailyView::setDailyWeight(const std::string& weight) {
    m_dailyWeightTextCtrl->SetValue(weight);
}

void DailyView::setDailyFoodList(const std::vector<XrefDailyFood> &xrefDailyFoods) {
    spdlog::debug("DailyView::setDailyFoodList");

    m_dailyFoodListView->DeleteAllItems();

    for (int i = 0; i < xrefDailyFoods.size(); i++) {
        m_dailyFoodListView->InsertItem(i, std::to_string(xrefDailyFoods[i].id));
        m_dailyFoodListView->SetItem(i, 1, xrefDailyFoods[i].name);
        m_dailyFoodListView->SetItem(i, 2, std::to_string(xrefDailyFoods[i].calories));
        m_dailyFoodListView->SetItem(i, 3, std::to_string(xrefDailyFoods[i].fat));
        m_dailyFoodListView->SetItem(i, 4, std::to_string(xrefDailyFoods[i].protein));
        m_dailyFoodListView->SetItem(i, 5, std::to_string(xrefDailyFoods[i].carb));
    }
}

void DailyView::setTotalsList(const std::vector<XrefDailyFood> &totals, int percentFat, int percentProtein, int percentCarb) {
    spdlog::debug("DailyView::setTotalsList size: {}", totals.size());

    m_totalsListView->DeleteAllItems();

    for (int i = 0; i < totals.size(); i++) {
        m_totalsListView->InsertItem(i, totals[i].name);
        m_totalsListView->SetItem(i, 1, std::to_string(totals[i].calories));
        m_totalsListView->SetItem(i, 2, std::to_string(totals[i].fat));
        m_totalsListView->SetItem(i, 3, std::to_string(totals[i].protein));
        m_totalsListView->SetItem(i, 4, std::to_string(totals[i].carb));
    }

    m_fatPercent->SetLabel(std::to_string(percentFat) + "%");
    m_proteinPercent->SetLabel(std::to_string(percentProtein) + "%");
    m_carbPercent->SetLabel(std::to_string(percentCarb) + "%");
}

int DailyView::getActivityBonus() {
    spdlog::debug("DailyView::getActivityBonus");
    return std::stoi(m_dailyActivityBonusTextCtrl->GetValue().ToStdString());
}

double DailyView::getWeight() {
    return std::stod(m_dailyWeightTextCtrl->GetValue().ToStdString());
}

int DailyView::getDailyMultiplier() {
    spdlog::debug("DailyView::getDailyMultiplier");
    return m_multiplierUnitComboBox->GetSelection();
}

void DailyView::warnFutureDate() {
    wxMessageBox("You cannot enter data for a future date", "Warning", wxICON_WARNING);
}

void DailyView::resetDailyMultiplier(const std::vector<std::string> &increments, int defaultIndex) {
    spdlog::debug("DailyView::resetDailyMultiplier");
    m_multiplierUnitComboBox->Clear();
    for (auto i : increments) {
        m_multiplierUnitComboBox->Append(i);
    }
    m_multiplierUnitComboBox->SetSelection(defaultIndex);
}

XrefDailyFood DailyView::promptUserForOneOff()
{
    spdlog::info("DailyView::promptUserForOneOff");
    OneOffDialog oneOffDialog(m_parent, wxID_ANY, "Enter One-off data");
    if (oneOffDialog.ShowModal() == wxID_OK) {
        XrefDailyFood xfd;
        xfd.name = oneOffDialog.getName();
        xfd.calories = wxAtoi(oneOffDialog.getCalories());
        xfd.fat = wxAtoi(oneOffDialog.getFat());
        xfd.protein = wxAtoi(oneOffDialog.getProtein());
        xfd.carb = wxAtoi(oneOffDialog.getCarb());
        return xfd;
    } else {
        spdlog::info("DailyView::promptUserForOneOff cancelled");
    }
    return XrefDailyFood();
}
