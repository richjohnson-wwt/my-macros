#ifndef GOAL_VIEW_H
#define GOAL_VIEW_H

#include "../model/MyMacroTypes.h"
#include <wx/wx.h>
#include "wx/notebook.h"

class IGoalView {
public:
    virtual void setStartDate(const std::string &date) = 0;
    virtual void setTargetWeight(const std::string &targetWeight) = 0;
    virtual void setBmrCalories(const std::string &bmrCalories) = 0;
    virtual void setFatPercent(const std::string &fatPercent) = 0;
    virtual void setProteinPercent(const std::string &proteinPercent) = 0;
    virtual void setCarbPercent(const std::string &carbPercent) = 0;
};

class GoalView : public IGoalView {
private:
    wxTextCtrl *m_startDateTextCtrl;
    wxTextCtrl *m_targetWeightTextCtrl;
    wxTextCtrl *m_bmrCaloriesTextCtrl;
    wxTextCtrl *m_fatPercentTextCtrl;
    wxTextCtrl *m_proteinPercentTextCtrl;
    wxTextCtrl *m_carbPercentTextCtrl;

    wxSizer *createTextWithLabelSizer(wxPanel *panel, const wxString &label, wxTextCtrl *text);

public: 

    wxPanel *createGoalPanel(wxNotebook *parent);

    void setStartDate(const std::string &date) override;
    void setTargetWeight(const std::string &targetWeight) override;
    void setBmrCalories(const std::string &bmrCalories) override;
    void setFatPercent(const std::string &fatPercent) override;
    void setProteinPercent(const std::string &proteinPercent) override;
    void setCarbPercent(const std::string &carbPercent) override;
};

#endif // GOAL_VIEW_H