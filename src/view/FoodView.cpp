#include "FoodView.h"

#include "../presenter/FoodPresenter.h"

#include <spdlog/spdlog.h>

FoodView::FoodView(IFoodCallback *callback, FoodListView *foodsListView)
: m_foodCallback(callback), m_foodsListView(foodsListView) {
}

FoodView::~FoodView() {
}

wxPanel *FoodView::createFoodPanel(wxNotebook *parent)
{
    spdlog::info("FoodView::createFoodPanel");

    m_topPanel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxBoxSizer *sizermain = new wxBoxSizer(wxVERTICAL);
    m_splitter = new wxSplitterWindow(m_topPanel, wxID_ANY);
    m_splitter->SetSashGravity(0.5);
    m_splitter->SetMinimumPaneSize(200); // Smalest size the
    sizermain->Add(m_splitter, 1,wxEXPAND,0);

    wxPanel *pnl1 = new wxPanel(m_splitter, wxID_ANY);

    m_foodsListView->createFoodListPanel2(pnl1);

    wxPanel *pnl2 = new wxPanel(m_splitter, wxID_ANY);

    wxBoxSizer *txt2sizer = new wxBoxSizer(wxHORIZONTAL);
    wxPanel *itemPanel = createRightFoodItemPanel(pnl2);
    txt2sizer->Add(itemPanel, 0, wxEXPAND, 0);
    pnl2->SetSizer(txt2sizer);

    m_splitter->SplitVertically(pnl1, pnl2);

    m_topPanel->SetSizer(sizermain);
    sizermain->SetSizeHints(m_topPanel);

    return m_topPanel;
}

wxSizer *FoodView::CreateTextWithLabelSizer(wxPanel *panel, const wxString& label, wxTextCtrl *text)
{
    wxSizer *sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(new wxStaticText(panel, wxID_ANY, label), 0,
                  wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    sizerRow->Add(text, 0, wxALIGN_CENTRE_VERTICAL);

    return sizerRow;
}

wxPanel *FoodView::createRightFoodItemPanel(wxWindow *parent)
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
    m_foodUnitComboBox->Bind(wxEVT_COMBOBOX, &FoodView::onFoodUnitComboBox, this);
    comboSizerRow->Add(new wxStaticText(panel, wxID_ANY, "Food Unit: "), 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    comboSizerRow->Add(m_foodUnitComboBox, 0, wxALIGN_CENTRE_VERTICAL);
    topsizer->Add(comboSizerRow, 0, wxALL, 10);

    m_foodDeleteButton = new wxButton(panel, -1, _T("Delete Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_foodDeleteButton->Bind(wxEVT_BUTTON, &FoodView::onDeleteFood, this);

    m_foodSaveButton = new wxButton(panel, -1, _T("Save Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_foodSaveButton->Bind(wxEVT_BUTTON, &FoodView::onSaveFood, this);

    m_foodNewButton = new wxButton(panel, -1, _T("New Food"), wxDefaultPosition, wxDefaultSize, 0);
    m_foodNewButton->Bind(wxEVT_BUTTON, &FoodView::onNewFood, this);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(m_foodDeleteButton, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    buttonSizer->Add(m_foodSaveButton, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    buttonSizer->Add(m_foodNewButton, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);

    topsizer->Add(buttonSizer, 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, 5);

    panel->SetSizer(topsizer);
    return panel;
}

void FoodView::OnPositionChanging(wxSplitterEvent& event)
{
    wxLogStatus(m_topPanel, "Position is changing, now = %d (or %d)",
                event.GetSashPosition(), m_splitter->GetSashPosition());
}
    
void FoodView::onDeleteFood(wxCommandEvent& event) {

}

void FoodView::onSaveFood(wxCommandEvent& event) {

}

void FoodView::onNewFood(wxCommandEvent& event) {

}

void FoodView::onFoodUnitComboBox(wxCommandEvent& event) {

}
