#ifndef SINGLEDATATYPE_H
#include "SingleDataType.h"
#endif
   
/*********************** CONSTRUCTORS ******************************/

SingleDataType::SingleDataType(float datum, bool mature) 
{
    this->mature = mature;
    myData = datum;
}

/************************ SETTERS *******************************/

// Set Data Name //
void SingleDataType::setDataName(std::string name)
{
    myDataName = name;
}

/************************ GETTERS *******************************/

// Get Data //
float SingleDataType::getData()
{
    return myData;
}

// Get Data Name //
std::string SingleDataType::getDataName()
{
    return myDataName;
}

// Is Mature //
bool SingleDataType::isMature()
{
    return mature;
}