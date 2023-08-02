
#include "WxApp.h"

wxDECLARE_APP(MyApp);
wxIMPLEMENT_APP(MyApp);
 
bool MyApp::OnInit() {
    
    MyFrame* frame = new MyFrame(NULL);
    SetTopWindow(frame);
    frame->Show();
    frame->postInit();
    return true;                    
    
}