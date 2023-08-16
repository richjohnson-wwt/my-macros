#ifndef OUTLOOK_VIEW_H
#define OUTLOOK_VIEW_H

#include <wx/wx.h>

#include "IOutlookView.h"

class OutlookView : public IOutlookView
{
private:
    wxFrame *m_wxFrame;
    wxTextCtrl *m_consumedCalories;
    wxTextCtrl *m_activityCalories;
    wxTextCtrl *m_expectedWeightDelta;
    wxTextCtrl *m_bmrPlusExercise;
    wxTextCtrl *m_netInOut;

    wxTextCtrl *m_goalDate;
    wxTextCtrl *m_progressDate;
    wxTextCtrl *m_actualWeightLost;

    wxSizer *CreateTextWithLabelSizer(wxPanel *panel,
                                      const wxString &label,
                                      wxTextCtrl *text);

public:
    OutlookView(wxFrame *parent);

    wxPanel *createRecipePanel();

    void setTotalCaloriesForWeek(int totalCalories) override;
    void setTotalExerciseCaloriesForWeek(int totalCalories) override;

    void setProgressDate(const std::string &progressDate) override;
    void setTargetDate(const std::string &targetDate) override;
    void setPredictedPoundsLost(const std::string &poundsLost) override;
    void setActualPoundsLost(const std::string &poundsLost) override;
    void setBmrPlusExercise(const std::string &bmrPlusExercise) override;
    void setDeficitCalories(const std::string &deficitCalories) override;
};

#endif // OUTLOOK_VIEW_H