//
// Created by matteo on 25/06/19.
//

#ifndef BLUEPAWN_INCLUDEFILE_H
#define BLUEPAWN_INCLUDEFILE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class IncludeFile
{
public:
    IncludeFile(string path);

    vector<string> GetNatives();

private:
    string path;
};


#endif //BLUEPAWN_INCLUDEFILE_H
