//
// Created by matteo on 16/09/18.
//

#ifndef TEXTEDITOR_MAINAPP_H
#define TEXTEDITOR_MAINAPP_H

#include <wx/wx.h>
#include <memory>
#include "MainWindow.h"

using namespace std;

class MainApp : public wxApp {

public:

    MainApp()= default;

    virtual bool OnInit() override ;
    virtual int OnExit() override ;

private:

     MainWindow * mainWindow;
};

wxIMPLEMENT_APP(MainApp);

#endif //TEXTEDITOR_MAINAPP_H
