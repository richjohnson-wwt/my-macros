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
    m_weekCalories = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    topsizer->Add(CreateTextWithLabelSizer(panel, "Consumed Calories:", m_weekCalories), 0, wxALL, 10);
    m_weekExerciseCalories = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 20), wxTE_READONLY);
    topsizer->Add(CreateTextWithLabelSizer(panel, "Exercise Calories:", m_weekExerciseCalories), 0, wxALL, 10);
    
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