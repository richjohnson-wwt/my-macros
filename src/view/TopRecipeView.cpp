#include "TopRecipeView.h"

#include <spdlog/spdlog.h>

TopRecipeView::TopRecipeView(RecipeItemView *recipeItemView)
    : m_recipeItemView(recipeItemView)
{
}

wxPanel *TopRecipeView::createRecipePanel(wxNotebook *parent)
{
    spdlog::debug("TopFoodView::createFoodPanel");

    wxPanel *topPanel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxBoxSizer *notebookSizer = new wxBoxSizer(wxVERTICAL);
    m_recipeBookCtrl = new wxNotebook(topPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _("Notebook"));
    m_recipeBookCtrl->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &TopRecipeView::onNotebookPageChanged, this);

    wxWindow *page1 = m_recipeItemView->createRecipeItemPanel(m_recipeBookCtrl);
    
    m_recipeBookCtrl->AddPage(page1, "Food Item", false, 0);

    notebookSizer->Add(m_recipeBookCtrl, 0, wxEXPAND, 0);
    topPanel->SetSizer(notebookSizer);

    return topPanel;
}

void TopRecipeView::onNotebookPageChanged(wxCommandEvent &event)
{
    spdlog::debug("TopFoodView::onNotebookPageChanged");
    m_recipeItemView->onNotebookPageChanged();
}