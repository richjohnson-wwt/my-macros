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
    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
    
    // Create RecipeID as wxTextCtrl
    m_recipeIdTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe ID:", m_recipeIdTextCtrl), 0, wxALL, 10);

    // Recipe Name wxTextCtrl
    m_recipeNameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Name:", m_recipeNameTextCtrl), 0, wxALL, 10);

    // Recipe Description wxTextCtrl
    m_recipeDescriptionTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Description:", m_recipeDescriptionTextCtrl), 0, wxALL, 10);

    // Recipe URL wxTextCtrl
    m_recipeUrlTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe URL:", m_recipeUrlTextCtrl), 0, wxALL, 10);

    // Recipe Servings wxTextCtrl
    m_recipeServingsTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Servings:", m_recipeServingsTextCtrl), 0, wxALL, 10);

    // Recipe Instructions wxTextCtrl
    m_recipeInstructionsTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    topsizer->Add(CreateTextWithLabelSizer(panel, "Recipe Instructions:", m_recipeInstructionsTextCtrl), 0, wxALL, 10);

    wxBoxSizer *ingredientButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
    m_addRecipeIngredientButton = new wxButton(panel, -1, _T("Add Food With Multiplier"), wxDefaultPosition, wxDefaultSize, 0);
    m_addRecipeIngredientButton->Bind(wxEVT_BUTTON, &TopRecipeView::onAddIngredient, this);
    
    m_recipeIngredientMultiplierTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    ingredientButtonsSizer->Add(m_addRecipeIngredientButton, 0, wxALL, 10);
    ingredientButtonsSizer->Add(m_recipeIngredientMultiplierTextCtrl, 0, wxALL, 10);
    topsizer->Add(ingredientButtonsSizer, 0, wxALL, 10);
    
    // Recipe Ingredients - List Ctrl
    m_recipeIngredientsListView = new wxListView(panel);
    m_recipeIngredientsListView->AppendColumn("ID");
    m_recipeIngredientsListView->AppendColumn("Name");
    m_recipeIngredientsListView->AppendColumn("Qty");
    m_recipeIngredientsListView->AppendColumn("Unit");
    m_recipeIngredientsListView->AppendColumn("Multiplier");
    m_recipeIngredientsListView->SetColumnWidth(0, 40);
    m_recipeIngredientsListView->SetColumnWidth(1, 320);
    m_recipeIngredientsListView->SetColumnWidth(2, 100);
    m_recipeIngredientsListView->SetColumnWidth(3, 100);
    m_recipeIngredientsListView->SetColumnWidth(4, 100);
    m_recipeIngredientsListView->Bind(wxEVT_LIST_ITEM_SELECTED, &TopRecipeView::onIngredientSelChange, this);
    topsizer->Add(m_recipeIngredientsListView, 1, wxEXPAND | wxALL, 10);

    m_deleteRecipeIngredientButton = new wxButton(panel, -1, _T("Delete Selected Ingredient"), wxDefaultPosition, wxDefaultSize, 0);
    m_deleteRecipeIngredientButton->Bind(wxEVT_BUTTON, &TopRecipeView::onDeleteIngredient, this);
    topsizer->Add(m_deleteRecipeIngredientButton, 0, wxALL, 10);

    wxBoxSizer *recipeButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
    m_recipeDeleteButton = new wxButton(panel, -1, _T("Delete"), wxDefaultPosition, wxDefaultSize, 0);
    m_recipeDeleteButton->Bind(wxEVT_BUTTON, &TopRecipeView::onDeleteRecipe, this);
    m_recipeSaveButton = new wxButton(panel, -1, _T("Save"), wxDefaultPosition, wxDefaultSize, 0);
    m_recipeSaveButton->Bind(wxEVT_BUTTON, &TopRecipeView::onSaveRecipe, this);
    m_recipeNewButton = new wxButton(panel, -1, _T("New"), wxDefaultPosition, wxDefaultSize, 0);
    m_recipeNewButton->Bind(wxEVT_BUTTON, &TopRecipeView::onNewRecipe, this);
    recipeButtonsSizer->Add(m_recipeDeleteButton, 0, wxALL, 10);
    recipeButtonsSizer->Add(m_recipeSaveButton, 0, wxALL, 10);
    recipeButtonsSizer->Add(m_recipeNewButton, 0, wxALL, 10);
    topsizer->Add(recipeButtonsSizer, 0, wxALL, 10);

    panel->SetSizer(topsizer);

    return panel;
}

void TopRecipeView::OnPositionChanging(wxSplitterEvent &event)
{
    // wxLogStatus(m_topPanel, "Position is changing, now = %d (or %d)",
    //             event.GetSashPosition(), m_splitter->GetSashPosition());
}

void TopRecipeView::onDeleteRecipe(wxCommandEvent &event)
{
}

void TopRecipeView::onSaveRecipe(wxCommandEvent &event)
{
}

void TopRecipeView::onNewRecipe(wxCommandEvent &event)
{
}

void TopRecipeView::onAddIngredient(wxCommandEvent &event) {

}

void TopRecipeView::onDeleteIngredient(wxCommandEvent &event) {
    
}

void TopRecipeView::onIngredientSelChange(wxListEvent &event) {
    
}

