#ifndef FOOD_ITEM_VIEW_H
#define FOOD_ITEM_VIEW_H

#include "FatSecretView.h"

#include "../model/MyMacroTypes.h"

#include <wx/wx.h>
#include "wx/event.h"

class IFoodCallback;

class IFoodItemView {
public:
    virtual void setFoodId(const std::string& id) = 0;
};

class FoodItemView : public wxEvtHandler, public IFoodItemView {
private:
    IFoodCallback *m_foodCallback;

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
                                      const wxString &label,
                                      wxTextCtrl *text);

protected:

    void onDeleteFood(wxCommandEvent &event);
    void onSaveFood(wxCommandEvent &event);
    void onNewFood(wxCommandEvent &event);
    void onFoodUnitComboBox(wxCommandEvent &event);

public:
    FoodItemView(IFoodCallback *callback);

    wxPanel *createFoodItemPanel(wxNotebook *parent);

    void setFoodId(const std::string& id);

};

#endif // FOOD_ITEM_VIEW_H