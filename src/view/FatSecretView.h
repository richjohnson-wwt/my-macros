#ifndef FAT_SECRET_VIEW_H
#define FAT_SECRET_VIEW_H

#include "../model/FatSecretModel.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/event.h>
#include <wx/srchctrl.h>
#include "wx/notebook.h"

class IFatSecretCallback;

class IFatSecretView {
public:
    virtual void setSearchResults(const FatSecret::SearchFoods& searchFoods) = 0;
    // virtual void setGetResult(const FatSecret::GetFood& getFood) = 0;
};

class FatSecretView : public wxEvtHandler, public IFatSecretView {
private:
    IFatSecretCallback *m_fatSecretCallback;

    wxButton *m_refreshTokenButton;

    wxSearchCtrl *m_searchText;
    wxListCtrl *m_searchListCtrl;

    wxButton *m_getResultButton;

protected:
    void onRefreshToken(wxCommandEvent &event);
    void onAddFood(wxCommandEvent &event);

    void onSearch(wxCommandEvent& event);
    void onSearchCancel(wxCommandEvent& event);
    void onGetResult(wxCommandEvent& event);

public:
    FatSecretView(IFatSecretCallback *callback);
    
    wxPanel *createPanel(wxBookCtrlBase *parent);

    void setSearchResults(const FatSecret::SearchFoods& searchFoods);
    // void setGetResult(const FatSecret::GetFood& getFood);

};


#endif // FAT_SECRET_VIEW_H