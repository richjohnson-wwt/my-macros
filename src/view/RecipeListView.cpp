#include "RecipeListView.h"

#include "../presenter/RecipeListPresenter.h"

#include <spdlog/spdlog.h>

RecipeListView::RecipeListView(IRecipeListCallback *callback): m_recipeListCallback(callback)
{
    
}

void RecipeListView::createRecipeListPanel(wxPanel *parent)
{
    spdlog::debug("RecipeListView::createRecipeListPanel");
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

void RecipeListView::setRecipes(const std::vector<Recipe> &recipes) {
    spdlog::debug("RecipeListView::setRecipes with size {}", recipes.size());
    m_recipesListView->DeleteAllItems();
    int row = 0;
    for (auto &recipe : recipes) {
        m_recipesListView->InsertItem(row, std::to_string(recipe.id));
        m_recipesListView->SetItem(row, 1, recipe.name);
        row++;
    }
}

void RecipeListView::setSelected(int idx) {
    spdlog::debug("RecipeListView::setSelected with id({})", idx);
    int actualIndex = getZeroBasedIndexOfItem(wxString(std::to_string(idx)));
    m_recipesListView->SetItemState(actualIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void RecipeListView::onRecipeSelChange(wxListEvent &event) {
    wxListItem item = event.GetItem();
    wxInt16 id = wxAtoi(item.GetText());
    spdlog::debug("RecipeListView::onRecipeSelChange ({})", id);
    m_recipeListCallback->onRecipeSelected(id);
}

int RecipeListView::getZeroBasedIndexOfItem(wxString id) {
    spdlog::debug("RecipeListView::getZeroBasedIndexOfItem");
    // iterate over the m_recipesListView
    for (int i = 0; i < m_recipesListView->GetItemCount(); ++i) {
        if (m_recipesListView->GetItemText(i, 0) == id) {
            return i;
        }    
    }
    return 0;
}