#ifndef DAILY_VIEW_H
#define DAILY_VIEW_H

#include "../model/MyMacroTypes.h"

#include <wx/wx.h>
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "wx/event.h"

class IDailyCallback;

class IDailyView {
public:
    virtual void setFoods(const std::vector<Food> &foods) = 0;
    virtual void setFoodSelected(int idx) = 0;
    virtual void setRecipes(const std::vector<Recipe> &foods) = 0;
    virtual void setRecipeSelected(int idx) = 0;
};

class DailyView : public wxEvtHandler, public IDailyView {
private:
    wxNotebook *m_foodRecipeBookCtrl;
    wxListView *m_foodsListView;
    wxListView *m_recipesListView;
    IDailyCallback *m_dailyCallback;

protected:
    void onFoodRecipeBookPageChanged(wxNotebookEvent &event);
    void onFoodSelChange(wxListEvent &event);
    void onRecipeSelChange(wxListEvent &event);

public:
    DailyView(IDailyCallback *callback);

    wxPanel *createDailyPanel(wxNotebook *parent);
    wxPanel *createFoodPage(wxNotebook *parent);
    wxPanel *createRecipePage(wxNotebook *parent);

    void postInit();

    void setFoods(const std::vector<Food> &foods) override;
    void setFoodSelected(int idx) override;
    void setRecipes(const std::vector<Recipe> &foods) override;
    void setRecipeSelected(int idx) override;
};

#endif // DAILY_VIEW_H