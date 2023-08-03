#ifndef MY_MACRO_APP_H
#define MY_MACRO_APP_H

#include <wx/wx.h>
#include <wx/frame.h>
#include "wx/notebook.h"

// VIEW
#include "view/TopFoodView.h"
#include "view/FoodListView.h"
#include "view/TopDailyView.h"
#include "view/TopRecipeView.h"
#include "view/RecipeListView.h"
#include "view/FatSecretView.h"

// PRESENTER
#include "presenter/FoodPresenter.h"
#include "presenter/FoodListPresenter.h"
#include "presenter/DailyPresenter.h"
#include "presenter/RecipeListPresenter.h"
#include "presenter/RecipePresenter.h"
#include "presenter/FatSecretPresenter.h"

// MODEL
#include "model/FoodModel.h"
#include "model/DailyModel.h"
#include "model/RecipeModel.h"

class MyMacroApp
{
private:
    FoodPresenter m_foodPresenter;
    FoodModel m_foodModel;
    TopFoodView m_topFoodView;

    FoodListPresenter m_foodListPresenter;
    FoodListView m_foodListView;

    DailyPresenter m_dailyPresenter;
    DailyView m_dailyView;
    DailyModel m_dailyModel;

    RecipeModel m_recipeModel;
    RecipeListPresenter m_recipeListPresenter;
    RecipeListView m_recipeListView;
    TopRecipeView m_topRecipeView;
    RecipePresenter m_recipePresenter;

    FatSecretView m_fatSecretView;
    FatSecretPresenter m_fatSecretPresenter;

protected:
    void onNotebookPageChanged(wxNotebookEvent &event);

public:
    MyMacroApp();
    ~MyMacroApp();

    wxNotebook *createNotebook(wxFrame *parent);

    void postInit();
};

#endif // MY_MACRO_APP_H