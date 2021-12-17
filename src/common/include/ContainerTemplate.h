/* 
 * This is a base container unit, that contains a map of a double & class object
 * The double is a datenum, and the object is a unit...Price, Metrics, etc.
 * Common utility will be added to this container. 
 */

#ifndef CONTAINERTEMPLATE_H
#define CONTAINERTEMPLATE_H

#ifndef CLASSTEMPLATE_H
#include "ClassTemplate.h"
#endif

#include <map>
#include <iterator>

template <class T>
class ContainerTemplate: public ClassTemplate
{
public: // Public Methods

    // Get Begin Iterator //
	/*--------------------------------------------------------------
	 * Description - get the iterator for beginnings of container
	 * Input(s):
	 *   void
	 * Output(s):
	 *   map<double, Price>::iterator - iterator for the data 
     *   point if there is a match
	 ---------------------------------------------------------------*/
	typename std::map<double, T>::iterator begin()
    {
        return myDataMap.begin();
    }
    
    // Get End Iterator //
	/*--------------------------------------------------------------
	 * Description - get the iteratorfor end of container
	 * Input(s):
	 *   void
	 * Output(s):
	 *   map<double, Price>::iterator - iterator for the data 
     *   point if there is a match
	 ---------------------------------------------------------------*/
	typename std::map<double, T>::iterator end()
    {
        return myDataMap.end();
    }
    
    	// Get Iterator //
	/*--------------------------------------------------------------
	 * Description - get the iterator for a lookup value in History
     *   from a str / double
	 * Input(s) - Overload 1:
	 *   double - a datenum for the increment
	 * Output(s):
	 *   map<double, T>::iterator - iterator for the data 
     *   point if there is a match
	 ---------------------------------------------------------------*/
    typename std::map<double, T>::iterator getIter(double datenum)
    {
        lastIter = myDataMap.find(datenum);
        if (lastIter == myDataMap.end())
        {
            lastDatenum = -1;
        }
        else
        {
            lastDatenum = lastIter->first;
        }

        return lastIter;
    }
    
    void add(double datenum, T item)
    {
        myDataMap.insert( std::pair<double,T>(datenum,item) );
    }
        
        
protected:  // Protected Members
    // Last looked up items, this is to save time and resources
    typename std::map<double, T>::iterator lastIter;
    double lastDatenum;
    
    // A mapping of multiple incremental data points
    std::map<double, T> myDataMap;

};

#endif