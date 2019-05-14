//
// Created by matteo on 10/05/19.
//

#ifndef BLUEPAWN_CONFIGFILE_H
#define BLUEPAWN_CONFIGFILE_H

#include <fstream>
#include <filesystem>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <exception>

using namespace std;

class ConfigFile
{
public:

    ConfigFile();
    ~ConfigFile();

    std::string GetKeyValue(const string & key)
    {
        string value;
        if(valuesMap.find(key)!=valuesMap.end())
            value=valuesMap[key];
        return valuesMap[key];
    }

    void SetKeyValue(std::string key, string value);

    void SaveConfigFile();

private:
    void GenerateConfigFile();
    void LoadDefaultSettings();
    void LoadConfigFile();

    void ProcessFileEntry(string entry);

    void WriteDefaultConfig(ofstream & file);

    map<string,string> valuesMap;

    static const vector<string> entriesDictionary;
};


#endif //BLUEPAWN_CONFIGFILE_H
