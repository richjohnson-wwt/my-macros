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

    wxBoxSizer *searchBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    m_foodSearchTextCtrl = new wxSearchCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20));
    m_foodSearchTextCtrl->ShowCancelButton(1);
    m_foodSearchTextCtrl->Bind(wxEVT_SEARCHCTRL_SEARCH_BTN, &FoodListView::OnSearch, this);
    m_foodSearchTextCtrl->Bind(wxEVT_SEARCHCTRL_CANCEL_BTN, &FoodListView::OnSearchCancel, this);
    searchBoxSizer->Add(m_foodSearchTextCtrl, wxSizerFlags(2).DoubleBorder());
    topSizer->Add(searchBoxSizer, wxSizerFlags(0).Expand().DoubleBorder());

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

void FoodListView::OnSearch(wxCommandEvent& event)
{
    const wxString searchText = m_foodSearchTextCtrl->GetValue();
    spdlog::info("FoodListView::OnSearch: {}", std::string(searchText));
    m_foodListCallback->onSearch(searchText.ToStdString());
}

void FoodListView::OnSearchCancel(wxCommandEvent& event)
{
    spdlog::debug("FoodListView::OnSearchCancel");
    m_foodListCallback->onSearchCancel();
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