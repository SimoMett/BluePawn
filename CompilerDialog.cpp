//
// Created by matteo on 17/09/18.
//

#include "CompilerDialog.h"

CompilerDialog::CompilerDialog(wxWindow *parent) : wxFrame(parent,wxID_ANY,"Compilation Result")
{
    SetMinSize(wxSize(1000,400));
    textCtrl=new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE|wxTE_PROCESS_TAB);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(textCtrl, 1, wxEXPAND);
    SetSizer(sizer);

    textCtrl->SetEditable(false);
    textCtrl->WriteText("Compiling...\n\n");

    Show(true);
}

void CompilerDialog::Write(std::string text)
{
    textCtrl->AppendText(text);
}