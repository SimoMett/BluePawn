//
// Created by matteo on 11/05/19.
//

#ifndef BLUEPAWN_COMPILERCFGDIALOG_H
#define BLUEPAWN_COMPILERCFGDIALOG_H


#include <wx/wx.h>

class CompilerCfgDialog : public wxFrame
{
public:
    CompilerCfgDialog(wxWindow* parent, wxWindowID id);

private:

    wxTextCtrl * text_ctrl_3;
    wxTextCtrl * text_ctrl_4;

};


#endif //BLUEPAWN_COMPILERCFGDIALOG_H
