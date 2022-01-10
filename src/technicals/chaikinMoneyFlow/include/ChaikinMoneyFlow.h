/*
 * An object that contains the indicators for the period of provided.
 * Chaikin Money Flow
 * Description: 
 *   Chaikin Money Flow can be used to define a general buying or
 *   selling bias simply with positive or negative values. The indicator 
 *   oscillates above/below the zero line. Generally, buying pressure is 
 *   stronger when the indicator is positive and selling pressure is stronger 
 *   when the indicator is negative.
 * Calculation:
 *   1. Money Flow Multiplier = [(Close  -  Low) - (High - Close)] /(High - Low) 
 *   2. Money Flow Volume = Money Flow Multiplier x Volume for the Period
 *   3. 20-period CMF = 20-period Sum of Money Flow Volume / 20 period Sum of Volume 
 */

#ifndef CHAIKINMONEYFLOW_H
#define CHAIKINMONEYFLOW_H

#ifndef CONTAINERTEMPLATE_H
#include "ContainerTemplate.h"
#endif

#ifndef PRICECONTAINER_H
#include "PriceContainer.h"
#endif

#ifndef DATATYPE1_H
#include "DataType1.h"
#endif

#ifndef CHAIKINMONEYFLOWENGINE_H
#include "ChaikinMoneyFlowEngine.h"
#endif

class ChaikinMoneyFlow: public ContainerTemplate<DataType1>
{
public: // Public Methods

    /*********************** CONSTRUCTORS ******************************/

     // Default Constructor //
    ChaikinMoneyFlow(PriceContainer* priceContainer, int size);

    /*********************** DESTRUCTORS *******************************/

    // Default Destructor //
    ~ChaikinMoneyFlow();
    
private: // Private Members
    
    // Engine to generate technicals data
    ChaikinMoneyFlowEngine myEngine = ChaikinMoneyFlowEngine();
};

#endif