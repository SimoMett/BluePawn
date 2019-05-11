//
// Created by matteo on 11/05/19.
//

#include "CompilerCfgDialog.h"

CompilerCfgDialog::CompilerCfgDialog(wxWindow *parent, wxWindowID id): wxFrame( parent, id, "Compiler settings")
{
    SetTitle("Compiler settings");

    SetPosition(wxPoint(0,0));

    text_ctrl_3 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    text_ctrl_4 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);

    text_ctrl_3->WriteText("babla");
    text_ctrl_4->WriteText("babla2");

    wxBoxSizer* sizer_3 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* label_2 = new wxStaticText(this, wxID_ANY, wxT("Pawncc location:"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER|wxALIGN_LEFT|wxST_NO_AUTORESIZE);
    sizer_4->Add(label_2, 1, wxALIGN_CENTER|wxALL, 4);
    sizer_4->Add(text_ctrl_3, 3, wxALIGN_CENTER|wxALL, 8);
    sizer_3->Add(sizer_4, 2, wxEXPAND, 0);
    wxStaticText* label_3 = new wxStaticText(this, wxID_ANY, wxT("Compiler options:"));
    sizer_5->Add(label_3, 1, wxALIGN_CENTER|wxALL, 4);
    sizer_5->Add(text_ctrl_4, 3, wxALIGN_CENTER|wxALIGN_RIGHT|wxALL, 8);
    sizer_3->Add(sizer_5, 2, wxEXPAND, 0);
    SetSizer(sizer_3);
    sizer_3->Fit(this);
    Layout();
}