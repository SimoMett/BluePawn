//
// Created by matteo on 10/05/19.
//

#include "ConfigFile.h"

ConfigFile::ConfigFile()
{
    if(!filesystem::exists("config.ini"))
    {
        ofstream file;
        file.open("config.ini");
        file.close();
    }

    ifstream configFile("config.ini");

    if(configFile.is_open())
    {
        string line;
        while(getline(configFile,line))
        {
            cout << line <<endl;//debug
        }
    }

    //TODO default settings
    AddKey("PawnccLocation","pawncc");

    InitValuesMap();
}

void ConfigFile::AddKey(std::string key, string value)
{
    //TODO
}

void ConfigFile::InitValuesMap()
{
    //TODO
}
