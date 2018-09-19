//
// Created by matteo on 18/09/18.
//

#ifndef BLUEPAWN_DOCUMENT_H
#define BLUEPAWN_DOCUMENT_H

#include <string>
#include <sstream>
#include <fstream>
#include <wx/stc/stc.h>

using namespace std;

class PawnDocument {

public:
    PawnDocument(string _path);

    string GetPath() const
    {
        return path;
    }

    void SetPath(string _path)
    {
        path=_path;
    }

    string GetName();
    void WriteInTextEditor(wxStyledTextCtrl & textEditor);
    void Save(const string & data);

    bool isEdited;

private:

    string path;
};


#endif //BLUEPAWN_DOCUMENT_H
