#ifndef MY_MACRO_APP_H
#define MY_MACRO_APP_H

#include <wx/wx.h>
#include <wx/frame.h>
#include "wx/notebook.h"

// VIEW
#include "view/FoodView.h"
#include "view/FoodListView.h"
#include "view/DailyView.h"

// PRESENTER
#include "presenter/FoodPresenter.h"
#include "presenter/FoodListPresenter.h"
#include "presenter/DailyPresenter.h"

// MODEL
#include "model/FoodModel.h"
#include "model/DailyModel.h"

class MyMacroApp {
private:
    FoodPresenter m_foodPresenter;
    FoodModel m_foodModel;
    FoodView m_foodView;

    FoodListPresenter m_foodListPresenter;
    FoodListView m_foodListView;
    
    DailyPresenter m_dailyPresenter;
    DailyView m_dailyView;
    DailyModel m_dailyModel;

protected:
    void onNotebookPageChanged(wxNotebookEvent &event);
    
public:
    MyMacroApp();
    ~MyMacroApp();

    wxNotebook *createNotebook(wxFrame *parent);

    void postInit();


};

#endif // MY_MACRO_APP_H