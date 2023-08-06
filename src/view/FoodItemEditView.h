#ifndef FOOD_ITEM_EDIT_VIEW_H
#define FOOD_ITEM_EDIT_VIEW_H

#include "FatSecretView.h"

#include "../model/MyMacroTypes.h"

#include <wx/wx.h>
#include "wx/event.h"

class IFoodEditCallback;

class IFoodItemEditView {
public:
    virtual void setFoodId(const std::string& id) = 0;
    virtual void setFoodName(const std::string& name) = 0;
    virtual void setFoodFat(const std::string& fat) = 0;
    virtual void setFoodProtein(const std::string& protein) = 0;
    virtual void setFoodCarb(const std::string& carb) = 0;
    virtual void setFoodCalories(const std::string& calories) = 0;
    virtual void setFoodQuantity(const std::string& quantity) = 0;
    virtual void setFoodUnit(int unitId, const std::vector<Unit>& units) = 0;

    virtual std::string getFoodId() = 0;
    virtual std::string getFoodName() = 0;
    virtual std::string getFoodFat() = 0;
    virtual std::string getFoodProtein() = 0;
    virtual std::string getFoodCarb() = 0;
    virtual std::string getFoodCalories() = 0;
    virtual std::string getFoodQuantity() = 0;
    virtual int getFoodUnitId() = 0;
};

class FoodItemEditView : public wxEvtHandler, public IFoodItemEditView {
private:
    IFoodEditCallback *m_foodCallback;
    wxNotebook *m_parent;

    wxTextCtrl *m_foodIdTextCtrl;
    wxTextCtrl *m_foodNameTextCtrl;
    wxTextCtrl *m_foodFatTextCtrl;
    wxTextCtrl *m_foodProteinTextCtrl;
    wxTextCtrl *m_foodCarbTextCtrl;
    wxTextCtrl *m_foodCaloriesTextCtrl;
    wxTextCtrl *m_foodQuantityTextCtrl;
    wxComboBox *m_foodUnitComboBox;

    wxButton *m_foodSaveButton;
    wxButton *m_foodNewCancelButton;

    wxSizer *CreateTextWithLabelSizer(wxPanel *panel,
                                      const wxString &label,
                                      wxTextCtrl *text);
    void deleteThisPage();

protected:

    void onSaveFood(wxCommandEvent &event);
    void onNewFoodCancel(wxCommandEvent &event);
    void onFoodUnitComboBox(wxCommandEvent &event);

public:
    FoodItemEditView(IFoodEditCallback *callback);

    wxPanel *createFoodItemEditPanel(wxNotebook *parent);
    void initNewPage(bool isNew);

    void setFoodId(const std::string& id);
    void setFoodName(const std::string& name);
    void setFoodFat(const std::string& fat);
    void setFoodProtein(const std::string& protein);
    void setFoodCarb(const std::string& carb);
    void setFoodCalories(const std::string& calories);
    void setFoodQuantity(const std::string& quantity);
    void setFoodUnit(int unitId, const std::vector<Unit>& units);

    std::string getFoodId();
    std::string getFoodName();
    std::string getFoodFat();
    std::string getFoodProtein();
    std::string getFoodCarb();
    std::string getFoodCalories();
    std::string getFoodQuantity();
    int getFoodUnitId();

};

#endif // FOOD_ITEM_EDIT_VIEW_H