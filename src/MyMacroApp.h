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
#include "view/FoodItemEditView.h"
#include "view/FoodItemView.h"
#include "view/RecipeItemView.h"
#include "view/RecipeEditView.h"

// PRESENTER
#include "presenter/FoodPresenter.h"
#include "presenter/FoodEditPresenter.h"
#include "presenter/FoodListPresenter.h"
#include "presenter/DailyPresenter.h"
#include "presenter/RecipeListPresenter.h"
#include "presenter/RecipePresenter.h"
#include "presenter/RecipeEditPresenter.h"
#include "presenter/FatSecretPresenter.h"

// MODEL
#include "model/DailyModel.h"
#include "model/food/FoodCommonModel.h"
#include "model/food/FoodModel.h"
#include "model/food/FoodEditModel.h"
#include "model/food/FoodListModel.h"
#include "model/fatsecret/FatSecretWrapper.h"
#include "model/fatsecret/FatSecretModel.h"
#include "model/recipe/RecipeCommonModel.h"
#include "model/recipe/RecipeModel.h"
#include "model/recipe/RecipeEditModel.h"
#include "model/recipe/RecipeListModel.h"

// DB
#include "model/db/DbFood.h"
#include "model/db/DbRecipe.h"
#include "model/db/DbDaily.h"

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
    TopRecipeView m_topRecipeView;

    FoodCommonModel m_foodCommonModel;
    RecipeCommonModel m_recipeCommonModel;
    
    FoodEditPresenter m_foodEditPresenter;
    FoodItemEditView m_foodItemEditView;
    FoodEditModel m_foodEditModel;

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
    
    RecipeItemView m_recipeItemView;
    RecipePresenter m_recipePresenter;
    RecipeModel m_recipeModel;
    
    RecipeEditView m_recipeEditView;
    RecipeEditPresenter m_recipeEditPresenter;
    RecipeEditModel m_recipeEditModel;

    FatSecretView m_fatSecretView;
    FatSecretPresenter m_fatSecretPresenter;
    FatSecretWrapper m_fatSecretWrapper;
    FatSecretModel m_fatSecretModel;

    DbFood m_dbFood;
    DbRecipe m_dbRecipe;
    DbDaily m_dbDaily;

public:
    MyMacroApp(wxFrame *parent);
    ~MyMacroApp();

    void create();

    void postInit();
};

#endif // MY_MACRO_APP_H