#include "MainNotebook.h"

#include <spdlog/spdlog.h>

MainNotebook::MainNotebook(wxFrame *parent, 
    DailyView *dailyView, 
    TopFoodView *topFoodView, 
    TopRecipeView *topRecipeView):
        m_dailyView(dailyView), 
        m_topFoodView(topFoodView), 
        m_topRecipeView(topRecipeView),
        m_wxFrame(parent) {

}

wxNotebook *MainNotebook::createMainBookCtrl()
{
    spdlog::debug("MainNotebook::MainNotebook");
    m_mainBookCtrl = new wxNotebook(m_wxFrame, wxID_ANY);
    // m_mainBookCtrl->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MainNotebook::onNotebookPageChanged, this);

    wxWindow *page1 = m_dailyView->createDailyPanel(m_mainBookCtrl);
    wxWindow *page2 = m_topFoodView->createFoodPanel(m_mainBookCtrl);
    wxWindow *page3 = m_topRecipeView->createRecipePanel(m_mainBookCtrl);
    m_mainBookCtrl->AddPage(page1, "Daily", false, 0);
    m_mainBookCtrl->AddPage(page2, "Food", false, 0);
    m_mainBookCtrl->AddPage(page3, "Recipe", false, 0);
    return m_mainBookCtrl;
}
