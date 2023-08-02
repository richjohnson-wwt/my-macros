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

void RecipeListView::setRecipes(const std::vector<Recipe> &recipes) {
    spdlog::info("RecipeListView::setRecipes");
    m_recipesListView->DeleteAllItems();
    int row = 0;
    for (auto &recipe : recipes) {
        m_recipesListView->InsertItem(row, std::to_string(recipe.id));
        m_recipesListView->SetItem(row, 1, recipe.name);
        row++;
    }
}

void RecipeListView::setSelected(int idx) {
    m_recipesListView->Focus(idx);
}

void RecipeListView::onRecipeSelChange(wxListEvent &event) {
    wxListItem item = event.GetItem();
    int id = wxAtoi(item.GetText());
    spdlog::info("RecipeListView::onRecipeSelChange ({})", id);
    m_recipeListCallback->onRecipeSelected(id);
}