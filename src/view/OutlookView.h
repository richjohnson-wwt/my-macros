#ifndef OUTLOOK_VIEW_H
#define OUTLOOK_VIEW_H

#include <wx/wx.h>

#include "IOutlookView.h"

class OutlookView : public IOutlookView
{
private:
    wxFrame *m_wxFrame;
    wxTextCtrl *m_weekCalories;
    wxTextCtrl *m_weekExerciseCalories;

    wxTextCtrl *m_goalDate;
    wxTextCtrl *m_progressDate;

    wxSizer *CreateTextWithLabelSizer(wxPanel *panel,
                                      const wxString &label,
                                      wxTextCtrl *text);
public:
    OutlookView(wxFrame* parent);

     wxPanel *createRecipePanel();

    void setTotalCaloriesForWeek(int totalCalories) override;
    void setTotalExerciseCaloriesForWeek(int totalCalories) override;

    void setProgressDate(const std::string &progressDate) override;
    void setTargetDate(const std::string &targetDate) override;
};

#endif // OUTLOOK_VIEW_H