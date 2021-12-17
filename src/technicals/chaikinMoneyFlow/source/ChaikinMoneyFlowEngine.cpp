#ifndef CHAIKINMONEYFLOWENGINE_H
#include "ChaikinMoneyFlowEngine.h"
#endif

/*********************** CONSTRUCTORS ******************************/

ChaikinMoneyFlowEngine::ChaikinMoneyFlowEngine() { }

/*********************** DESTRUCTORS *******************************/

ChaikinMoneyFlowEngine::~ChaikinMoneyFlowEngine() { } 

/************************* SETTERS *********************************/

// setAverageSize //
void ChaikinMoneyFlowEngine::setAverageSize(int size)
{
    if ( size > 0 && size <= 50 )
        averageSize = size;
}

/************************ FUNCTIONAL *******************************/

ChaikinMoneyFlowType ChaikinMoneyFlowEngine::nextEntry(float close, float low, 
                                                       float high, long volume)
{
    // Make this iterations preliminary calculations
    double multiplier = (2*close - low - high) / (high - low);
    //std::cout << std::to_string(multiplier) << "\t";
    double flowVolume = multiplier * volume;

    mature++;

    if (isMature)
    {
        // Calculate the index to be replaced
        int lastIndex = (mature - 1) % averageSize;

        // Calculate the volume sums
        volumeSum += volume - myVolumes[lastIndex];
        flowVolumeSum += flowVolume  - myFlowVolumes[lastIndex];

        // Store the volumes for later
        myVolumes[lastIndex] = volume;
        myFlowVolumes[lastIndex] = flowVolume;
    }
    else
    {
        if (mature == averageSize)
            isMature = true;

        // Calculate the volume sums
        volumeSum += volume;
        flowVolumeSum += flowVolume;

        // Store the volumes for later
        myVolumes[mature -1] = volume;
        myFlowVolumes[mature-1] = flowVolume;
    }
    float cmfValue = flowVolumeSum / volumeSum;

    return ChaikinMoneyFlowType(cmfValue, isMature);
}

