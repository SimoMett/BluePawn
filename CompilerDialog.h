//
// Created by matteo on 17/09/18.
//

#ifndef BLUEPAWN_COMPILERDIALOG_H
#define BLUEPAWN_COMPILERDIALOG_H

#include <wx/wx.h>

class CompilerDialog : public wxFrame{

public:
    CompilerDialog(wxWindow * parent);

    void Write(std::string text);

private:
    wxTextCtrl * textCtrl;

};


#endif //BLUEPAWN_COMPILERDIALOG_H
