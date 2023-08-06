#include "MyFrame.h"

#include <spdlog/spdlog.h>

MyFrame::MyFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, _("My Macro Calculator"),
                                             wxDefaultPosition, wxSize(1200, 800),
                                             wxDEFAULT_FRAME_STYLE), m_app(this)
{
    m_app.create();
}

MyFrame::~MyFrame()
{

}

void MyFrame::postInit() {
    spdlog::info("MyFrame::postInit");
    m_app.postInit();
}