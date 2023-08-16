#ifndef ONE_OFF_DIALOG_H
#define ONE_OFF_DIALOG_H

#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/button.h>


class OneOffDialog : public wxDialog {
private:
    wxTextCtrl *m_nameCtrl;
    wxTextCtrl *m_fatCtrl;
    wxTextCtrl *m_proteinCtrl;
    wxTextCtrl *m_carbCtrl;
    wxTextCtrl *m_caloriesCtrl;
    // wxButton *m_okButton;
    // wxButton *m_cancelButton;

public:
    OneOffDialog(wxWindow *parent, 
        wxWindowID id, 
        const wxString &title, 
        const wxPoint &pos = wxDefaultPosition, 
        const wxSize &size = wxDefaultSize, 
        long style = wxDEFAULT_DIALOG_STYLE);

    // virtual void OnOk(wxCommandEvent& event);
    // virtual void OnCancel(wxCommandEvent& event);

    wxString getName();
    wxString getFat();
    wxString getProtein();
    wxString getCarb();
    wxString getCalories();

};

#endif // ONE_OFF_DIALOG_H