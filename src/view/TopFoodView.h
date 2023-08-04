#ifndef FOOD_VIEW_H
#define FOOD_VIEW_H

// #include "FoodListView.h"
#include "FatSecretView.h"

#include "../model/MyMacroTypes.h"

#include <wx/wx.h>
#include "wx/splitter.h"
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "wx/event.h"

class IFoodCallback;

class ITopFoodView {
public:
    virtual void setFoodId(const std::string& id) = 0;
};

class TopFoodView : public wxEvtHandler, public ITopFoodView
{
private:
    FatSecretView *m_fatSecretView;

    wxNotebook *m_foodFatSecretBookCtrl;

    IFoodCallback *m_foodCallback;

    wxPanel *createRightFoodItemPanel(wxNotebook *parent);

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
    // void onFoodFatSecretBookPageChanged(wxNotebookEvent &event);

public:
    TopFoodView(IFoodCallback *callback, FatSecretView *fatSecretView);
    ~TopFoodView();

    wxPanel *createFoodPanel(wxNotebook *parent);

    void setFoodId(const std::string& id) override;

    // void setActive();
};

#endif // FOOD_VIEW_H