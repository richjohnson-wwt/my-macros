#include "OneOffDialog.h"
#include <spdlog/spdlog.h>

OneOffDialog::OneOffDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style)
: wxDialog(parent, id, title, pos, size, style)
{
    
    wxFlexGridSizer* gatherInfoSizer = new wxFlexGridSizer(2);

    gatherInfoSizer->Add(new wxStaticText(this, wxID_ANY, _("&Name:")), 0, wxALL | wxALIGN_RIGHT, 5);
    m_nameCtrl = new wxTextCtrl(this, wxID_ANY);
    gatherInfoSizer->Add(m_nameCtrl, 0, wxALL, 5);

    gatherInfoSizer->Add(new wxStaticText(this, wxID_ANY, _("&Fat:")), 0, wxALL | wxALIGN_RIGHT, 5);
    m_fatCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    gatherInfoSizer->Add(m_fatCtrl, 0, wxALL, 5);

    gatherInfoSizer->Add(new wxStaticText(this, wxID_ANY, _("&Protein:")), 0, wxALL | wxALIGN_RIGHT, 5);
    m_proteinCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    gatherInfoSizer->Add(m_proteinCtrl, 0, wxALL, 5);

    gatherInfoSizer->Add(new wxStaticText(this, wxID_ANY, _("&Carbs:")), 0, wxALL | wxALIGN_RIGHT, 5);
    m_carbCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    gatherInfoSizer->Add(m_carbCtrl, 0, wxALL, 5);

    gatherInfoSizer->Add(new wxStaticText(this, wxID_ANY, _("&Calories:")), 0, wxALL | wxALIGN_RIGHT, 5);
    m_caloriesCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    gatherInfoSizer->Add(m_caloriesCtrl, 0, wxALL, 5);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(gatherInfoSizer, 0, wxALL, 5);                
    mainSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALL, 5);   
    
    SetSizerAndFit(mainSizer); 
    Centre();
}

wxString OneOffDialog::getName()
{
    return m_nameCtrl->GetValue();
}

wxString OneOffDialog::getFat() {
    return m_fatCtrl->GetValue();
}

wxString OneOffDialog::getProtein() {

    return m_proteinCtrl->GetValue();
}

wxString OneOffDialog::getCarb() {
    return m_carbCtrl->GetValue();
}

wxString OneOffDialog::getCalories() {
    return m_caloriesCtrl->GetValue();
}
