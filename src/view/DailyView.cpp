#include "DailyView.h"
#include "../presenter/DailyPresenter.h"
#include <spdlog/spdlog.h>

DailyView::DailyView(IDailyCallback *callback) : m_dailyCallback(callback)
{
}

wxPanel *DailyView::createDailyPanel(wxNotebook *parent)
{
    wxPanel *topPanel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxSizer *sizerTop = new wxBoxSizer(wxHORIZONTAL);

    // LEFT PANEL
    wxSizer *leftPanelSizer = new wxBoxSizer(wxVERTICAL);

    m_foodRecipeBookCtrl = new wxNotebook(topPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _("Notebook"));
    m_foodRecipeBookCtrl->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &DailyView::onFoodRecipeBookPageChanged, this);

    wxWindow *pageFood = createFoodPage(m_foodRecipeBookCtrl);
    wxWindow *pageRecipe = createRecipePage(m_foodRecipeBookCtrl);
    m_foodRecipeBookCtrl->AddPage(pageFood, "Foods", false, 0);
    m_foodRecipeBookCtrl->AddPage(pageRecipe, "Recipes", false, 0);

    leftPanelSizer->Add(m_foodRecipeBookCtrl, 1, wxEXPAND | wxALL, 5);

    // RIGHT PANEL
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

wxPanel *DailyView::createFoodPage(wxNotebook *parent) {
    spdlog::info("DailyView::createFoodPage");

    wxPanel *panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);

    m_foodsListView = new wxListView(panel);
    m_foodsListView->AppendColumn("ID");
    m_foodsListView->AppendColumn("Name");
    m_foodsListView->SetColumnWidth(0, 40);
    m_foodsListView->SetColumnWidth(1, 320);
    m_foodsListView->Bind(wxEVT_LIST_ITEM_SELECTED, &DailyView::onFoodSelChange, this);

    wxBoxSizer *listCtrlBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags ListViewFlags(1);
    ListViewFlags.Expand().DoubleBorder();
    listCtrlBoxSizer->Add(m_foodsListView, 0, wxEXPAND | wxALL, 10);

    topSizer->Add(listCtrlBoxSizer, ListViewFlags);

    panel->SetSizer(topSizer);

    return panel;
}

wxPanel *DailyView::createRecipePage(wxNotebook *parent) {
    wxPanel *panel = new wxPanel(parent);
    m_recipesListView = new wxListView(panel);
    m_recipesListView->AppendColumn("ID");
    m_recipesListView->AppendColumn("Name");
    m_recipesListView->SetColumnWidth(0, 40);
    m_recipesListView->SetColumnWidth(1, 320);
    m_recipesListView->Bind(wxEVT_LIST_ITEM_SELECTED, &DailyView::onRecipeSelChange, this);

    wxBoxSizer *sizerPanel = new wxBoxSizer(wxVERTICAL);
    sizerPanel->Add(m_recipesListView, wxSizerFlags(2).Expand().Border());
    panel->SetSizer(sizerPanel);
    return panel;
}

void DailyView::postInit() {
}

void DailyView::setFoods(const std::vector<Food> &foods)
{
    spdlog::info("DailyView::setFoods");
    m_foodsListView->DeleteAllItems();
    int row = 0;
    for (auto &food : foods) {
        m_foodsListView->InsertItem(row, std::to_string(food.id));
        m_foodsListView->SetItem(row, 1, food.name);
        row++;
    }
}

void DailyView::setRecipes(const std::vector<Recipe> &recipes)
{
    spdlog::info("DailyView::setRecipes");
    m_recipesListView->DeleteAllItems();
    int row = 0;
    for (auto &recipe : recipes) {
        m_recipesListView->InsertItem(row, std::to_string(recipe.id));
        m_recipesListView->SetItem(row, 1, recipe.name);
        row++;
    }
}

void DailyView::onRecipeSelChange(wxListEvent &event)
{
    wxListItem item = event.GetItem();
    int id = wxAtoi(item.GetText());
    m_dailyCallback->onRecipeSelected(id);
}

void DailyView::onFoodSelChange(wxListEvent &event)
{
    wxListItem item = event.GetItem();
    int id = wxAtoi(item.GetText());
    m_dailyCallback->onFoodSelected(id);
}

void DailyView::onFoodRecipeBookPageChanged(wxNotebookEvent &event)
{
    spdlog::info("DailyView::onFoodRecipeBookPageChanged");
    m_dailyCallback->onFoodRecipeBookPageChanged(event.GetSelection());
}

void DailyView::setFoodSelected(int idx)
{
    m_foodsListView->SetItemState(idx, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void DailyView::setRecipeSelected(int idx)
{
    m_recipesListView->SetItemState(idx, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}