#include "MyMacroApp.h"

#include <spdlog/spdlog.h>

MyMacroApp::MyMacroApp() 
: m_foodPresenter(&m_foodView, &m_foodModel), m_foodView(&m_foodPresenter), 
    m_dailyPresenter(&m_dailyView, &m_dailyModel), m_dailyView(&m_dailyPresenter)
{
}

MyMacroApp::~MyMacroApp() {
}

wxNotebook *MyMacroApp::createNotebook(wxFrame *parent)
{
    spdlog::info("MyMacroApp::createFoodPanel");

    wxNotebook *notebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _("Notebook"));
    notebook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MyMacroApp::onNotebookPageChanged, this);

    wxPanel *dailyPanel = m_dailyView.createDailyPanel(notebook);
    wxPanel *foodPanel = m_foodView.createFoodPanel(notebook);

    notebook->AddPage(dailyPanel, _("Daily"));
    notebook->AddPage(foodPanel, _("Food"));

    return notebook;
}

void MyMacroApp::postInit()
{
    spdlog::info("MyMacroApp::postInit");
    m_dailyPresenter.setActive();
}

void MyMacroApp::onNotebookPageChanged(wxNotebookEvent &event)
{
    
    int page = event.GetSelection();
    if (page == 0) {
        spdlog::info("MyMacroApp::onNotebookPageChanged DAILY");
        m_dailyPresenter.setActive();
    } else {
        spdlog::info("MyMacroApp::onNotebookPageChanged FOOD PAGE");
        m_foodPresenter.setActive();
    }
}