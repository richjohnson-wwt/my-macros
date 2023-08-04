#include "TopFoodView.h"

#include "../presenter/FoodPresenter.h"

#include <spdlog/spdlog.h>

TopFoodView::TopFoodView(IFoodCallback *callback, FatSecretView *fatSecretView)
    : m_foodCallback(callback), m_fatSecretView(fatSecretView)
{
}

TopFoodView::~TopFoodView()
{
}

wxPanel *TopFoodView::createFoodPanel(wxNotebook *parent)
{
    spdlog::debug("TopFoodView::createFoodPanel");

    wxPanel *topPanel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxBoxSizer *notebookSizer = new wxBoxSizer(wxVERTICAL);
    m_foodFatSecretBookCtrl = new wxNotebook(topPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _("Notebook"));

    wxWindow *page1 = createRightFoodItemPanel(m_foodFatSecretBookCtrl);
    wxWindow *page2 = m_fatSecretView->createPanel(m_foodFatSecretBookCtrl);
    
    m_foodFatSecretBookCtrl->AddPage(page1, "Food Item", false, 0);
    m_foodFatSecretBookCtrl->AddPage(page2, "Fat Secret", false, 0);

    notebookSizer->Add(m_foodFatSecretBookCtrl, 0, wxEXPAND, 0);
    topPanel->SetSizer(notebookSizer);

    return topPanel;
}

void TopFoodView::setFoodId(const std::string &id)
{
    m_foodIdTextCtrl->SetValue(id);
}

wxSizer *TopFoodView::CreateTextWithLabelSizer(wxPanel *panel, const wxString &label, wxTextCtrl *text)
{
    wxSizer *sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(new wxStaticText(panel, wxID_ANY, label), 0,
                  wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    sizerRow->Add(text, 0, wxALIGN_CENTRE_VERTICAL);

    return sizerRow;
}

wxPanel *TopFoodView::createRightFoodItemPanel(wxNotebook *parent)
{
    wxPanel *panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

    m_foodIdTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Food ID:", m_foodIdTextCtrl), 0, wxALL, 10);

    m_foodNameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(400, 20));
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
    m_foodUnitComboBox->Bind(wxEVT_COMBOBOX, &TopFoodView::onFoodUnitComboBox, this);
    comboSizerRow->Add(new wxStaticText(panel, wxID_ANY, "Food Unit: "), 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    comboSizerRow->Add(m_foodUnitComboBox, 0, wxALIGN_CENTRE_VERTICAL);
    topsizer->Add(comboSizerRow, 0, wxALL, 10);

    m_foodDeleteButton = new wxButton(panel, -1, _T("Delete Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_foodDeleteButton->Bind(wxEVT_BUTTON, &TopFoodView::onDeleteFood, this);

    m_foodSaveButton = new wxButton(panel, -1, _T("Save Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_foodSaveButton->Bind(wxEVT_BUTTON, &TopFoodView::onSaveFood, this);

    m_foodNewButton = new wxButton(panel, -1, _T("New Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_foodNewButton->Bind(wxEVT_BUTTON, &TopFoodView::onNewFood, this);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(m_foodDeleteButton, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    buttonSizer->Add(m_foodSaveButton, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    buttonSizer->Add(m_foodNewButton, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);

    topsizer->Add(buttonSizer, 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, 5);

    panel->SetSizer(topsizer);

    return panel;
}

void TopFoodView::onDeleteFood(wxCommandEvent &event)
{
}

void TopFoodView::onSaveFood(wxCommandEvent &event)
{
}

void TopFoodView::onNewFood(wxCommandEvent &event)
{
}

void TopFoodView::onFoodUnitComboBox(wxCommandEvent &event)
{
}
