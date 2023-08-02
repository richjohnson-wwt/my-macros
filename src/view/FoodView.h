#ifndef FOOD_VIEW_H
#define FOOD_VIEW_H


#include "../model/MyMacroTypes.h"

#include <wx/wx.h>
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "wx/event.h"

class IFoodCallback;

class IFoodView {
public:
    virtual void setFoods(const std::vector<Food> &foods) = 0;
    virtual void setSelected(int idx) = 0;
};

class FoodView : public wxEvtHandler, public IFoodView {
private:
    wxListView *m_foodsListView;
    IFoodCallback *m_foodCallback;

protected:
    void onFoodSelChange(wxListEvent &event);

public:
    FoodView(IFoodCallback *callback);
    ~FoodView();

    wxPanel *createFoodPanel(wxNotebook *parent);

    void setFoods(const std::vector<Food> &foods) override;
    void setSelected(int idx) override;

};

#endif // FOOD_VIEW_H