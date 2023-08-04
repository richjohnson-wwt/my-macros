#ifndef MY_MACRO_APP_H
#define MY_MACRO_APP_H

#include <wx/wx.h>
#include "wx/aui/aui.h"
#include <wx/frame.h>
#include "wx/notebook.h"

// VIEW
#include "view/ExplorerNotebook.h"
#include "view/MainNotebook.h"
#include "view/FoodListView.h"
#include "view/RecipeListView.h"
#include "view/TopFoodView.h"
#include "view/TopDailyView.h"
#include "view/TopRecipeView.h"
#include "view/FatSecretView.h"
#include "view/FoodItemView.h"

// PRESENTER
#include "presenter/FoodPresenter.h"
#include "presenter/FoodListPresenter.h"
#include "presenter/DailyPresenter.h"
#include "presenter/RecipeListPresenter.h"
#include "presenter/RecipePresenter.h"
#include "presenter/FatSecretPresenter.h"

// MODEL
#include "model/FoodModel.h"
#include "model/FoodListModel.h"
#include "model/DailyModel.h"
#include "model/RecipeModel.h"
#include "model/RecipeListModel.h"
#include "model/FatSecretWrapper.h"

// DB
#include "model/DbFood.h"
#include "model/DbRecipe.h"

class MyMacroApp
{
private:
    wxAuiManager m_mgr; 
    wxLog *m_logOld;
    wxTextCtrl *m_logWindow;
    wxFrame *m_wxFrame;
    ExplorerNotebook m_explorerNotebook;
    MainNotebook m_mainNotebook;

    TopFoodView m_topFoodView;
    
    FoodPresenter m_foodPresenter;
    FoodModel m_foodModel;
    FoodItemView m_foodItemView;

    FoodListPresenter m_foodListPresenter;
    FoodListView m_foodListView;
    FoodListModel m_foodListModel;

    DailyPresenter m_dailyPresenter;
    DailyView m_dailyView;
    DailyModel m_dailyModel;

    RecipeListModel m_recipeListModel;
    RecipeListPresenter m_recipeListPresenter;
    RecipeListView m_recipeListView;

    TopRecipeView m_topRecipeView;
    RecipePresenter m_recipePresenter;
    RecipeModel m_recipeModel;

    FatSecretView m_fatSecretView;
    FatSecretPresenter m_fatSecretPresenter;
    FatSecretWrapper m_fatSecretWrapper;

    DbFood m_dbFood;
    DbRecipe m_dbRecipe;

public:
    MyMacroApp(wxFrame *parent);
    ~MyMacroApp();

    void create();

    void postInit();
};

#endif // MY_MACRO_APP_H