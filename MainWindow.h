//
// Created by matteo on 16/09/18.
//

#ifndef TEXTEDITOR_MAINWINDOW_H
#define TEXTEDITOR_MAINWINDOW_H

#include <string>
#include <fstream>
#include <memory>
#include <wx/wx.h>
#include <wx/stc/stc.h>
#include <wx/splitter.h>
#include <wx/treelist.h>
#include <wx/artprov.h>
#include <wx/config.h>
#include "PawnDocument.h"

using std::string;

class MainWindow : public wxFrame{

public:

    MainWindow();

    const string & GetIncludesPath()
    {
        return includesPath;
    }

    void SetIncludePath(const string & path)
    {
        includesPath=path;
    }

protected:

    string includesPath;
    PawnDocument * currentFile;
    string compileFlags;

    void SaveFile(const string & path);

private:

    wxMenuBar* menuBar;
    wxMenu* fileMenu;
    wxMenu* buildMenu;
    wxMenu * settingsMenu;
    wxToolBar* toolBar;
    wxToolBarToolBase* newDocTool;
    wxToolBarToolBase* openTool;
    wxToolBarToolBase* saveTool;
    wxToolBarToolBase* m_tool4;
    wxToolBarToolBase* compileTool;
    wxToolBarToolBase* m_tool7;
    wxStyledTextCtrl* textEditor;
    wxSplitterWindow* m_splitter1;
    wxPanel* panel1;
    wxPanel* m_panel2;
    wxTreeListCtrl* m_treeListCtrl1;
    wxStatusBar* statusBar;

    void CreateMenuBar();
    void CreateToolbar();
    void CreateSplittedWindow();
    void CreateTextEditor();
    void StatusBar();
    void SetupBindings();
    void ResetAppName();

    void OnNewPage(wxCommandEvent & event);
    void OnOpenFile(wxCommandEvent & event);
    void OnSaveFile(wxCommandEvent & event);
    void OnSaveFileAs(wxCommandEvent & event);
    void OnCompile(wxCommandEvent & event);
    void OnChangeIncludesFolder(wxCommandEvent & event);
    void OnTypeText(wxStyledTextEvent & event);

    void ShowFileDialog(wxFileDialog & fileDialog);
};


#endif //TEXTEDITOR_MAINWINDOW_H
