//
// Created by matteo on 10/05/19.
//

#include "ConfigFile.h"

ConfigFile::ConfigFile()
{
    if(!filesystem::exists("config.ini"))
    {
        GenerateConfigFile();
    }

    LoadConfigFile();
}

void ConfigFile::AddKey(std::string key, string value)
{
    valuesMap.insert(pair<string,string>(key,value));
}

void ConfigFile::GenerateConfigFile()
{
    ofstream file;
    file.open("config.ini");

    WriteDefaultConfig(file);

    file.close();
}

void ConfigFile::LoadConfigFile()
{
    //TODO load default settings
    //then override
    ifstream configFile("config.ini");

    if(configFile.is_open())
    {
        string line;
        while(getline(configFile,line))
        {
            ProcessFileEntry(line);
        }
    }
}

void ConfigFile::ProcessFileEntry(string entry)
{
    if(entry.find('=')==string::npos)
        throw runtime_error("Found bad entry: "+entry);

    string key=entry.substr(0,entry.find('='));

    //Erase spaces from 'key'
    std::string::iterator end_pos = std::remove(key.begin(), key.end(), ' ');
    key.erase(end_pos, key.end());
    //

    //check for bad entries
    bool found=false;
    for(string e : entriesDictionary)
    {
        if(e==key)
        {
            found = true;
            break;
        }
    }
    if (!found)
        throw (runtime_error("Bad key entry: "+key));

    string value=entry.substr(entry.find('=')+1,entry.size());
    AddKey(key,value);
}

const vector<string> ConfigFile::entriesDictionary{"PawnccLocation"};
void ConfigFile::WriteDefaultConfig(ofstream & file)
{
    file << "PawnccLocation=pawncc" <<endl;
}