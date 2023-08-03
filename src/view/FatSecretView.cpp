#include "FatSecretView.h"

#include <spdlog/spdlog.h>

FatSecretView::FatSecretView(IFatSecretCallback *callback): m_fatSecretCallback(callback)
{
}

wxPanel *FatSecretView::createPanel(wxBookCtrlBase *parent)
{
    spdlog::info("FatSecretView::createPanel");
    wxPanel *panel = new wxPanel(parent);
    spdlog::info("FatSecretView::createPanel1a");
    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
    spdlog::info("FatSecretView::createPanel1b");


    // m_refreshTokenButton = new wxButton(panel, wxID_ANY, _T("Refresh Token"), wxDefaultPosition, wxDefaultSize, 0);
    wxButton *b = new wxButton(panel, wxID_ANY, _T("Refresh Token"), wxDefaultPosition, wxDefaultSize, 0);
    
    
    
    spdlog::info("FatSecretView::createPanel1c");

    b->Bind(wxEVT_BUTTON, &FatSecretView::onRefreshToken, this);
    spdlog::info("FatSecretView::createPanel1d");
    topsizer->Add(b, wxSizerFlags().Align(wxALIGN_RIGHT).Border(wxALL & ~wxBOTTOM, 5));

    spdlog::info("FatSecretView::createPanela");

    wxBoxSizer *searchSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSearchCtrl *st = new wxSearchCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHORIZONTAL);
    st->ShowCancelButton(1);
    st->Bind(wxEVT_SEARCHCTRL_SEARCH_BTN, &FatSecretView::onSearch, this);
    st->Bind(wxEVT_SEARCHCTRL_CANCEL_BTN, &FatSecretView::onSearchCancel, this);
    searchSizer->Add(st, 0, wxALL, 10);

    spdlog::info("FatSecretView::createPanelb");

    wxBoxSizer *listSizer = new wxBoxSizer(wxHORIZONTAL);
    wxListCtrl *lc = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT);
    wxListItem itemCol;
    itemCol.SetId(0);
    itemCol.SetColumn(0);
    lc->InsertColumn(0, "Food ID", itemCol, 100);
    lc->InsertColumn(1, "Food Name", itemCol, 200);
    lc->InsertColumn(2, "Food Description", itemCol, 500);
    listSizer->Add(lc, 1, wxEXPAND, 10);

    spdlog::info("FatSecretView::createPanelc");

    topsizer->Add(searchSizer, wxSizerFlags().Proportion(0).Expand().Border(wxALL, 10));
    topsizer->Add(listSizer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 10));

    spdlog::info("FatSecretView::createPaneld");

    panel->SetSizer(topsizer);

    return panel;
}

void FatSecretView::onRefreshToken(wxCommandEvent &event) {
    spdlog::info("onRefreshToken");
}

void FatSecretView::onAddFood(wxCommandEvent &event) {
    spdlog::info("onAddFood");
}

void FatSecretView::onSearch(wxCommandEvent& event) {
    spdlog::info("onSearch");
}

void FatSecretView::onSearchCancel(wxCommandEvent& event) {
    spdlog::info("onSearchCancel");
}