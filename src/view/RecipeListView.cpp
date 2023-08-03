#include "RecipeListView.h"

#include "../presenter/RecipeListPresenter.h"

#include <spdlog/spdlog.h>

RecipeListView::RecipeListView(IRecipeListCallback *callback): m_recipeListCallback(callback)
{
    
}

void RecipeListView::createRecipeListPanel(wxPanel *parent)
{
    spdlog::info("RecipeListView::createRecipeListPanel");
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    
    m_recipesListView = new wxListView(parent);
    m_recipesListView->AppendColumn("ID");
    m_recipesListView->AppendColumn("Name");
    m_recipesListView->SetColumnWidth(0, 40);
    m_recipesListView->SetColumnWidth(1, 320);
    m_recipesListView->Bind(wxEVT_LIST_ITEM_SELECTED, &RecipeListView::onRecipeSelChange, this);
    
    wxBoxSizer *listCtrlBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags ListViewFlags(1);
    ListViewFlags.Expand().DoubleBorder();
    listCtrlBoxSizer->Add(m_recipesListView, 0, wxEXPAND | wxALL, 10);
    topSizer->Add(m_recipesListView, ListViewFlags);
    
    parent->SetSizer(topSizer);
}

void RecipeListView::setActive() {
    spdlog::info("RecipeListView::setActive");
    m_recipeListCallback->setActive();
}

void RecipeListView::setRecipes(const std::vector<Recipe> &recipes) {
    spdlog::info("RecipeListView::setRecipes with size {}", recipes.size());
    m_recipesListView->DeleteAllItems();
    int row = 0;
    for (auto &recipe : recipes) {
        m_recipesListView->InsertItem(row, std::to_string(recipe.id));
        m_recipesListView->SetItem(row, 1, recipe.name);
        spdlog::info("RecipeListView::setRecipes with name {}", recipe.name);
        row++;
    }
}

void RecipeListView::setSelected(int idx) {
    m_recipesListView->SetItemState(idx, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void RecipeListView::onRecipeSelChange(wxListEvent &event) {
    wxListItem item = event.GetItem();
    int actualIndex = getZeroBasedIndexOfItem(item.GetText());
    spdlog::info("RecipeListView::onRecipeSelChange ({})", actualIndex);
    m_recipeListCallback->onRecipeSelected(actualIndex);
}

int RecipeListView::getZeroBasedIndexOfItem(wxString id) {
    spdlog::info("RecipeListView::getZeroBasedIndexOfItem");
    // iterate over the m_recipesListView
    for (int i = 0; i < m_recipesListView->GetItemCount(); ++i) {
        if (m_recipesListView->GetItemText(i, 0) == id) {
            return i;
        }    
    }
    return 0;
}