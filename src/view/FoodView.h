#ifndef FOOD_VIEW_H
#define FOOD_VIEW_H

#include "FoodListView.h"

#include "../model/MyMacroTypes.h"

#include <wx/wx.h>
#include "wx/splitter.h"
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "wx/event.h"

class IFoodCallback;

class IFoodView {
public:

};

class FoodView : public wxEvtHandler, public IFoodView {
private:
    FoodListView *m_foodsListView;

    wxSplitterWindow* m_splitter;
    wxWindow *m_left; 
    wxWindow *m_right;
    wxPanel *m_topPanel;

    // Left List View
    IFoodCallback *m_foodCallback;

    wxPanel *createRightFoodItemPanel(wxWindow *parent);

    // Right Item View
    wxTextCtrl *m_foodIdTextCtrl;
    wxTextCtrl *m_foodNameTextCtrl;
    wxTextCtrl *m_foodFatTextCtrl;
    wxTextCtrl *m_foodProteinTextCtrl;
    wxTextCtrl *m_foodCarbTextCtrl;
    wxTextCtrl *m_foodCaloriesTextCtrl;
    wxTextCtrl *m_foodQuantityTextCtrl;
    wxComboBox *m_foodUnitComboBox;

    wxButton *m_foodDeleteButton;
    wxButton *m_foodSaveButton;
    wxButton *m_foodNewButton;

    wxSizer *CreateTextWithLabelSizer(wxPanel *panel, 
        const wxString& label,
         wxTextCtrl *text);

protected:
    // Left List View
    void OnPositionChanging(wxSplitterEvent& event);

    // Right Item View
    void onDeleteFood(wxCommandEvent& event);
    void onSaveFood(wxCommandEvent& event);
    void onNewFood(wxCommandEvent& event);
    void onFoodUnitComboBox(wxCommandEvent& event);
    
    
public:
    FoodView(IFoodCallback *callback, FoodListView *foodsListView);
    ~FoodView();

    wxPanel *createFoodPanel(wxNotebook *parent);

};

#endif // FOOD_VIEW_H