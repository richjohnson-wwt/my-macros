#include "FoodItemView.h"
#include "../presenter/FoodPresenter.h"
#include <spdlog/spdlog.h>

FoodItemView::FoodItemView(IFoodCallback *callback)
    : m_foodCallback(callback)
{
}

wxSizer *FoodItemView::CreateTextWithLabelSizer(wxPanel *panel, const wxString &label, wxTextCtrl *text)
{
    wxSizer *sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(new wxStaticText(panel, wxID_ANY, label, wxDefaultPosition, wxSize(100, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
    sizerRow->Add(text, 0, wxALIGN_LEFT);
    return sizerRow;
}

wxPanel *FoodItemView::createFoodItemPanel(wxNotebook *parent)
{
    wxPanel *panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

    m_foodIdTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Food ID:", m_foodIdTextCtrl), 0, wxALL, 10);

    m_foodNameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Food Name:", m_foodNameTextCtrl), 0, wxALL, 10);

    m_foodFatTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Food Fat:", m_foodFatTextCtrl), 0, wxALL, 10);

    m_foodProteinTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Food Protein:", m_foodProteinTextCtrl), 0, wxALL, 10);

    m_foodCarbTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Food Carb:", m_foodCarbTextCtrl), 0, wxALL, 10);

    m_foodCaloriesTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Food Calories:", m_foodCaloriesTextCtrl), 0, wxALL, 10);

    m_foodQuantityTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Food Quantity:", m_foodQuantityTextCtrl), 0, wxALL, 10);

    wxSizer *comboSizerRow = new wxBoxSizer(wxHORIZONTAL);
    m_foodUnitComboBox = new wxComboBox(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    m_foodUnitComboBox->Bind(wxEVT_COMBOBOX, &FoodItemView::onFoodUnitComboBox, this);
    comboSizerRow->Add(new wxStaticText(panel, wxID_ANY, "Food Unit: ", wxDefaultPosition, wxSize(100, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
    comboSizerRow->Add(m_foodUnitComboBox, 0, wxALIGN_LEFT);
    topsizer->Add(comboSizerRow, 0, wxALL, 10);

    m_foodDeleteButton = new wxButton(panel, -1, _T("Delete Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_foodDeleteButton->Bind(wxEVT_BUTTON, &FoodItemView::onDeleteFood, this);

    m_foodSaveButton = new wxButton(panel, -1, _T("Save Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_foodSaveButton->Bind(wxEVT_BUTTON, &FoodItemView::onSaveFood, this);

    m_foodNewButton = new wxButton(panel, -1, _T("New Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_foodNewButton->Bind(wxEVT_BUTTON, &FoodItemView::onNewFood, this);

    m_foodNewCancelButton = new wxButton(panel, -1, _T("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
    m_foodNewCancelButton->Bind(wxEVT_BUTTON, &FoodItemView::onNewFoodCancel, this);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(m_foodDeleteButton, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    buttonSizer->Add(m_foodSaveButton, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    buttonSizer->Add(m_foodNewButton, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    buttonSizer->Add(m_foodNewCancelButton, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);

    topsizer->Add(buttonSizer, 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, 5);

    panel->SetSizer(topsizer);

    return panel;
}

void FoodItemView::onDeleteFood(wxCommandEvent &event)
{
    m_foodCallback->onDeleteFood();
}

void FoodItemView::onSaveFood(wxCommandEvent &event)
{
    m_foodCallback->onSaveFood();
}

void FoodItemView::onNewFood(wxCommandEvent &event)
{
    m_foodCallback->onNewFood();
}

void FoodItemView::onNewFoodCancel(wxCommandEvent &event)
{
    m_foodCallback->onNewFoodCancel();
}

void FoodItemView::onFoodUnitComboBox(wxCommandEvent &event)
{
}


void FoodItemView::setFoodId(const std::string &id)
{
    m_foodIdTextCtrl->SetValue(id);
}

void FoodItemView::setFoodName(const std::string &name)
{
    m_foodNameTextCtrl->SetValue(name);
}

void FoodItemView::setFoodFat(const std::string &fat)
{
    m_foodFatTextCtrl->SetValue(fat);
}

void FoodItemView::setFoodProtein(const std::string &protein)
{
    m_foodProteinTextCtrl->SetValue(protein);
}

void FoodItemView::setFoodCarb(const std::string &carb)
{
    m_foodCarbTextCtrl->SetValue(carb);
}

void FoodItemView::setFoodCalories(const std::string &calories)
{
    m_foodCaloriesTextCtrl->SetValue(calories);
}

void FoodItemView::setFoodQuantity(const std::string &quantity)
{
    m_foodQuantityTextCtrl->SetValue(quantity);
}

void FoodItemView::setFoodUnit(int unitId, const std::vector<Unit>& units)
{
    m_foodUnitComboBox->Clear();
    for (auto unit : units) {
        spdlog::debug("FoodItemView::setFoodUnit: {}", unit.name);
        m_foodUnitComboBox->Append(unit.name);
    }
    m_foodUnitComboBox->SetSelection(unitId - 1);
}

std::string FoodItemView::getFoodId()
{
    return m_foodIdTextCtrl->GetValue().ToStdString();
}

std::string FoodItemView::getFoodName()
{
    return m_foodNameTextCtrl->GetValue().ToStdString();
}

std::string FoodItemView::getFoodFat()
{
    return m_foodFatTextCtrl->GetValue().ToStdString();
}

std::string FoodItemView::getFoodProtein()
{
    return m_foodProteinTextCtrl->GetValue().ToStdString();
}

std::string FoodItemView::getFoodCarb()
{
    return m_foodCarbTextCtrl->GetValue().ToStdString();
}

std::string FoodItemView::getFoodCalories()
{
    return m_foodCaloriesTextCtrl->GetValue().ToStdString();
}

std::string FoodItemView::getFoodQuantity()
{
    return m_foodQuantityTextCtrl->GetValue().ToStdString();
}

int FoodItemView::getFoodUnitId()
{
    return m_foodUnitComboBox->GetSelection() + 1;
}


