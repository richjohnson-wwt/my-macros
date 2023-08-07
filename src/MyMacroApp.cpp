#include "MyMacroApp.h"

#include <spdlog/spdlog.h>

MyMacroApp::MyMacroApp(wxFrame *parent)
: m_dbFood("../db/my-macro.sqlite3"),
    m_dbRecipe("../db/my-macro.sqlite3", &m_dbFood),
    m_dbDaily("../db/my-macro.sqlite3"),
    m_foodModel(&m_dbFood, &m_foodListModel, &m_foodCommonModel), 
    m_foodEditModel(&m_dbFood, &m_foodListModel, &m_foodCommonModel), 
    m_foodListModel(&m_dbFood),
    m_foodPresenter(&m_foodItemView, &m_foodModel, &m_foodListModel), 
    m_foodEditPresenter(&m_foodItemEditView, &m_foodEditModel, &m_foodListModel), 
    m_foodListPresenter(&m_foodListView, &m_foodListModel, &m_foodModel), 
    m_foodListView(&m_foodListPresenter),
    m_foodItemView(&m_foodPresenter, &m_foodItemEditView),
    m_topFoodView(&m_foodItemView, &m_fatSecretView), 
    m_foodItemEditView(&m_foodEditPresenter),
    m_recipeModel(&m_dbRecipe, &m_recipeListModel, &m_recipeCommonModel),
    m_recipeEditModel(&m_dbRecipe, &m_recipeListModel, &m_foodListModel, &m_recipeCommonModel),
    m_recipeListModel(&m_dbRecipe),
    m_recipePresenter(&m_recipeItemView, &m_recipeModel, &m_recipeListModel),
    m_recipeListPresenter(&m_recipeListView, &m_recipeListModel, &m_recipeModel),
    m_topRecipeView(&m_recipeItemView),
    m_recipeListView(&m_recipeListPresenter),
    m_recipeItemView(&m_recipePresenter, &m_recipeEditView),
    m_recipeEditView(&m_recipeEditPresenter),
    m_recipeEditPresenter(&m_recipeEditView, &m_recipeEditModel, &m_recipeListModel, &m_recipePresenter),
    m_dailyModel(&m_dbDaily, &m_foodListModel, &m_recipeListModel, &m_recipeModel),
    m_dailyPresenter(&m_dailyView, &m_dailyModel), 
    m_dailyView(&m_dailyPresenter),
    m_fatSecretModel(&m_dbFood),
    m_fatSecretWrapper(&m_fatSecretModel),
    m_fatSecretView(&m_fatSecretPresenter),
    m_fatSecretPresenter(&m_fatSecretView, &m_fatSecretWrapper),
    m_explorerNotebook(parent, &m_foodListView, &m_recipeListView),
    m_mainNotebook(parent, &m_dailyView, &m_topFoodView, &m_topRecipeView),
    m_wxFrame(parent)
{
}

MyMacroApp::~MyMacroApp() {
}

void MyMacroApp::create() {
    
    spdlog::set_level(spdlog::level::info);

    spdlog::debug("MyMacroApp::run");
    m_logWindow = new wxTextCtrl(m_wxFrame, wxID_ANY, wxEmptyString,
                                 wxDefaultPosition, wxDefaultSize,
                                 wxTE_READONLY | wxTE_MULTILINE | wxSUNKEN_BORDER);
    m_logOld = wxLog::SetActiveTarget(new wxLogTextCtrl(m_logWindow));

    // notify wxAUI which frame to use
    m_mgr.SetManagedWindow(m_wxFrame);

    // add the panes to the manager
    m_mgr.AddPane(m_explorerNotebook.createExplorerBookCtrl(), wxLEFT, wxT("Foods/Recipes"));
    m_mgr.AddPane(m_logWindow, wxBOTTOM, wxT("Log Console"));
    m_mgr.AddPane(m_mainNotebook.createMainBookCtrl(), wxCENTER);

    // tell the manager to "commit" all the changes just made
    m_mgr.Update();
    wxLogMessage("Macro App Running...");

}

void MyMacroApp::postInit()
{
    spdlog::debug("MyMacroApp::postInit");
    m_foodPresenter.postInit();
    m_foodListPresenter.postInit();
    m_recipePresenter.postInit();
    m_recipeListPresenter.postInit();
    m_dailyPresenter.postInit();


}
