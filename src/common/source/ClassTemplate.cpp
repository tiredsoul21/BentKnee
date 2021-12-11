#ifndef CLASSTEMPLATE_H
#include "ClassTemplate.h"
#endif

/*********************** CONSTRUCTORS ******************************/

ClassTemplate::ClassTemplate()
{
    myErrorString = "";
}

/*********************** DESTRUCTORS *******************************/

ClassTemplate::~ClassTemplate(){ } 

/************************ FUNCTIONAL *******************************/

// errorFound //
bool ClassTemplate::errorFound()
{
    return (this->myErrorString.length() > 0);
}

// clearError //
void ClassTemplate::clearError()
{
    this->myErrorString.clear();
}

// errorString //
std::string ClassTemplate::errorString()
{
    return this->myErrorString;
}

