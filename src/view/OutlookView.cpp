#include "OutlookView.h"
#include <wx/statbox.h>

OutlookView::OutlookView(wxFrame* parent)
    : m_wxFrame(parent)
{
}

wxSizer *OutlookView::CreateTextWithLabelSizer(wxPanel *panel, const wxString &label, wxTextCtrl *text)
{
    wxSizer *sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(new wxStaticText(panel, wxID_ANY, label, wxDefaultPosition, wxSize(130, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
    sizerRow->Add(text, 0, wxALIGN_LEFT);
    return sizerRow;
}

wxPanel *OutlookView::createRecipePanel()
{
    wxPanel *panel = new wxPanel(m_wxFrame, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxBoxSizer *topsizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticBox *calorieStaticBox = new wxStaticBox(panel, wxID_ANY, "&Last 7 Days");

    wxSizer *sizerCalorieBox = new wxStaticBoxSizer(calorieStaticBox, wxVERTICAL);
    wxSizer *sizerFirstRow = new wxBoxSizer(wxHORIZONTAL);
    m_bmrPlusExercise = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    sizerFirstRow->Add(CreateTextWithLabelSizer(panel, "BMR + Activity:", m_bmrPlusExercise), 0, wxALL, 10);
    m_consumedCalories = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    sizerFirstRow->Add(CreateTextWithLabelSizer(panel, "-    Consumed Calories:", m_consumedCalories), 0, wxALL, 10);
    sizerCalorieBox->Add(sizerFirstRow, 0, wxGROW | wxALL, 0);

    wxSizer *sizerSecondRow = new wxBoxSizer(wxHORIZONTAL);
    m_netInOut = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    sizerSecondRow->Add(CreateTextWithLabelSizer(panel, "= NET In/Out:", m_netInOut), 0, wxALL, 10);
    m_activityCalories = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    sizerSecondRow->Add(CreateTextWithLabelSizer(panel, "Activity Calories:", m_activityCalories), 0, wxALL, 10);
    sizerCalorieBox->Add(sizerSecondRow, 0, wxGROW | wxALL, 0);

    m_expectedWeightDelta = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    sizerCalorieBox->Add(CreateTextWithLabelSizer(panel, "Expected Weight +/-:", m_expectedWeightDelta), 0, wxALL, 10);

    wxStaticBox *weightStaticBox = new wxStaticBox(panel, wxID_ANY, "&Weight Progress");
    wxSizer *sizerWeightBox = new wxStaticBoxSizer(weightStaticBox, wxVERTICAL);
    m_progressDate = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    sizerWeightBox->Add(CreateTextWithLabelSizer(panel, "Progress Date:", m_progressDate), 0, wxALL, 10);
    m_goalDate = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    sizerWeightBox->Add(CreateTextWithLabelSizer(panel, "Goal Date:", m_goalDate), 0, wxALL, 10);
    m_actualWeightLost = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    sizerWeightBox->Add(CreateTextWithLabelSizer(panel, "Actual Weight +/-:", m_actualWeightLost), 0, wxALL, 10);
    
    topsizer->Add(sizerCalorieBox, 5, wxGROW | wxALL, 5);
    topsizer->Add(sizerWeightBox, 5, wxGROW | wxALL, 5);
    panel->SetSizer(topsizer);
    return panel;
}

void OutlookView::setTotalCaloriesForWeek(int totalCalories)
{
    m_consumedCalories->SetValue(std::to_string(totalCalories));
}

void OutlookView::setTotalExerciseCaloriesForWeek(int totalCalories)
{
    m_activityCalories->SetValue(std::to_string(totalCalories));
}

void OutlookView::setProgressDate(const std::string &progressDate)
{
    m_progressDate->SetValue(progressDate);
}

void OutlookView::setTargetDate(const std::string &targetDate)
{
    m_goalDate->SetValue(targetDate);
}

void OutlookView::setPredictedPoundsLost(const std::string &poundsLost)
{
    m_expectedWeightDelta->SetValue(poundsLost);
}

void OutlookView::setActualPoundsLost(const std::string &poundsLost)
{
    m_actualWeightLost->SetValue(poundsLost);
}

void OutlookView::setBmrPlusExercise(const std::string &bmrPlusExercise) {
    m_bmrPlusExercise->SetValue(bmrPlusExercise);
}

void OutlookView::setDeficitCalories(const std::string &deficitCalories) {
    m_netInOut->SetValue(deficitCalories);
}
