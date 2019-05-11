//
// Created by matteo on 11/05/19.
//

#ifndef BLUEPAWN_COMPILERCFGDIALOG_H
#define BLUEPAWN_COMPILERCFGDIALOG_H


#include <wx/wx.h>
#include "ConfigFile.h"

class CompilerCfgDialog : public wxDialog
{
public:
    CompilerCfgDialog(wxWindow* parent, wxWindowID id,ConfigFile & configFile);

private:

    ConfigFile & configFile;
    wxTextCtrl * pawncLocTextCtrl;
    wxTextCtrl * pawncOptTextCtrl;

};


#endif //BLUEPAWN_COMPILERCFGDIALOG_H
