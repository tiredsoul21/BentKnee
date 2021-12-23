#ifndef CHAIKINMONEYFLOW_H
#include "ChaikinMoneyFlow.h"
#endif

/*********************** CONSTRUCTORS ******************************/

ChaikinMoneyFlow::ChaikinMoneyFlow(PriceContainer* priceContainer, int size)
{
    std::map<double, Price>::iterator it;
    for (it = priceContainer->begin(); it != priceContainer->end(); it++)
    {
        myEngine.setAverageSize(size);
        add(it->first, myEngine.nextEntry(it->second.getClose(), 
                                          it->second.getLow(),
                                          it->second.getHigh(), 
                                          it->second.getVolume()));
    }
}

/*********************** DESTRUCTORS *******************************/

ChaikinMoneyFlow::~ChaikinMoneyFlow() { } 




