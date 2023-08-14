#include "GoalView.h"

wxSizer *GoalView::createTextWithLabelSizer(wxPanel *panel, const wxString &label, wxTextCtrl *text) {
    wxSizer *sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(new wxStaticText(panel, wxID_ANY, label, wxDefaultPosition, wxSize(100, 20)), 0, wxALIGN_LEFT | wxRIGHT, 5);
    sizerRow->Add(text, 0, wxALIGN_LEFT);
    return sizerRow;
}

wxPanel *GoalView::createGoalPanel(wxNotebook *parent)
{
    wxPanel * panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(400, 150));

    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

    m_startDateTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20), wxTE_READONLY);
    topsizer->Add(createTextWithLabelSizer(panel, "Start Date:", m_startDateTextCtrl), 0, wxALL, 10);

    m_targetWeightTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20), wxTE_READONLY);
    topsizer->Add(createTextWithLabelSizer(panel, "Target Weight:", m_targetWeightTextCtrl), 0, wxALL, 10);

    m_bmrCaloriesTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20), wxTE_READONLY);
    topsizer->Add(createTextWithLabelSizer(panel, "BMR Calories:", m_bmrCaloriesTextCtrl), 0, wxALL, 10);

    m_fatPercentTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20), wxTE_READONLY);
    topsizer->Add(createTextWithLabelSizer(panel, "Fat Percent:", m_fatPercentTextCtrl), 0, wxALL, 10);

    m_proteinPercentTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20), wxTE_READONLY);
    topsizer->Add(createTextWithLabelSizer(panel, "Protein Percent:", m_proteinPercentTextCtrl), 0, wxALL, 10);

    m_carbPercentTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 20), wxTE_READONLY);
    topsizer->Add(createTextWithLabelSizer(panel, "Carb Percent:", m_carbPercentTextCtrl), 0, wxALL, 10);

    panel->SetSizer(topsizer);
    return panel;
}

void GoalView::setStartDate(const std::string &date) {
    m_startDateTextCtrl->SetValue(date);
    
}

void GoalView::setTargetWeight(const std::string &targetWeight) {
    m_targetWeightTextCtrl->SetValue(targetWeight);    
}

void GoalView::setBmrCalories(const std::string &bmrCalories) {
    m_bmrCaloriesTextCtrl->SetValue(bmrCalories);
}

void GoalView::setFatPercent(const std::string &fatPercent) {
    m_fatPercentTextCtrl->SetValue(fatPercent);
}

void GoalView::setProteinPercent(const std::string &proteinPercent) {
    m_proteinPercentTextCtrl->SetValue(proteinPercent);
}

void GoalView::setCarbPercent(const std::string &carbPercent) {
    m_carbPercentTextCtrl->SetValue(carbPercent);
}
