#include "TopDailyView.h"
#include "../presenter/DailyPresenter.h"
#include "../presenter/FoodListPresenter.h"
#include "../presenter/RecipeListPresenter.h"
#include <spdlog/spdlog.h>

DailyView::DailyView(IDailyCallback *callback, 
    IFoodListCallback * foodListCallback, 
    FoodListView *foodListView,
    RecipeListView *recipeListView,
    IRecipeListCallback * recipeListCallback) 
: m_dailyCallback(callback), 
m_foodListView(foodListView), 
m_foodListCallback(foodListCallback),
m_recipeListView(recipeListView),
m_recipeListCallback(recipeListCallback)
{
}

wxPanel *DailyView::createDailyPanel(wxNotebook *parent)
{
    wxPanel *topPanel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxSizer *sizerTop = new wxBoxSizer(wxHORIZONTAL);

    // LEFT PANEL - Food/Recipe Explorer Notebook
    wxSizer *leftPanelSizer = new wxBoxSizer(wxVERTICAL);

    m_foodRecipeBookCtrl = new wxNotebook(topPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _("Notebook"));
    m_foodRecipeBookCtrl->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &DailyView::onFoodRecipeBookPageChanged, this);
    wxPanel *page1 = new wxPanel(m_foodRecipeBookCtrl, wxID_ANY);
    wxPanel *page2 = new wxPanel(m_foodRecipeBookCtrl, wxID_ANY);

    m_foodListView->createFoodListPanel(page1);
    m_recipeListView->createRecipeListPanel(page2);

    m_foodRecipeBookCtrl->AddPage(page1, "Foods", true, wxID_ANY);
    m_foodRecipeBookCtrl->AddPage(page2, "Recipes", true, wxID_ANY);

    leftPanelSizer->Add(m_foodRecipeBookCtrl, 1, wxEXPAND | wxALL, 5);

    // RIGHT PANEL - Daily Food Tracker
    wxSizer *rightPanelSizer = new wxBoxSizer(wxVERTICAL);

    rightPanelSizer->Add(new wxStaticText(topPanel, wxID_ANY, "Right Panel1"), 0, wxALL, 5);
    rightPanelSizer->AddSpacer(10);
    rightPanelSizer->Add(new wxStaticText(topPanel, wxID_ANY, "Right Panel2"), 0, wxALL, 5);

    // END RIGHT PANEL

    sizerTop->Add(leftPanelSizer, 1, wxEXPAND | wxALL, 5);
    sizerTop->Add(rightPanelSizer, 1, wxEXPAND | wxALL, 5);

    topPanel->SetSizer(sizerTop);
    return topPanel;
}

void DailyView::postInit() {
}

void DailyView::onFoodRecipeBookPageChanged(wxNotebookEvent &event)
{
    spdlog::info("DailyView::onFoodRecipeBookPageChanged");
    if (event.GetSelection() == 0) {
        m_foodListCallback->onFoodBookPageChanged();
    } else {
        // m_dailyCallback->onRecipeBookPageChanged();
        m_recipeListCallback->onRecipeBookPageChanged();
    }
}
