//
// Created by matteo on 25/06/19.
//

#include <algorithm>
#include "IncludeFile.h"

IncludeFile::IncludeFile(string path): path(path){}

vector<string> IncludeFile::GetNatives()
{
    vector<string> natives;

    ifstream stream;
    stream.open(path);
    if(stream.is_open())
    {
        string line;
        while(getline(stream,line))
        {
            if(auto pos=line.find("native")!=string::npos)
            {
                line.erase(0,pos+string("native").length());

                line.erase(line.find(";"),line.size());

                //TODO erase useless stuff from line (eg labels)

                //cout <<line <<endl;
                natives.push_back(line);
            }
        }
        stream.close();
    }

    sort(natives.begin(),natives.end());
    return natives;
}