#ifndef FOOD_ITEM_VIEW_H
#define FOOD_ITEM_VIEW_H

#include "FatSecretView.h"
#include "FoodItemEditView.h"

#include "../model/MyMacroTypes.h"

#include <wx/wx.h>
#include "wx/event.h"

class IFoodCallback;

class IFoodItemView {
public:
    virtual void setFoodId(const std::string& id) = 0;
    virtual void setFoodName(const std::string& name) = 0;
    virtual void setFoodFat(const std::string& fat) = 0;
    virtual void setFoodProtein(const std::string& protein) = 0;
    virtual void setFoodCarb(const std::string& carb) = 0;
    virtual void setFoodCalories(const std::string& calories) = 0;
    virtual void setFoodQuantity(const std::string& quantity) = 0;
    virtual void setFoodUnit(int unitId, const std::vector<Unit>& units) = 0;

    virtual void insertNewPage(bool isNew) = 0;
};

class FoodItemView : public wxEvtHandler, public IFoodItemView {
private:
    IFoodCallback *m_foodCallback;
    wxNotebook *m_parent;
    FoodItemEditView *m_foodItemEditView;

    wxTextCtrl *m_foodIdTextCtrl;
    wxTextCtrl *m_foodNameTextCtrl;
    wxTextCtrl *m_foodFatTextCtrl;
    wxTextCtrl *m_foodProteinTextCtrl;
    wxTextCtrl *m_foodCarbTextCtrl;
    wxTextCtrl *m_foodCaloriesTextCtrl;
    wxTextCtrl *m_foodQuantityTextCtrl;
    wxComboBox *m_foodUnitComboBox;

    wxButton *m_foodEditButton;
    wxButton *m_foodDeleteButton;
    wxButton *m_foodNewButton;

    wxSizer *CreateTextWithLabelSizer(wxPanel *panel,
                                      const wxString &label,
                                      wxTextCtrl *text);
    
protected:

    void onDeleteFood(wxCommandEvent &event);
    void onEditFood(wxCommandEvent &event);
    void onNewFood(wxCommandEvent &event);

public:
    FoodItemView(IFoodCallback *callback, FoodItemEditView *foodItemEditView);

    wxPanel *createFoodItemPanel(wxNotebook *parent);

    void setFoodId(const std::string& id) override;
    void setFoodName(const std::string& name) override;
    void setFoodFat(const std::string& fat) override;
    void setFoodProtein(const std::string& protein) override;
    void setFoodCarb(const std::string& carb) override;
    void setFoodCalories(const std::string& calories) override;
    void setFoodQuantity(const std::string& quantity) override;
    void setFoodUnit(int unitId, const std::vector<Unit>& units) override;

    void insertNewPage(bool isNew) override;

};

#endif // FOOD_ITEM_VIEW_H