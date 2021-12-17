#ifndef CHAIKINMONEYFLOWTYPE_H
#include "ChaikinMoneyFlowType.h"
#endif

/*********************** CONSTRUCTORS ******************************/

ChaikinMoneyFlowType::ChaikinMoneyFlowType(float cmf, bool mature) 
{
    this->mature = mature;
    chaikinMoneyFlow = cmf
;}

/*********************** DESTRUCTORS *******************************/

ChaikinMoneyFlowType::~ChaikinMoneyFlowType(){ } 

/************************ FUNCTIONAL *******************************/


float ChaikinMoneyFlowType::getChaikinMoneyFlow()
{
    return chaikinMoneyFlow;
}

bool ChaikinMoneyFlowType::isMature()
{
    return mature;
}