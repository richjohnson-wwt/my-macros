#ifndef FAT_SECRET_VIEW_H
#define FAT_SECRET_VIEW_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/event.h>
#include <wx/srchctrl.h>
#include "wx/notebook.h"

class IFatSecretCallback;

class IFatSecretView {
public:

};

class FatSecretView : public wxEvtHandler, public IFatSecretView {
private:
    IFatSecretCallback *m_fatSecretCallback;

    // wxButton *m_refreshTokenButton;

    // wxSearchCtrl *m_searchText;
    // wxListCtrl *m_searchListCtrl;

protected:
    void onRefreshToken(wxCommandEvent &event);
    void onAddFood(wxCommandEvent &event);

    void onSearch(wxCommandEvent& event);
    void onSearchCancel(wxCommandEvent& event);

public:
    FatSecretView(IFatSecretCallback *callback);
    
   wxPanel *createPanel(wxBookCtrlBase *parent);
};


#endif // FAT_SECRET_VIEW_H