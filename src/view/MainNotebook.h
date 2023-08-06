#ifndef MAIN_NOTEBOOK_H
#define MAIN_NOTEBOOK_H

#include "TopDailyView.h"
#include "TopFoodView.h"
#include "TopRecipeView.h"

#include <wx/wx.h>
#include "wx/listctrl.h"
#include "wx/notebook.h"

class MyFrame;

class MainNotebook {
public:
    MainNotebook(wxFrame* parent, DailyView *topDailyView, TopFoodView *topFoodView, TopRecipeView *topRecipeView);

    wxNotebook *createMainBookCtrl();

private:
    wxFrame *m_wxFrame;
    wxNotebook *m_mainBookCtrl;
    DailyView *m_dailyView;
    TopFoodView *m_topFoodView;
    TopRecipeView *m_topRecipeView;
};



#endif // MAIN_NOTEBOOK_H