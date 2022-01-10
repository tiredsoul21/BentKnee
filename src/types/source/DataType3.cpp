#ifndef DATATYPE3_H
#include "DataType3.h"
#endif
   
/*********************** CONSTRUCTORS ******************************/

DataType3::DataType3()
{
    data1Set = false;
    data2Set = false;
    data3Set = false;
}

DataType3::DataType3(double datum1, bool mature) : DataType3()
{
    this->mature = mature;
    myData1 = datum1;
    data1Set = true;
}

DataType3::DataType3(double datum1, double datum2, bool mature) : DataType3()
{
    this->mature = mature;
    myData1 = datum1;
    data1Set = true;
    myData2 = datum2;
    data2Set = true;
}

DataType3::DataType3(double datum1, double datum2, double datum3, bool mature) : DataType3()
{
    this->mature = mature;
    myData1 = datum1;
    data1Set = true;
    myData2 = datum2;
    data2Set = true;
    myData3 = datum3;
    data3Set = true;
}

/************************ SETTERS *******************************/

// Set Data Name //
void DataType3::setData1Name(std::string name)
{
    myData1Name = name;
}
void DataType3::setData2Name(std::string name)
{
    myData2Name = name;
}
void DataType3::setData3Name(std::string name)
{
    myData3Name = name;
}
void DataType3::setDataName(std::string name1, std::string name2, std::string name3)
{
    setData1Name(name1);
    setData2Name(name2);
    setData3Name(name3);
}

/************************ GETTERS *******************************/

// Get Data //
double DataType3::getData1()
{
    return myData1;
}
double DataType3::getData2()
{
    return myData2;
}
double DataType3::getData3()
{
    return myData3;
}


// Get Data Name //
std::string DataType3::getData1Name()
{
    return myData1Name;
}
std::string DataType3::getData2Name()
{
    return myData2Name;
}
std::string DataType3::getData3Name()
{
    return myData3Name;
}

// Is Mature //
bool DataType3::isMature()
{
    return mature;
}

// Is Data Set //
bool DataType3::isData1Set()
{
    return data1Set;
}
bool DataType3::isData2Set()
{
    return data2Set;
}
bool DataType3::isData3Set()
{
    return data3Set;
}