#include "MyFrame.h"

#include <spdlog/spdlog.h>

MyFrame::MyFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, _("In/Out"),
                                             wxDefaultPosition, wxSize(1400, 1000),
                                             wxDEFAULT_FRAME_STYLE), m_app(this)
{
    m_app.create();
}

MyFrame::~MyFrame()
{

}

void MyFrame::postInit() {
    spdlog::debug("MyFrame::postInit");
    m_app.postInit();
}