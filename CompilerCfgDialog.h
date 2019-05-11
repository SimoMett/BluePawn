//
// Created by matteo on 11/05/19.
//

#ifndef BLUEPAWN_COMPILERCFGDIALOG_H
#define BLUEPAWN_COMPILERCFGDIALOG_H


#include <wx/wx.h>

class CompilerCfgDialog : public wxDialog
{
public:
    CompilerCfgDialog(wxWindow* parent, wxWindowID id);

private:

    wxTextCtrl * pawncLocTextCtrl;
    wxTextCtrl * pawncOptTextCtrl;

};


#endif //BLUEPAWN_COMPILERCFGDIALOG_H
