#include "ExplorerNotebook.h"

#include <spdlog/spdlog.h>

ExplorerNotebook::ExplorerNotebook(wxFrame *parent, FoodListView *foodListView, RecipeListView *recipeListView):m_foodListView(foodListView), m_recipeListView(recipeListView)
{
    m_explorerBookCtrl = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxSize(300, 200)); 
    m_explorerBookCtrl->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &ExplorerNotebook::onNotebookPageChanged, this);

    wxWindow *pageFood = CreateExplorerFoodPage(m_explorerBookCtrl);
    wxWindow *pageRecipe = CreateExplorerRecipePage(m_explorerBookCtrl);
    m_explorerBookCtrl->AddPage(pageFood, "Foods", false, 0);
    m_explorerBookCtrl->AddPage(pageRecipe, "Recipes", false, 0);
}

void ExplorerNotebook::onNotebookPageChanged( wxNotebookEvent &event ) {
    spdlog::info("ExplorerNotebook::onNotebookPageChanged");
    if (event.GetSelection() == 0) {
        m_foodListView->setActive();
    } else {
        m_recipeListView->setActive();
    }
}

wxPanel *ExplorerNotebook::CreateExplorerFoodPage(wxBookCtrlBase *parent) {
    wxPanel *panel = new wxPanel(parent);
    m_foodListView->createFoodListPanel(panel);
    return panel;
}

wxPanel *ExplorerNotebook::CreateExplorerRecipePage(wxBookCtrlBase *parent) {
    wxPanel *panel = new wxPanel(parent);
    m_recipeListView->createRecipeListPanel(panel);
    return panel;
}