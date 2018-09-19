//
// Created by matteo on 17/09/18.
//

#ifndef BLUEPAWN_INCLUDEDIRDIALOG_H
#define BLUEPAWN_INCLUDEDIRDIALOG_H

#include <wx/wx.h>
#include <wx/filepicker.h>

using namespace std;

class IncludeDirDialog : public wxFrame {

public:

    IncludeDirDialog(wxWindow* parent, wxWindowID id);

    string GetPath()
    {
        return dirPicker->GetPath().ToStdString();
    }

private:

    wxStaticText * staticText1;
    wxDirPickerCtrl * dirPicker;

    void OnClose(wxCloseEvent & event);

    DECLARE_EVENT_TABLE()
};


#endif //BLUEPAWN_INCLUDEDIRDIALOG_H
