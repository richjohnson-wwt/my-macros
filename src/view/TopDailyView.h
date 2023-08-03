#ifndef DAILY_VIEW_H
#define DAILY_VIEW_H

#include "FoodListView.h"
#include "RecipeListView.h"
#include "../model/MyMacroTypes.h"

#include <wx/wx.h>
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "wx/event.h"

class IDailyCallback;
class IFoodListCallback;
class IRecipeListCallback;

class IDailyView {
public:

};

class DailyView : public wxEvtHandler, public IDailyView {
private:
    FoodListView *m_foodListView;
    RecipeListView *m_recipeListView;

    wxNotebook *m_foodRecipeBookCtrl;

    IDailyCallback *m_dailyCallback;
    IFoodListCallback *m_foodListCallback;
    IRecipeListCallback *m_recipeListCallback;

protected:
    void onFoodRecipeBookPageChanged(wxNotebookEvent &event);

public:
    DailyView(IDailyCallback *callback, 
        IFoodListCallback * foodListCallback, 
        FoodListView *foodListView, 
        RecipeListView *recipeListView,
        IRecipeListCallback * recipeListCallback);

    wxPanel *createDailyPanel(wxNotebook *parent);

    void postInit();

};

#endif // DAILY_VIEW_H