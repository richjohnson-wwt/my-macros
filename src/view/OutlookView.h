#ifndef OUTLOOK_VIEW_H
#define OUTLOOK_VIEW_H

#include <wx/wx.h>

class IOutlookView {
public:
    virtual void setTotalCaloriesForWeek(int totalCalories) = 0;
    virtual void setTotalExerciseCaloriesForWeek(int totalCalories) = 0;

};

class OutlookView : public IOutlookView
{
private:
    wxFrame *m_wxFrame;
    wxTextCtrl *m_weekCalories;
    wxTextCtrl *m_weekExerciseCalories;

    wxSizer *CreateTextWithLabelSizer(wxPanel *panel,
                                      const wxString &label,
                                      wxTextCtrl *text);
public:
    OutlookView(wxFrame* parent);

     wxPanel *createRecipePanel();

    void setTotalCaloriesForWeek(int totalCalories) override;
    void setTotalExerciseCaloriesForWeek(int totalCalories) override;
};

#endif // OUTLOOK_VIEW_H