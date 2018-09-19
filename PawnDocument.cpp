//
// Created by matteo on 18/09/18.
//

#include "PawnDocument.h"

PawnDocument::PawnDocument(string _path): path(_path), isEdited(false){}

string PawnDocument::GetName()
{
    string name;
    if(path.length())
        name=path.substr(path.find_last_of("/")+1,path.length());
    else
        name="untitled";
    return name;
}

void PawnDocument::WriteInTextEditor(wxStyledTextCtrl &textEditor)
{
    std::ifstream file;
    file.open(path);
    if(file.good() && file.is_open())
    {
        std::stringstream codeText;

        string line;
        while (getline(file,line))
            codeText<<line<<std::endl;

        textEditor.SetText(codeText.str());
    }
}

void PawnDocument::Save(const string & data)
{
    ofstream outputFile;
    outputFile.open(path);
    outputFile << data<<endl;
    outputFile.close();
    isEdited=false;
}