//
// Created by matteo on 17/09/18.
//

#include "IncludeDirDialog.h"
#include "WindowsIDs.h"
#include "MainWindow.h"

BEGIN_EVENT_TABLE(IncludeDirDialog, wxFrame)
    EVT_CLOSE(IncludeDirDialog::OnClose)
END_EVENT_TABLE()

IncludeDirDialog::IncludeDirDialog( wxWindow* parent, wxWindowID id) : wxFrame( parent, id, "Include folder")
{
    SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxGridSizer* gSizer1;
    gSizer1 = new wxGridSizer( 2, 1, 0, 0 );

    staticText1 = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
    staticText1->Wrap( -1 );
    gSizer1->Add( staticText1, 0, wxALL|wxEXPAND, 5 );

    dirPicker = new wxDirPickerCtrl( this, ID_IncFoldPicker, static_cast<MainWindow*>(parent)->GetIncludesPath(), wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
    gSizer1->Add( dirPicker, 0, wxEXPAND|wxALIGN_BOTTOM|wxALL, 5 );

    this->SetSizer( gSizer1 );
    this->Layout();

    this->Centre( wxBOTH );
}

void IncludeDirDialog::OnClose(wxCloseEvent &event)
{
    MainWindow * parent= static_cast<MainWindow*>(GetParent());

    parent->SetIncludePath(dirPicker->GetPath().ToStdString());

    Destroy();
}