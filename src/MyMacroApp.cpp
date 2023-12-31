#include "MyMacroApp.h"

#include <spdlog/spdlog.h>

MyMacroApp::MyMacroApp(wxFrame *parent)
: m_dbFood("/Users/johnsori/Documents/code/cpp/MyMacroMvvm/db/my-macro.sqlite3"),
    m_dbRecipe("/Users/johnsori/Documents/code/cpp/MyMacroMvvm/db/my-macro.sqlite3", &m_dbFood),
    m_dbDaily("/Users/johnsori/Documents/code/cpp/MyMacroMvvm/db/my-macro.sqlite3"),
    m_dbGoal("/Users/johnsori/Documents/code/cpp/MyMacroMvvm/db/my-macro.sqlite3"),
    m_foodModel(&m_dbFood, &m_foodListModel, &m_foodCommonModel), 
    m_foodEditModel(&m_dbFood, &m_foodListModel, &m_foodCommonModel), 
    m_foodListModel(&m_dbFood),
    m_foodPresenter(&m_foodItemView, &m_foodModel, &m_foodListModel), 
    m_foodEditPresenter(&m_foodItemEditView, &m_foodEditModel, &m_foodListModel), 
    m_foodListPresenter(&m_foodListView, &m_foodListModel, &m_dbFood), 
    m_foodListView(&m_foodListPresenter),
    m_foodItemView(&m_foodPresenter, &m_foodItemEditView),
    m_topFoodView(&m_foodItemView, &m_fatSecretView), 
    m_foodItemEditView(&m_foodEditPresenter),
    m_recipeModel(&m_dbRecipe, &m_recipeListModel, &m_recipeCommonModel),
    m_recipeEditModel(&m_dbRecipe, &m_recipeListModel, &m_foodListModel, &m_recipeCommonModel),
    m_recipeListModel(&m_dbRecipe),
    m_recipePresenter(&m_recipeItemView, &m_recipeModel, &m_recipeListModel),
    m_recipeListPresenter(&m_recipeListView, &m_recipeListModel, &m_dbRecipe),
    m_topRecipeView(&m_recipeItemView),
    m_recipeListView(&m_recipeListPresenter),
    m_recipeItemView(&m_recipePresenter, &m_recipeEditView),
    m_recipeEditView(&m_recipeEditPresenter),
    m_recipeEditPresenter(&m_recipeEditView, &m_recipeEditModel, &m_recipeListModel, &m_recipePresenter),
    m_dailyModel(&m_dbDaily, &m_dbGoal, &m_dbFood, &m_foodListModel, &m_recipeListModel, &m_recipeModel),
    m_dailyPresenter(&m_dailyView, &m_dailyModel, &m_timeHelper), 
    m_dailyView(&m_dailyPresenter),
    m_fatSecretModel(&m_dbFood),
    m_fatSecretWrapper(&m_fatSecretModel),
    m_fatSecretView(&m_fatSecretPresenter),
    m_fatSecretPresenter(&m_fatSecretView, &m_fatSecretWrapper),
    m_explorerNotebook(parent, &m_foodListView, &m_recipeListView),
    m_mainNotebook(parent, &m_dailyView, &m_topFoodView, &m_topRecipeView, &m_goalView),
    m_outlookView(parent),
    m_outlookPresenter(&m_outlookView, &m_outlookModel, &m_timeHelper, &m_dbDaily),
    m_outlookModel(&m_dbDaily, &m_dbGoal),
    m_goalPresenter(&m_dbGoal, &m_goalView),
    m_wxFrame(parent)
{
}

MyMacroApp::~MyMacroApp() {
}

void MyMacroApp::create() {
    
    spdlog::set_level(spdlog::level::info);

    spdlog::debug("MyMacroApp::run");

    // notify wxAUI which frame to use
    m_mgr.SetManagedWindow(m_wxFrame);

    // add the panes to the manager
    auto explorerPanel = m_explorerNotebook.createExplorerBookCtrl();
    m_mgr.AddPane(explorerPanel, wxLEFT, wxT("Foods/Recipes"));
    auto outlookPanel = m_outlookView.createRecipePanel();
    m_mgr.AddPane(outlookPanel, wxBOTTOM, wxT("Progress"));
    m_mgr.AddPane(m_mainNotebook.createMainBookCtrl(), wxCENTER);

    // Hack 1
    m_mgr.GetPane(explorerPanel).MinSize(450, -1);
    m_mgr.GetPane(explorerPanel).Fixed();
    m_mgr.Update();

    // hack
    m_mgr.GetPane(outlookPanel).MinSize(-1, 200);
    m_mgr.GetPane(outlookPanel).Fixed();
    m_mgr.Update();

    //now make resizable again
    m_mgr.GetPane(outlookPanel).Resizable();
    m_mgr.Update();

    // tell the manager to "commit" all the changes just made
    m_mgr.Update();

}

void MyMacroApp::postInit()
{
    spdlog::debug("MyMacroApp::postInit");
    m_foodPresenter.postInit();
    m_foodListPresenter.postInit();
    m_recipePresenter.postInit();
    m_recipeListPresenter.postInit();
    m_dailyPresenter.postInit();
    m_outlookPresenter.postInit();
    m_goalPresenter.postInit();
}
