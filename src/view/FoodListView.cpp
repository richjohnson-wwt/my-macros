#include "FoodListView.h"

#include "../presenter/FoodListPresenter.h"

#include <spdlog/spdlog.h>

FoodListView::FoodListView(IFoodListCallback *callback): m_foodListCallback(callback)
{
}

void FoodListView::createFoodListPanel(wxPanel *parent)
{
    spdlog::info("FoodListView::createFoodListPanel");
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


 void FoodListView::setFoods(const std::vector<Food> &foods)
{
    spdlog::info("FoodListView::setFoods with size {}", foods.size());
    m_foodsListView->DeleteAllItems();
    int row = 0;
    for (auto &food : foods) {
        m_foodsListView->InsertItem(row, std::to_string(food.id));
        m_foodsListView->SetItem(row, 1, food.name);
        row++;
    }
}

void FoodListView::setSelected(int idx)
{
    m_foodsListView->Focus(idx);
}

void FoodListView::onFoodSelChange(wxListEvent &event)
{
    wxListItem item = event.GetItem();
    int id = wxAtoi(item.GetText());
    spdlog::info("FoodListView::onFoodSelChange ({})", id);
    m_foodListCallback->onFoodSelected(id);
}