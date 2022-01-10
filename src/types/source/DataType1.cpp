#ifndef DATATYPE1_H
#include "DataType1.h"
#endif
   
/*********************** CONSTRUCTORS ******************************/

DataType1::DataType1(double datum, bool mature) 
{
    this->mature = mature;
    myData = datum;
    dataSet = true;
}

/************************ SETTERS *******************************/

// Set Data Name //
void DataType1::setDataName(std::string name)
{
    myDataName = name;
}

/************************ GETTERS *******************************/

// Get Data //
double DataType1::getData()
{
    return myData;
}

// Get Data Name //
std::string DataType1::getDataName()
{
    return myDataName;
}

// Is Mature //
bool DataType1::isMature()
{
    return mature;
}

// Is Data Set //
bool DataType1::isDataSet()
{
    return dataSet;
}