#ifndef FAT_SECRET_VIEW_H
#define FAT_SECRET_VIEW_H

#include <wx/wx.h>
#include <wx/panel.h>

class IFatSecretCallback;

class IFatSecretView {
public:

};

class FatSecretView : public IFatSecretView {
private:
    IFatSecretCallback *m_fatSecretCallback;

public:
    FatSecretView(IFatSecretCallback *callback);
    
    void createPanel(wxPanel *parent);
};


#endif // FAT_SECRET_VIEW_H