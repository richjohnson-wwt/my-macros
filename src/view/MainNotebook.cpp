#include "MainNotebook.h"

#include <spdlog/spdlog.h>

MainNotebook::MainNotebook(wxFrame *parent, 
    DailyView *dailyView, 
    TopFoodView *topFoodView, 
    TopRecipeView *topRecipeView):
        m_dailyView(dailyView), 
        m_topFoodView(topFoodView), 
        m_topRecipeView(topRecipeView){

    m_mainBookCtrl = new wxNotebook(parent, wxID_ANY);
    m_mainBookCtrl->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MainNotebook::onNotebookPageChanged, this);

    wxWindow *page1 = m_dailyView->createDailyPanel(m_mainBookCtrl);
    wxWindow *page2 = m_topFoodView->createFoodPanel(m_mainBookCtrl);
    wxWindow *page3 = m_topRecipeView->createRecipePanel(m_mainBookCtrl);
    // wxWindow *page4 = m_fatSecretPanel.CreateFatSecretPage(m_mainBookCtrl);
    // wxWindow *page5 = m_macroPanel.CreateMacrosPage(m_mainBookCtrl);
    m_mainBookCtrl->AddPage(page1, "Daily", false, 0);
    m_mainBookCtrl->AddPage(page2, "Food", false, 0);
    m_mainBookCtrl->AddPage(page3, "Build Recipe", false, 0);
    // m_mainBookCtrl->AddPage(page4, "Fat Secret", false, 0);
    // m_mainBookCtrl->AddPage(page5, "Macros", false, 0);
}

void MainNotebook::onNotebookPageChanged( wxNotebookEvent &event ) {
    spdlog::info("MainNotebook::onNotebookPageChanged");
}

void MainNotebook::postInit() {
    // m_dailyPanel.postInit();
}