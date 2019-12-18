//
// Created by matteo on 17/09/18.
//

#include "IncludeDirDialog.h"
#include "WindowsIDs.h"
#include "MainWindow.h"

BEGIN_EVENT_TABLE(IncludeDirDialog, wxFrame)
                EVT_DIRPICKER_CHANGED(ID_IncFoldPicker,IncludeDirDialog::OnChangePath)
                EVT_FILEPICKER_CHANGED(ID_IncFoldPicker,IncludeDirDialog::OnChangePath)
                EVT_CLOSE(IncludeDirDialog::OnExit)
END_EVENT_TABLE()

IncludeDirDialog::IncludeDirDialog( wxWindow* parent, wxWindowID id, string path) : wxFrame( parent, id, "Include folder")
{
    SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxGridSizer* gSizer1;
    gSizer1 = new wxGridSizer( 2, 1, 0, 0 );

    wxStaticText * staticText1 = new wxStaticText( this, wxID_ANY, "Select includes folder:", wxDefaultPosition, wxDefaultSize, 0 );
    staticText1->Wrap( -1 );
    gSizer1->Add( staticText1, 0, wxALL|wxEXPAND, 5 );

    dirPicker = new wxDirPickerCtrl(this, ID_IncFoldPicker, path , "Select a folder", wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL );
    gSizer1->Add( dirPicker, 0, wxEXPAND|wxALIGN_BOTTOM|wxALL, 5 );

    this->SetSizer( gSizer1 );
    this->Layout();

    this->Centre( wxBOTH );
}

void IncludeDirDialog::OnChangePath(wxFileDirPickerEvent &event)
{
    MainWindow * parent= dynamic_cast<MainWindow*>(GetParent());

    //cout <<"dir==" << dirPicker->GetPath()<<endl;//DEBUG
    parent->SetIncludesPath(dirPicker->GetPath().ToStdString());
}

void IncludeDirDialog::OnExit(wxCloseEvent & event)
{
    MainWindow * parent= dynamic_cast<MainWindow*>(GetParent());
    parent->UpdateIncludesTreeList();
    event.Skip();
}