#include "MyMacroApp.h"

#include <spdlog/spdlog.h>

MyMacroApp::MyMacroApp() 
: m_foodPresenter(&m_topFoodView, &m_foodModel), 
    m_topFoodView(&m_foodPresenter, &m_foodListView), 
    m_foodListPresenter(&m_foodListView, &m_foodModel), 
    m_foodListView(&m_foodListPresenter),
    m_dailyPresenter(&m_dailyView, &m_dailyModel, &m_recipeModel), 
    m_dailyView(&m_dailyPresenter, &m_foodListPresenter, &m_foodListView, &m_recipeListView, &m_recipeListPresenter),
    m_recipePresenter(&m_topRecipeView, &m_recipeModel),
    m_topRecipeView(&m_recipePresenter, &m_recipeListView),
    m_recipeListPresenter(&m_recipeListView, &m_recipeModel),
    m_recipeListView(&m_recipeListPresenter)
{
}

MyMacroApp::~MyMacroApp() {
}

wxNotebook *MyMacroApp::createNotebook(wxFrame *parent)
{
    spdlog::info("MyMacroApp::createNotebook pages DailyView and FoodView");

    wxNotebook *notebook = new wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _("Notebook"));
    notebook->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MyMacroApp::onNotebookPageChanged, this);

    wxPanel *dailyPanel = m_dailyView.createDailyPanel(notebook);
    wxPanel *foodPanel = m_topFoodView.createFoodPanel(notebook);
    wxPanel *recipePanel = m_topRecipeView.createRecipePanel(notebook);

    notebook->AddPage(dailyPanel, _("Daily"));
    notebook->AddPage(foodPanel, _("Food"));
    notebook->AddPage(recipePanel, _("Recipe"));

    return notebook;
}

void MyMacroApp::postInit()
{
    spdlog::info("MyMacroApp::postInit");
    // m_foodListPresenter.setActive();
    m_dailyPresenter.setActive();
}

void MyMacroApp::onNotebookPageChanged(wxNotebookEvent &event)
{
    
    int page = event.GetSelection();
    if (page == 0) {
        spdlog::info("MyMacroApp::onNotebookPageChanged DAILY");
        m_dailyPresenter.setActive();
        m_foodListPresenter.setActive();
    } else if (page == 1) {
        spdlog::info("MyMacroApp::onNotebookPageChanged FOOD PAGE");
        m_foodPresenter.setActive();
        m_foodListPresenter.setActive();
    } else if (page == 2) {
        spdlog::info("MyMacroApp::onNotebookPageChanged RECIPE PAGE");
        m_recipePresenter.setActive();
        m_recipeListPresenter.setActive();
    } else {
        spdlog::error("MyMacroApp::onNotebookPageChanged ERROR");
    }
}