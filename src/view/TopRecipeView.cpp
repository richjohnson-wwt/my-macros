#include "TopRecipeView.h"

#include "../presenter/RecipePresenter.h"

#include <spdlog/spdlog.h>

TopRecipeView::TopRecipeView(IRecipeCallback *callback, RecipeListView *recipesListView)
: m_recipeCallback(callback), m_recipeListView(recipesListView) {

}

wxPanel *TopRecipeView::createRecipePanel(wxNotebook *parent) {
    spdlog::info("TopRecipeView::createRecipePanel");
    wxPanel *topPanel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxBoxSizer *sizermain = new wxBoxSizer(wxVERTICAL);
    m_splitter = new wxSplitterWindow(topPanel, wxID_ANY);
    m_splitter->SetSashGravity(0.5);
    m_splitter->SetMinimumPaneSize(200); // Smalest size the
    sizermain->Add(m_splitter, 1, wxEXPAND, 0);

    wxPanel *pnl1 = new wxPanel(m_splitter, wxID_ANY);

    m_recipeListView->createRecipeListPanel(pnl1);

    wxPanel *pnl2 = new wxPanel(m_splitter, wxID_ANY);

    wxBoxSizer *txt2sizer = new wxBoxSizer(wxHORIZONTAL);
    wxPanel *itemPanel = createRightFoodItemPanel(pnl2);
    txt2sizer->Add(itemPanel, 0, wxEXPAND, 0);
    pnl2->SetSizer(txt2sizer);

    m_splitter->SplitVertically(pnl1, pnl2);

    topPanel->SetSizer(sizermain);
    sizermain->SetSizeHints(topPanel);

    return topPanel;
}

wxSizer *TopRecipeView::CreateTextWithLabelSizer(wxPanel *panel, const wxString &label, wxTextCtrl *text) {
    wxSizer *sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(new wxStaticText(panel, wxID_ANY, label), 0,
                  wxALIGN_CENTRE_VERTICAL | wxRIGHT, 5);
    sizerRow->Add(text, 0, wxALIGN_CENTRE_VERTICAL);
    return sizerRow;
}

wxPanel *TopRecipeView::createRightFoodItemPanel(wxWindow *parent) {
    wxPanel *panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));
    // wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
    // Compare this snippet from src/view/RecipeListView.h:

    return panel;
}

void TopRecipeView::OnPositionChanging(wxSplitterEvent &event)
{
    // wxLogStatus(m_topPanel, "Position is changing, now = %d (or %d)",
    //             event.GetSashPosition(), m_splitter->GetSashPosition());
}

void TopRecipeView::onDeleteFood(wxCommandEvent &event)
{
}

void TopRecipeView::onSaveFood(wxCommandEvent &event)
{
}

void TopRecipeView::onNewFood(wxCommandEvent &event)
{
}


