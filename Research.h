//
// Created by matteo on 19/09/18.
//

#ifndef BLUEPAWN_RESEARCH_H
#define BLUEPAWN_RESEARCH_H

#include <string>
#include <wx/stc/stc.h>

using namespace std;

class Research {

public:
    Research(const wxStyledTextCtrl & _source) :source(_source), lastPos(string::npos){}

    unsigned long NewResearch(string _text);
    unsigned long Search();

    const string & GetText()
    {
        return text;
    }

private:
    string text;
    const wxStyledTextCtrl & source;
    unsigned long lastPos;

};


#endif //BLUEPAWN_RESEARCH_H
