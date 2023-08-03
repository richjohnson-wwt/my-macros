#ifndef MY_FRAME_H
#define MY_FRAME_H


#include "MyMacroApp.h"

// #include "wx/aui/aui.h"
#include "wx/notebook.h"
#include <wx/wx.h>

class MyFrame : public wxFrame
{
public:
    MyFrame(wxWindow *parent);
    ~MyFrame();

    void postInit();

protected:

private:
    // wxAuiManager m_mgr;
    // wxNotebook *m_notebookCtrl;

    MyMacroApp m_app;
    
};

#endif // MY_FRAME_H
