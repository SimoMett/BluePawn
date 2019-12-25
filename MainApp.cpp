//
// Created by matteo on 16/09/18.
//

#include <iostream>
#include <boost/filesystem.hpp>
#include "MainApp.h"

using std::cout;
using std::endl;

bool MainApp::OnInit()
{
    wxInitAllImageHandlers();

    mainWindow=new MainWindow(configFile);
    mainWindow->Show(true);

    if(argc>1)
    {
        if(boost::filesystem::exists(string(argv[1])))
            mainWindow->OpenPawnDocument(string(argv[1]));
    }
    return true;
}

int MainApp::OnExit()
{
    //TODO
    return 0;
}

