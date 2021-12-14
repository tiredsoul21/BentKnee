/* 
 *  This class is a pure super class, one for which contains standardized
 *  class concepts that should be employed across all objects for uniformity
 */

#ifndef CONTAINERTEMPLATE_H
#define CONTAINERTEMPLATE_H

#ifndef CLASSTEMPLATE_H
#include "ClassTemplate.h"
#endif

#include <map>

template <class T>
class ContainerTemplate: public ClassTemplate
{
public: // Public Methods


protected:  // Protected Members
    
    // A mapping of multiple Prices 
    std::map<double, T> myDataMap;

};

#endif