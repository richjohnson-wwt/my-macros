#include "FoodItemEditView.h"
#include "../presenter/FoodEditPresenter.h"
#include <spdlog/spdlog.h>

FoodItemEditView::FoodItemEditView(IFoodEditCallback *callback)
    : m_foodCallback(callback)
{
}

wxSizer *FoodItemEditView::CreateTextWithLabelSizer(wxPanel *panel, const wxString &label, wxTextCtrl *text)
{
    wxSizer *sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(new wxStaticText(panel, wxID_ANY, label, wxDefaultPosition, wxSize(100, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
    sizerRow->Add(text, 0, wxALIGN_LEFT);
    return sizerRow;
}

wxPanel *FoodItemEditView::createFoodItemEditPanel(wxNotebook *parent)
{
    spdlog::info("FoodItemEditView::createFoodItemEditPanel");
    m_parent = parent;
    wxPanel *panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));
    spdlog::info("FoodItemEditView::createFoodItemEditPanel2");
    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

    m_foodIdTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20), wxTE_READONLY);
    // m_foodIdTextCtrl->SetReadOnly(true);
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
    m_foodUnitComboBox->Bind(wxEVT_COMBOBOX, &FoodItemEditView::onFoodUnitComboBox, this);
    comboSizerRow->Add(new wxStaticText(panel, wxID_ANY, "Food Unit: ", wxDefaultPosition, wxSize(100, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
    comboSizerRow->Add(m_foodUnitComboBox, 0, wxALIGN_LEFT);
    topsizer->Add(comboSizerRow, 0, wxALL, 10);

    m_foodSaveButton = new wxButton(panel, -1, _T("Save Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_foodSaveButton->Bind(wxEVT_BUTTON, &FoodItemEditView::onSaveFood, this);

    m_foodNewCancelButton = new wxButton(panel, -1, _T("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
    m_foodNewCancelButton->Bind(wxEVT_BUTTON, &FoodItemEditView::onNewFoodCancel, this);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(m_foodSaveButton, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    buttonSizer->Add(m_foodNewCancelButton, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);

    topsizer->Add(buttonSizer, 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, 5);

    panel->SetSizer(topsizer);

    return panel;
}

void FoodItemEditView::initNewPage(bool isNew) {
    if (isNew) {
        spdlog::info("FoodItemEditView::initNewPage");
        m_foodCallback->initNewPage();
    } else {
        spdlog::info("FoodItemEditView::initEditPage");
        m_foodCallback->initEditPage();
    }
}

void FoodItemEditView::deleteThisPage()
{
    if ( m_parent )
    {
        int sel = m_parent->GetSelection();

        if (sel != wxNOT_FOUND)
        {
            m_parent->DeletePage(sel);
            m_parent->SetSelection(1);
            m_parent->SetSelection(0);
        }
    }
}

void FoodItemEditView::onSaveFood(wxCommandEvent &event)
{
    m_foodCallback->onSaveFood();
    deleteThisPage();
}

void FoodItemEditView::onNewFoodCancel(wxCommandEvent &event)
{
    m_foodCallback->onNewFoodCancel();
    deleteThisPage();
}

void FoodItemEditView::onFoodUnitComboBox(wxCommandEvent &event)
{
}

void FoodItemEditView::setFoodId(const std::string &id)
{
    m_foodIdTextCtrl->SetValue(id);
}

void FoodItemEditView::setFoodName(const std::string &name)
{
    m_foodNameTextCtrl->SetValue(name);
}

void FoodItemEditView::setFoodFat(const std::string &fat)
{
    m_foodFatTextCtrl->SetValue(fat);
}

void FoodItemEditView::setFoodProtein(const std::string &protein)
{
    m_foodProteinTextCtrl->SetValue(protein);
}

void FoodItemEditView::setFoodCarb(const std::string &carb)
{
    m_foodCarbTextCtrl->SetValue(carb);
}

void FoodItemEditView::setFoodCalories(const std::string &calories)
{
    m_foodCaloriesTextCtrl->SetValue(calories);
}

void FoodItemEditView::setFoodQuantity(const std::string &quantity)
{
    m_foodQuantityTextCtrl->SetValue(quantity);
}

void FoodItemEditView::setFoodUnit(int unitId, const std::vector<Unit>& units)
{
    m_foodUnitComboBox->Clear();
    for (auto unit : units) {
        spdlog::debug("FoodItemEditView::setFoodUnit: {}", unit.name);
        m_foodUnitComboBox->Append(unit.name);
    }
    m_foodUnitComboBox->SetSelection(unitId - 1);
}

std::string FoodItemEditView::getFoodId()
{
    return m_foodIdTextCtrl->GetValue().ToStdString();
}

std::string FoodItemEditView::getFoodName()
{
    return m_foodNameTextCtrl->GetValue().ToStdString();
}

std::string FoodItemEditView::getFoodFat()
{
    return m_foodFatTextCtrl->GetValue().ToStdString();
}

std::string FoodItemEditView::getFoodProtein()
{
    return m_foodProteinTextCtrl->GetValue().ToStdString();
}

std::string FoodItemEditView::getFoodCarb()
{
    return m_foodCarbTextCtrl->GetValue().ToStdString();
}

std::string FoodItemEditView::getFoodCalories()
{
    return m_foodCaloriesTextCtrl->GetValue().ToStdString();
}

std::string FoodItemEditView::getFoodQuantity()
{
    return m_foodQuantityTextCtrl->GetValue().ToStdString();
}

int FoodItemEditView::getFoodUnitId()
{
    return m_foodUnitComboBox->GetSelection() + 1;
}


