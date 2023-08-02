#include "FoodView.h"

#include "../presenter/FoodPresenter.h"

#include <spdlog/spdlog.h>

FoodView::FoodView(IFoodCallback *callback): m_foodCallback(callback) {
}

FoodView::~FoodView() {
}

wxPanel *FoodView::createFoodPanel(wxNotebook *parent)
{
    spdlog::info("FoodView::createFoodPanel");

    wxPanel *panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);

    m_foodsListView = new wxListView(panel);
    m_foodsListView->AppendColumn("ID");
    m_foodsListView->AppendColumn("Name");
    m_foodsListView->SetColumnWidth(0, 40);
    m_foodsListView->SetColumnWidth(1, 320);
    m_foodsListView->Bind(wxEVT_LIST_ITEM_SELECTED, &FoodView::onFoodSelChange, this);

    wxBoxSizer *listCtrlBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags ListViewFlags(1);
    ListViewFlags.Expand().DoubleBorder();
    listCtrlBoxSizer->Add(m_foodsListView, 0, wxEXPAND | wxALL, 10);

    topSizer->Add(listCtrlBoxSizer, ListViewFlags);

    panel->SetSizer(topSizer);

    return panel;
}

void FoodView::setFoods(const std::vector<Food> &foods)
{
    spdlog::info("FoodView::populateFoodsList");
    m_foodsListView->DeleteAllItems();
    int row = 0;
    for (auto &food : foods) {
        m_foodsListView->InsertItem(row, std::to_string(food.id));
        m_foodsListView->SetItem(row, 1, food.name);
        row++;
    }
}

void FoodView::setSelected(int idx)
{
    m_foodsListView->SetItemState(idx, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void FoodView::onFoodSelChange(wxListEvent &event)
{
    wxListItem item = event.GetItem();
    int id = wxAtoi(item.GetText());
    m_foodCallback->onFoodSelected(id);
}
