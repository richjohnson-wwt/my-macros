#include "MyFrame.h"

#include <spdlog/spdlog.h>

MyFrame::MyFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, _("My Macro Calculator"),
                                             wxDefaultPosition, wxSize(1200, 800),
                                             wxDEFAULT_FRAME_STYLE)
{
    // create several text controls
    m_notebookCtrl = m_app.createNotebook(this);
}

MyFrame::~MyFrame()
{

}

void MyFrame::postInit() {
    spdlog::info("MyFrame::postInit");
    m_app.postInit();
}