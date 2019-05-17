//
// Created by matteo on 16/09/18.
//

#include <sstream>
#include <wx/mstream.h>
#include "MainWindow.h"
#include "CompilerDialog.h"
#include "IncludeDirDialog.h"
#include "WindowsIDs.h"
#include "CompilerCfgDialog.h"
#include "BluePawnPngRes.hpp"

using namespace std;

MainWindow::MainWindow(ConfigFile & configFile) :configFile(configFile), wxFrame(nullptr,wxID_ANY,"BluePawn",wxDefaultPosition,wxSize(1024,768)), currentFile(new PawnDocument(""))
{
    compileFlags="-i'"+GetIncludesPath()+"' ";

    SetBluePawnIcon();

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    CreateMenuBar();

    CreateToolbar();

    CreateSplittedWindow();

    research=unique_ptr<Research>(new Research(*textEditor));

    StatusBar();

    this->Layout();

    this->Centre( wxBOTH );

    SetupBindings();

    ResetAppName();
}

void MainWindow::SetBluePawnIcon()
{
    //found this fantastic solution online :P
    wxMemoryInputStream pngStream(bluepawn, sizeof(bluepawn));

    wxImage tmp;
    tmp.LoadFile(pngStream, wxBITMAP_TYPE_PNG);

    wxIcon icon;
    icon.CopyFromBitmap(tmp);

    SetIcon(icon);
}

void MainWindow::SetupBindings()
{
    Bind(wxEVT_TOOL,&MainWindow::OnNewPage,this,ID_New);
    Bind(wxEVT_TOOL,&MainWindow::OnOpenFile,this,ID_Open);
    Bind(wxEVT_TOOL,&MainWindow::OnSaveFile,this,ID_Save);
    //Bind(wxEVT_TOOL,&MainWindow::OnSaveFileAs,this,ID_SaveAs);
    Bind(wxEVT_TOOL,&MainWindow::OnFind,this,ID_Find);
    //Bind(wxEVT_TOOL,&MainWindow::OnFindReplace,this,ID_FindReplace);
    Bind(wxEVT_TOOL,&MainWindow::OnCompile,this,ID_Compile);
    Bind(wxEVT_TOOL,&MainWindow::OnChangeIncludesFolder,this,ID_IncFolder);
    Bind(wxEVT_TOOL,&MainWindow::OnCompilerSettings,this,ID_CompilerCfg);
    Bind(wxEVT_STC_MODIFIED,&MainWindow::OnTypeText,this,ID_TextEditor);

    Bind(wxEVT_CHAR_HOOK,&MainWindow::KeyShortcutManager,this);

    Bind(wxEVT_CLOSE_WINDOW,&MainWindow::OnFrameClose,this);
}

void MainWindow::CreateMenuBar()
{
    menuBar = new wxMenuBar( 0 );

    fileMenu = new wxMenu();

    wxMenuItem* newMenuItem=new wxMenuItem( fileMenu, ID_New, "New");
    fileMenu->Append( newMenuItem );

    wxMenuItem * openMenuItem=new wxMenuItem(fileMenu,ID_Open,"Open");
    fileMenu->Append(openMenuItem);

    wxMenuItem * saveMenuItem=new wxMenuItem(fileMenu,ID_Save,"Save");
    fileMenu->Append(saveMenuItem);

    wxMenuItem * saveasMenuItem=new wxMenuItem(fileMenu,ID_Save,"Save as");
    fileMenu->Append(saveasMenuItem);

    menuBar->Append( fileMenu, "File");

    buildMenu=new wxMenu();
    wxMenuItem * buildMenuItem=new wxMenuItem(buildMenu,ID_Compile,"Build");
    buildMenu->Append(buildMenuItem);
    wxMenuItem * lastBuildMenuItem=new wxMenuItem(buildMenu,ID_LastBuild,"Last build");
    buildMenu->Append(lastBuildMenuItem);

    menuBar->Append(buildMenu,"Build");

    settingsMenu=new wxMenu();

    wxMenuItem* includesMenuItem=new wxMenuItem( fileMenu, ID_IncFolder, "Includes folder");
    settingsMenu->Append( includesMenuItem );
    wxMenuItem* compilerSettingsMenuItem=new wxMenuItem(fileMenu,ID_CompilerCfg,"Compiler settings");
    settingsMenu->Append(compilerSettingsMenuItem);

    /*wxMenuItem* compilerMenuItem=new wxMenuItem( fileMenu, wxID_ANY, "Compiler");
    settingsMenu->Append( compilerMenuItem );*/

    menuBar->Append(settingsMenu,"Settings");

    this->SetMenuBar( menuBar );
}

void MainWindow::CreateToolbar()
{
    toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
    newDocTool = toolBar->AddTool( ID_New, wxT("tool"), wxArtProvider::GetBitmap( wxART_NORMAL_FILE, wxART_BUTTON ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

    openTool = toolBar->AddTool( ID_Open, wxT("tool"), wxArtProvider::GetBitmap( wxART_FOLDER_OPEN, wxART_BUTTON ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

    saveTool = toolBar->AddTool( ID_Save, wxT("tool"), wxArtProvider::GetBitmap( wxART_FLOPPY, wxART_BUTTON ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

    //findReplaceTool = toolBar->AddTool( ID_FindReplace, wxT("tool"), wxArtProvider::GetBitmap( wxT("gtk-find-and-replace"), wxART_BUTTON ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

#ifdef __APPLE__
    findTool = toolBar->AddTool( ID_Find, wxT("tool"), wxArtProvider::GetBitmap( wxART_MISSING_IMAGE, wxART_BUTTON ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

    compileTool = toolBar->AddTool( ID_Compile, wxT("tool"), wxArtProvider::GetBitmap( wxART_MISSING_IMAGE, wxART_BUTTON ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );
#else
    findTool = toolBar->AddTool( ID_Find, wxT("tool"), wxArtProvider::GetBitmap( wxT("gtk-find"), wxART_BUTTON ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

    compileTool = toolBar->AddTool( ID_Compile, wxT("tool"), wxArtProvider::GetBitmap( wxT("gtk-execute"), wxART_BUTTON ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );
#endif
    m_tool7 = toolBar->AddTool( wxID_ANY, wxT("tool"), wxArtProvider::GetBitmap( wxART_GO_FORWARD, wxART_BUTTON ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

    toolBar->Realize();
}

void MainWindow::CreateSplittedWindow()
{
    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer( wxVERTICAL );

    m_splitter1 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
    //m_splitter1->Connect( wxEVT_IDLE, wxIdleEventHandler( MainWindow::m_splitter1OnIdle ), NULL, this );

    panel1 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer( wxVERTICAL );

    CreateTextEditor();
    bSizer2->Add( textEditor, 1, wxEXPAND | wxALL, 5 );


    panel1->SetSizer( bSizer2 );
    panel1->Layout();
    bSizer2->Fit( panel1 );
    m_panel2 = new wxPanel( m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer( wxVERTICAL );

    m_treeListCtrl1 = new wxTreeListCtrl( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE );

    bSizer3->Add( m_treeListCtrl1, 1, wxEXPAND | wxALL, 5 );

    m_treeListCtrl1->AppendColumn("Includes (WIP)");
    wxTreeListItem asamp=m_treeListCtrl1->AppendItem(m_treeListCtrl1->GetRootItem(),"a_samp.inc");
    m_treeListCtrl1->AppendItem(asamp,"funzione()");


    m_panel2->SetSizer( bSizer3 );
    m_panel2->Layout();
    bSizer3->Fit( m_panel2 );
    m_splitter1->SplitVertically( panel1, m_panel2, 304 );
    bSizer1->Add( m_splitter1, 1, wxEXPAND, 5 );
    wxSize i=wxFrame::GetSize();
    m_splitter1->SetSashPosition(static_cast<int>(i.x * 0.8));

    this->SetSizer( bSizer1 );
}

void MainWindow::CreateTextEditor()
{
    textEditor = new wxStyledTextCtrl( panel1, ID_TextEditor, wxDefaultPosition, wxDefaultSize, 0, wxEmptyString );
    textEditor->SetTabIndents( true );

    textEditor->StyleSetSize(wxSTC_STYLE_DEFAULT,11);

    textEditor->SetLexer(wxSTC_LEX_CPP);

    textEditor->StyleSetForeground (wxSTC_C_STRING,            wxColour(150,0,0));
    textEditor->StyleSetForeground (wxSTC_C_PREPROCESSOR,      wxColour(165,105,0));
    textEditor->StyleSetForeground (wxSTC_C_IDENTIFIER,        wxColour(40,0,60));
    textEditor->StyleSetForeground (wxSTC_C_NUMBER,            wxColour(0,150,0));
    textEditor->StyleSetForeground (wxSTC_C_CHARACTER,         wxColour(150,0,0));
    textEditor->StyleSetForeground (wxSTC_C_WORD,              wxColour(0,0,150));
    textEditor->StyleSetForeground (wxSTC_C_WORD2,             wxColour(0,150,0));
    textEditor->StyleSetForeground (wxSTC_C_COMMENT,           wxColour(150,150,150));
    textEditor->StyleSetForeground (wxSTC_C_COMMENTLINE,       wxColour(150,150,150));
    textEditor->StyleSetForeground (wxSTC_C_COMMENTDOC,        wxColour(150,150,150));
    textEditor->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORD, wxColour(0,0,200));
    textEditor->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORDERROR, wxColour(0,0,200));
    textEditor->StyleSetBold(wxSTC_C_WORD, true);
    textEditor->StyleSetBold(wxSTC_C_WORD2, true);
    textEditor->StyleSetBold(wxSTC_C_COMMENTDOCKEYWORD, true);

    textEditor->SetKeyWords(0, wxT("return for while break continue do if else false true enum case default Float goto sizeof stock public new native forward switch"));//TODO Add more..
}

void MainWindow::StatusBar()
{
    statusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

    statusBar->SetStatusText("BluePawn by DonSimonetti");
}

void MainWindow::OnNewPage(wxCommandEvent &event)
{
    if(currentFile->isEdited)
    {
        wxMessageDialog newPage(this,"Warning: Any unsaved edit will be lost. Continue?","New Script",wxYES_NO|wxCENTRE);

        if(newPage.ShowModal()==wxID_YES)
        {
            textEditor->SetText("");
            delete currentFile;
            currentFile=new PawnDocument("");
        }
    }
    else
    {
        textEditor->SetText("");
        delete currentFile;
        currentFile=new PawnDocument("");
    }
    ResetAppName();
}

void MainWindow::OnOpenFile(wxCommandEvent &event)
{
    wxFileDialog fileDialog(this,"Open PWN fileMenu","","","BluePawn files (*.pwn)|*.pwn|BluePawn include files (*.inc)|*.inc|Other files ...|*",wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if(currentFile && currentFile->isEdited)
    {
        wxMessageDialog loadMessage(this, "document not saved", "MSG", wxICON_WARNING | wxCENTRE | wxOK);

        if(loadMessage.ShowModal()==wxID_OK)
        {
            ShowFileDialog(fileDialog);
        }
    }
    else
        ShowFileDialog(fileDialog);
}

void MainWindow::OpenPawnDocument(string path)
{
    if(currentFile)
        delete currentFile;

    currentFile=new PawnDocument(path);
    currentFile->WriteInTextEditor(*textEditor);
    currentFile->isEdited=false;
    ResetAppName();
}

void MainWindow::ShowFileDialog(wxFileDialog & fileDialog)
{
    if(fileDialog.ShowModal()==wxID_OK)
    {
        string path=fileDialog.GetPath().ToStdString();
        if(path.length())
        {
            OpenPawnDocument(path);
        }
        else
            wxMessageBox("Cannot open this file","Error",wxICON_ERROR);
    }
}

void MainWindow::OnSaveFile(wxCommandEvent &event)
{
    SaveFile();
}

void MainWindow::OnFind(wxCommandEvent &event)
{
    FindDialog();
}

void MainWindow::OnCompile(wxCommandEvent &event)
{
    if(GetIncludesPath().length())
    {
        if (currentFile->GetPath().length())
        {
            currentFile->Save(textEditor->GetText().ToStdString());
            string output;
            FILE *stream;
            const int max_buff = 512;
            char buffer[max_buff];

            string cmd = configFile.GetKeyValue("PawnccLocation")+" '" + currentFile->GetPath() + "'" +" -D'"+currentFile->GetPath().substr(0,currentFile->GetPath().find_last_of("/"))+"' " + "-i"+GetIncludesPath() + " "+configFile.GetKeyValue("PawnccOptions");
            cmd.append(" 2>&1");
            cout << cmd <<endl;

            CompilerDialog *compilerDialog = new CompilerDialog(this);

            stream = popen(cmd.c_str(), "r");
            if (stream)
            {
                while (!feof(stream))
                {
                    if (fgets(buffer, max_buff, stream) != nullptr)
                        output.append(buffer);
                }
                pclose(stream);

                output.append("\nCompilation ended");

                compilerDialog->Write(output);
            }
            else
                wxMessageBox("Unknown command", "Error", wxICON_ERROR);

            ResetAppName();
        }
        else
            wxMessageBox("PWN file should be saved first", "Error", wxICON_ERROR);
    }
    else
        wxMessageBox("No includes folder selected","Error",wxICON_ERROR);
}

void MainWindow::OnChangeIncludesFolder(wxCommandEvent &event)
{
    IncludeDirDialog * includeDialog=new IncludeDirDialog(this,wxID_ANY,configFile.GetKeyValue("IncludesFold"));

    includeDialog->Show();
}

void MainWindow::OnCompilerSettings(wxCommandEvent &event)
{
    CompilerCfgDialog * compilerCfgDialog=new CompilerCfgDialog(this,wxID_ANY,configFile);

    compilerCfgDialog->Show();
}

void MainWindow::OnTypeText(wxStyledTextEvent &event)
{
    //cout << "ott "<<currentFile->isEdited<<" " << event.GetText().length()<<endl;
    if(event.GetText().length() && currentFile)
    {
        currentFile->isEdited=true;
        ResetAppName();
    }
}

void MainWindow::KeyShortcutManager(wxKeyEvent &event)
{
    //cout << event.GetUnicodeKey()<<endl;
    //if(wxGetKeyState(WXK_CONTROL) and event.GetKeyCode()==70)//if CTRL+F is pressed.. wait, what? 'and'??? wtf is this shit m8? nonono let's remove this shit
    if(wxGetKeyState(WXK_CONTROL))
    {
        switch(event.GetUnicodeKey())
        {
            case 70://CTRL+F
            {
                FindDialog();
                break;
            }
            case 83://CTRL+S
            {
                SaveFile();
                break;
            }
        }
    }
    event.Skip();
}

void MainWindow::ResetAppName()
{
    if(currentFile)
    {
        string title="BluePawn [";

        if(currentFile->isEdited)
            title.append("*");

        title.append(currentFile->GetName()+"]");

        SetTitle(title);
    }
}

void MainWindow::FindDialog()
{
    wxTextEntryDialog findDialog(this,"Type text to search","Find...");

    if(findDialog.ShowModal()==wxID_OK)
    {
        unsigned long pos=research->NewResearch(findDialog.GetValue().ToStdString());

        if(pos!=string::npos)
        {
            textEditor->GotoPos(pos);
            textEditor->SetSelection(pos,pos+research->GetText().length());
        }
        else
        {
            wxMessageBox("Not found","Error",wxICON_ERROR);
        }
    }
}

void MainWindow::SaveFile()
{
    if(!currentFile->GetPath().length())
    {
        wxFileDialog saveDialog(this,"Save","","","BluePawn files (*.pwn)|*.pwn|BluePawn include files (*.inc)|*.inc",wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

        if(saveDialog.ShowModal()==wxID_OK)
        {
            string path=saveDialog.GetPath().ToStdString();

            //Check for file extension
            if(path.substr(path.find_last_of("/")+1,path.length()).find(".")==string::npos)
            {
                path.append(".pwn");
            }

            currentFile->SetPath(path);
            currentFile->Save(textEditor->GetText().ToStdString());
        }
    }
    else
        currentFile->Save(textEditor->GetText().ToStdString());

    ResetAppName();
}

void MainWindow::OnFrameClose(wxCloseEvent &event)
{
    bool canExit=false;
    if(currentFile->isEdited)
    {
        wxMessageDialog newPage(this, "Warning: Any unsaved edit will be lost. Continue?", "New Script",wxYES_NO | wxCENTRE);
        if (newPage.ShowModal() == wxID_YES)
            canExit=true;
    }
    else
        canExit=true;

    if(canExit)
        Destroy();
}