//
// Created by matteo on 19/09/18.
//

#include "Research.h"

unsigned long Research::NewResearch(string _text)
{
    lastPos=0;
    text=_text;
    return _text.length()? Search(): string::npos;
}

unsigned long Research::Search()
{
    lastPos=source.GetText().ToStdString().find(text,(lastPos==string::npos? 0 : lastPos));
    return lastPos;
}