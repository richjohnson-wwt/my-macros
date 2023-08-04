#include "TopFoodView.h"



#include <spdlog/spdlog.h>

TopFoodView::TopFoodView(FoodItemView *foodItemView, FatSecretView *fatSecretView)
    : m_foodItemView(foodItemView), m_fatSecretView(fatSecretView)
{
}

wxPanel *TopFoodView::createFoodPanel(wxNotebook *parent)
{
    spdlog::debug("TopFoodView::createFoodPanel");

    wxPanel *topPanel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxBoxSizer *notebookSizer = new wxBoxSizer(wxVERTICAL);
    m_foodFatSecretBookCtrl = new wxNotebook(topPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _("Notebook"));

    wxWindow *page1 = m_foodItemView->createFoodItemPanel(m_foodFatSecretBookCtrl);
    wxWindow *page2 = m_fatSecretView->createPanel(m_foodFatSecretBookCtrl);
    
    m_foodFatSecretBookCtrl->AddPage(page1, "Food Item", false, 0);
    m_foodFatSecretBookCtrl->AddPage(page2, "Fat Secret", false, 0);

    notebookSizer->Add(m_foodFatSecretBookCtrl, 0, wxEXPAND, 0);
    topPanel->SetSizer(notebookSizer);

    return topPanel;
}
