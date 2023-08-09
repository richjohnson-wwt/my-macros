#include "OutlookView.h"

OutlookView::OutlookView(wxFrame* parent)
    : m_wxFrame(parent)
{
}

wxSizer *OutlookView::CreateTextWithLabelSizer(wxPanel *panel, const wxString &label, wxTextCtrl *text)
{
    wxSizer *sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(new wxStaticText(panel, wxID_ANY, label, wxDefaultPosition, wxSize(100, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
    sizerRow->Add(text, 0, wxALIGN_LEFT);
    return sizerRow;
}

wxPanel *OutlookView::createRecipePanel()
{
    wxPanel *panel = new wxPanel(m_wxFrame, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *calorieSizer = new wxBoxSizer(wxHORIZONTAL);
    m_weekCalories = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    calorieSizer->Add(CreateTextWithLabelSizer(panel, "Consumed Calories:", m_weekCalories), 0, wxALL, 10);
    m_weekExerciseCalories = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    calorieSizer->Add(CreateTextWithLabelSizer(panel, "Exercise Calories:", m_weekExerciseCalories), 0, wxALL, 10);
    topsizer->Add(calorieSizer, 0, wxALL, 10);

    wxBoxSizer *weightStatsSizer = new wxBoxSizer(wxHORIZONTAL);
    m_progressDate = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    weightStatsSizer->Add(CreateTextWithLabelSizer(panel, "Progress Date:", m_progressDate), 0, wxALL, 10);
    m_goalDate = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    weightStatsSizer->Add(CreateTextWithLabelSizer(panel, "Goal Date:", m_goalDate), 0, wxALL, 10);
    topsizer->Add(weightStatsSizer, 0, wxALL, 10);
    
    panel->SetSizer(topsizer);
    return panel;
}

void OutlookView::setTotalCaloriesForWeek(int totalCalories)
{
    m_weekCalories->SetValue(std::to_string(totalCalories));
}

void OutlookView::setTotalExerciseCaloriesForWeek(int totalCalories)
{
    m_weekExerciseCalories->SetValue(std::to_string(totalCalories));
}

void OutlookView::setProgressDate(const std::string &progressDate)
{
    m_progressDate->SetValue(progressDate);
}

void OutlookView::setTargetDate(const std::string &targetDate)
{
    m_goalDate->SetValue(targetDate);
}
