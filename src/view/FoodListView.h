#ifndef FOOD_LIST_VIEW_H
#define FOOD_LIST_VIEW_H

#include "../model/MyMacroTypes.h"

#include <wx/wx.h>

#include "wx/listctrl.h"
#include "wx/srchctrl.h"
#include "wx/event.h"

class IFoodListCallback;

class IFoodListView
{
public:
    virtual void setFoods(const std::vector<Food> &foods) = 0;
    virtual void setSelected(wxInt16 idx) = 0;
};

class FoodListView : public wxEvtHandler, public IFoodListView
{
private:
    wxSearchCtrl *m_foodSearchTextCtrl;
    wxListView *m_foodsListView;
    IFoodListCallback *m_foodListCallback;

protected:
    void onFoodSelChange(wxListEvent &event);
    void OnSearch(wxCommandEvent& event);
    void OnSearchCancel(wxCommandEvent& event);

public:
    FoodListView(IFoodListCallback *callback);

    void createFoodListPanel(wxPanel *parent);

    void setFoods(const std::vector<Food> &foods) override;
    void setSelected(wxInt16 idx) override;

};

#endif // FOOD_LIST_VIEW_H