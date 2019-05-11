//
// Created by matteo on 11/05/19.
//

#include "CompilerCfgDialog.h"
#include "ConfigFile.h"

CompilerCfgDialog::CompilerCfgDialog(wxWindow *parent, wxWindowID id, ConfigFile & configFile): wxDialog( parent, id, "Compiler settings"), configFile(configFile)//BIG TODO
{
    this->SetSizeHints( wxSize( 600,-1 ), wxDefaultSize );

    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer* bSizer4;
    bSizer4 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText * m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Pawncc location:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText1->Wrap( -1 );
    bSizer4->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    pawncLocTextCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    bSizer4->Add( pawncLocTextCtrl, 1, wxALL|wxEXPAND, 5 );
    pawncLocTextCtrl->AppendText(configFile.GetKeyValue("PawnccLocation"));


    bSizer2->Add( bSizer4, 1, wxALL|wxEXPAND, 5 );

    wxBoxSizer* bSizer5;
    bSizer5 = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText * m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Compiler options:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticText2->Wrap( -1 );
    bSizer5->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    pawncOptTextCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    bSizer5->Add( pawncOptTextCtrl, 1, wxEXPAND|wxALL, 5 );
    pawncOptTextCtrl->AppendText(configFile.GetKeyValue("PawnccOptions"));


    bSizer2->Add( bSizer5, 1, wxALL|wxEXPAND, 5 );

    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer( wxHORIZONTAL );


    bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

    wxButton * m_button3 = new wxButton( this, wxID_ANY, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer3->Add( m_button3, 0, wxALL, 5 );

    wxButton * m_button4 = new wxButton( this, wxID_ANY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer3->Add( m_button4, 0, wxALL, 5 );

    wxButton * m_button5 = new wxButton( this, wxID_ANY, wxT("Exit"), wxDefaultPosition, wxDefaultSize, 0 );
    bSizer3->Add( m_button5, 0, wxALL, 5 );


    bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );


    this->SetSizer( bSizer2 );
    this->Layout();
    bSizer2->Fit( this );

    this->Centre( wxBOTH );
}