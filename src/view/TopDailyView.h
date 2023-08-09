#ifndef DAILY_VIEW_H
#define DAILY_VIEW_H

#include "../model/MyMacroTypes.h"

#include <wx/wx.h>
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include <wx/datectrl.h>
#include <wx/dateevt.h>

struct Goals {
    int fat;
    int protein;
    int carb;
    int calories;
};

struct CalculatedMacros
{
    double fatGrams;
    double proteinGrams;
    double carbGrams;
    int calories;
};

class IDailyCallback;

class IDailyView {
public:
    virtual void setDailyActivityBonus(const std::string& bonus) = 0;
    virtual void setDailyWeight(const std::string& weight) = 0;
    virtual void setDailyFoodList(const std::vector<XrefDailyFood> &xrefDailyFoods) = 0;

    virtual void setTotalsList(const std::vector<XrefDailyFood> &totals, int percentFat, int percentProtein, int percentCarb) = 0;

    virtual int getActivityBonus() = 0;
    virtual double getWeight() = 0;
    virtual double getDailyMultiplier() = 0;
    virtual void warnFutureDate() = 0;
};

class DailyView : public wxEvtHandler, public IDailyView {
private:
    wxNotebook *m_foodRecipeBookCtrl;
    IDailyCallback *m_dailyCallback;

    wxDatePickerCtrl* m_datePicker;

    wxTextCtrl *m_dailyActivityBonusTextCtrl;
    wxButton *m_addActivityBonusButton;

    wxTextCtrl *m_dailyWeightTextCtrl;
    wxButton *m_addWeightButton;
    
    wxListView *m_dailyFoodListView;
    wxTextCtrl *m_foodMultiplierTextCtrl;
    wxButton *m_addDailyFoodButton;
    wxButton *m_addDailyRecipeButton;
    wxButton *m_deleteDailyFoodButton;

    wxListView *m_totalsListView;

    wxStaticText * m_fatPercent;
    wxStaticText * m_proteinPercent;
    wxStaticText * m_carbPercent;

protected:
    void onDateChanged(wxDateEvent& event);
    void onAddDailyFood(wxCommandEvent& event);
    void onAddDailyRecipe(wxCommandEvent& event);
    void onDeleteDailyFood(wxCommandEvent& event);
    void onAddActivityBonus(wxCommandEvent& event);
    void onAddWeight(wxCommandEvent& event);
    void onSelectDailyFood(wxListEvent& event);

public:
    DailyView(IDailyCallback *callback);

    wxPanel *createDailyPanel(wxNotebook *parent);

    void setDailyActivityBonus(const std::string& bonus) override;
    void setDailyWeight(const std::string& weight) override;
    void setDailyFoodList(const std::vector<XrefDailyFood> &xrefDailyFoods) override;

    void setTotalsList(const std::vector<XrefDailyFood> &totals, int percentFat, int percentProtein, int percentCarb) override;

    int getActivityBonus() override;
    double getWeight() override;
    double getDailyMultiplier() override;
    void warnFutureDate() override;

};

#endif // DAILY_VIEW_H