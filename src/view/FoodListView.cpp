#include "FoodListView.h"

#include "../presenter/FoodListPresenter.h"

#include <spdlog/spdlog.h>

FoodListView::FoodListView(IFoodListCallback *callback): m_foodListCallback(callback)
{
}

void FoodListView::createFoodListPanel(wxPanel *parent)
{
    spdlog::debug("FoodListView::createFoodListPanel");
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);

    m_foodsListView = new wxListView(parent);
    m_foodsListView->AppendColumn("ID");
    m_foodsListView->AppendColumn("Name");
    m_foodsListView->SetColumnWidth(0, 40);
    m_foodsListView->SetColumnWidth(1, 320);
    m_foodsListView->Bind(wxEVT_LIST_ITEM_SELECTED, &FoodListView::onFoodSelChange, this);

    wxBoxSizer *listCtrlBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags ListViewFlags(1);
    ListViewFlags.Expand().DoubleBorder();
    listCtrlBoxSizer->Add(m_foodsListView, 0, wxEXPAND | wxALL, 10);
    topSizer->Add(m_foodsListView, ListViewFlags);

    parent->SetSizer(topSizer);
}

void FoodListView::setActive() {
    spdlog::debug("FoodListView::setActive");
    m_foodListCallback->setActive();
}

 void FoodListView::setFoods(const std::vector<Food> &foods)
{
    spdlog::debug("FoodListView::setFoods with size {}", foods.size());
    m_foodsListView->DeleteAllItems();
    int row = 0;
    for (auto &food : foods) {
        m_foodsListView->InsertItem(row, std::to_string(food.id));
        m_foodsListView->SetItem(row, 1, food.name);
        row++;
    }
}

void FoodListView::setSelected(wxInt16 idx)
{
    spdlog::debug("FoodListView::setSelected with id({})", idx);
    int actualIndex = getZeroBasedIndexOfItem(wxString(std::to_string(idx)));
    m_foodsListView->SetItemState(actualIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void FoodListView::onFoodSelChange(wxListEvent &event)
{
    wxListItem item = event.GetItem();
    wxInt16 id = wxAtoi(item.GetText());
    spdlog::debug("FoodListView::onFoodSelChange GetText({})", id);
    m_foodListCallback->onFoodSelected(id);
}

int FoodListView::getZeroBasedIndexOfItem(wxString id) {
    spdlog::debug("FoodListView::getZeroBasedIndexOfItem");
    // iterate over the m_foodsListView
    for (int i = 0; i < m_foodsListView->GetItemCount(); ++i) {
        if (m_foodsListView->GetItemText(i, 0) == id) {
            return i;
        }    
    }
    return 0;
}