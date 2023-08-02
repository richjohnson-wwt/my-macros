#ifndef WX_APP_H
#define WX_APP_H

#include <wx/aui/aui.h>
#include "MyFrame.h"
#include <wx/wx.h>

 
class MyApp : public wxApp
{
public:
    bool OnInit();
    
};
 
#endif // WX_APP_H