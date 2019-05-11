//
// Created by matteo on 16/09/18.
//

#include <iostream>
#include "MainApp.h"

using std::cout;
using std::endl;

bool MainApp::OnInit()
{
    mainWindow=new MainWindow(configFile);
    mainWindow->Show(true);
    return true;
}

int MainApp::OnExit()
{
    //TODO
    return 0;
}

