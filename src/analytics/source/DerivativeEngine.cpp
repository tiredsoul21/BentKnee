#ifndef DERIVATIVEENGINE_H
#include "DerivativeEngine.h"
#endif

#include <iostream>
/*********************** CONSTRUCTORS ******************************/

DerivativeEngine::DerivativeEngine()
{
    
}

/*********************** DESTRUCTORS *******************************/

DerivativeEngine::~DerivativeEngine()
{
    
}

/************************ FUNCTIONAL *******************************/

// Next Entry - Overload 1 //
DataType3 DerivativeEngine::nextEntry(float datum)
{
    return calculate(datum);
}

// Next Entry - Overload 2 //
DataType3 DerivativeEngine::nextEntry(double datum)
{
    return calculate(datum);
}

// Next Entry - Overload 3 //
DataType3 DerivativeEngine::nextEntry(int datum)
{
    return calculate(datum);
}

// Calculate //
template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
DataType3 DerivativeEngine::calculate(T datum)
{
    double thirdDeriv;
    bool first = false;
    bool second = false;
    bool third = false;
    
    // Boolean letting us know if the current step is a sampling step
    bool nextStep = (mature % derivativeStep == 0);
    if (nextStep)
    {
        // The first step is where we start computing the first derivative
        if (mature >= derivativeStep)
        {
            firstDeriv1 = firstDeriv2;
            firstDeriv2 = (datum - lastDatum)/derivativeStep;
            
        }
        lastDatum = datum;

        first = true;
    }
    if (nextStep && mature >= derivativeStep*2)
    {
        // The second step is where we start computing the second derivative
        if (mature >= derivativeStep*3)
            secondDeriv1 = secondDeriv2;
        
        secondDeriv2 = (firstDeriv2 - firstDeriv1);
        second = true;
    }
    if (nextStep && mature >= derivativeStep*3)
    {
        // The third step is where we start computing the third derivative
        thirdDeriv = (secondDeriv2 - secondDeriv1);
        third = true;
    }
    
    DataType3 returnValue;
    
    if (third)
        returnValue = DataType3(firstDeriv2, secondDeriv2, thirdDeriv, true);
    else if (second)
        returnValue = DataType3(firstDeriv2, secondDeriv2, true);
    else if (first)
        returnValue = DataType3(firstDeriv2, true);
    
    returnValue. setDataName("First Derivative", 
                             "Second Derivative",
                             "Third Derivative");
    
    mature++;
    return returnValue;
}

// Clear Engine //
void DerivativeEngine::clear()
{
    // This effectively clears the engine
    int mature = 0;
}

/************************ SETTERS *******************************/

// Set Derivative Step Size //  
void DerivativeEngine::setDerivativeStep(int stepSize)
{
    if (stepSize > 0)
        derivativeStep = stepSize;
    clear();
}

/************************ GETTERS *******************************/

// Get Derivative Step Size //  
int DerivativeEngine::getDerivativeSize()
{
    return derivativeStep;
}

