//
// Created by matteo on 10/05/19.
//

#ifndef BLUEPAWN_CONFIGFILE_H
#define BLUEPAWN_CONFIGFILE_H

#include <fstream>
#include <filesystem>
#include <iostream>
#include <map>

using namespace std;

class ConfigFile
{
public:

    ConfigFile();

    std::string GetKey(const std::string & key)
    {
        return valuesMap[key];
    }

    void AddKey(std::string key, string value);//TODO

private:

    void InitValuesMap();

    map<string,string> valuesMap;

};


#endif //BLUEPAWN_CONFIGFILE_H
