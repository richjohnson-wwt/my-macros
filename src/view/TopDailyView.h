#ifndef DAILY_VIEW_H
#define DAILY_VIEW_H

#include "../model/MyMacroTypes.h"

#include <wx/wx.h>
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include <wx/datectrl.h>
#include <wx/dateevt.h>

class IDailyCallback;

class IDailyView {
public:
    virtual void setDailyActivityBonus(const std::string& bonus) = 0;
    virtual void setDailyFoodList(const std::vector<XrefDailyFood> &xrefDailyFoods) = 0;

    virtual void setTotalsList(const std::vector<XrefDailyFood> &totals) = 0;

    virtual int getActivityBonus() = 0;
};

class DailyView : public wxEvtHandler, public IDailyView {
private:
    wxNotebook *m_foodRecipeBookCtrl;
    IDailyCallback *m_dailyCallback;

    wxDatePickerCtrl* m_datePicker;
    wxTextCtrl *m_dailyActivityBonusTextCtrl;
    wxButton *m_addActivityBonusButton;
    wxListView *m_dailyFoodListView;
    wxTextCtrl *m_foodMultiplierTextCtrl;
    wxButton *m_addDailyFoodButton;
    wxButton *m_deleteDailyFoodButton;

    wxListView *m_totalsListView;

protected:
    void onDateChanged(wxDateEvent& event);
    void onAddDailyFood(wxCommandEvent& event);
    void onDeleteDailyFood(wxCommandEvent& event);
    void onAddActivityBonus(wxCommandEvent& event);

public:
    DailyView(IDailyCallback *callback);

    wxPanel *createDailyPanel(wxNotebook *parent);

    void setDailyActivityBonus(const std::string& bonus) override;
    void setDailyFoodList(const std::vector<XrefDailyFood> &xrefDailyFoods) override;

    void setTotalsList(const std::vector<XrefDailyFood> &totals) override;

    int getActivityBonus() override;

};

#endif // DAILY_VIEW_H