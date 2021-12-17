#ifndef PRICECONTAINER_H
#include "PriceContainer.h"
#endif

/*********************** CONSTRUCTORS ******************************/

PriceContainer::PriceContainer()
{ 
    // Default Input Format
    myInputFormat = "MM/DD/YYYY hh:mm:ss";
    
    // Default Display Format
    myInputFormat = "YYYY-MM-DD";
    
    // Initialize the datenum engine
    myDatenumEngine = new DateEngine();
    
    // Initialize these to 0
    lastIter = myDataMap.begin();
    lastDatenum = 0;
    lastDateStr = "01/01/1970 00:00:00";
}

/*********************** DESTRUCTORS *******************************/

// Default Constructor //
PriceContainer::~PriceContainer() { }

/*********************** SETTERS ***********************************/

// setDateFormat //
void PriceContainer::setInputDateFormat(std::string* dateFormat)
{
    // If the date format is accepted by the engine, its a good date
    if( myDatenumEngine->setDateFormat(dateFormat) )
    {
        myInputFormat = *dateFormat;
    }
    else
    {
        myErrorString += myDatenumEngine->errorString();
        myErrorString += "PriceContainer::setInputDateFormat - ";
        myErrorString += "Error: Failed to set dateFormat, didn't pass DatenumEngine validation\n";
        myDatenumEngine->clearError();
    }
}

// setDateFormat
void PriceContainer::setDisplayDateFormat(std::string* dateFormat)
{
    // We don't really care if the user provides us garbage, the ambiguous 
    // assignment would just give them garbage back
    myDisplayFormat = *dateFormat;
}

/*********************** GETTERS ***********************************/

// getIter - Overload 1 //
std::map<double, Price>::iterator PriceContainer::getIter(std::string* dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
        myErrorString += "PriceContainer::getIter 1 - Failed to get iter for " + 
                *dateStr + ".  Not found in container.\n";

    // This will ether be last or some other iter, always good
    return lastIter;
}

// getIter - Overload 2//
std::map<double, Price>::iterator PriceContainer::getIter(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getIter 2 - Failed to get iter for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
    }
        
    // This will ether be last or some other iter, always good
    return lastIter;
}

// getDateNum - Overload 1 //
double PriceContainer::getDatenum(std::string* dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        myErrorString += "PriceContainer::getDatenum - Failed to get datenum for " + 
                *dateStr + ".  Not found in container.\n";
        return -1;
    }

    // Return the found datenum
    return lastDatenum;
}

// getDateNum - Overload 2 //
double PriceContainer::getDatenum(std::map<double, Price>::iterator it)
{
    // This is easy, they already gave us an iter, just use it!
    if (it != myDataMap.end())
    {
        lastDatenum = it->first;
        lastDateStr = it->second.getDateStr();
        lastIter = it;
        return lastDatenum;
    }
    else
    {
        // Not found
        myErrorString += "PriceContainer::getDatenum 2 - Failed to get datenum: bad iter\n";
        return -1;
    }
}

// getDateStr - Overload 1//
std::string PriceContainer::getDateStr(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getDateStr 1 - Failed to get date string for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return "";
    }
      
    // This will ether be last or some other iter, always good
    return lastDateStr;
}

// getDateStr - Overload 2//
std::string PriceContainer::getDateStr(std::map<double, Price>::iterator it)
{
    // This is easy, they already gave us an iter, just use it!
    if (it != myDataMap.end())
    {
        // Found it
        lastDatenum = it->first;
        lastDateStr = it->second.getDateStr();
        lastIter = it;
        return lastDateStr;
    }
    else
    {
        // Not found
        myErrorString += "PriceContainer::getDateStr 2 - Failed to get date string: bad iter\n";
        return "";
    }
}

// Free Format Datenum String - Overload 1 //
std::string PriceContainer::getCustomDateString(double dateNum)
{
    // In this function, we allow for any date generation, not bound to mapping
    myDatenumEngine->setDatenum(dateNum);
	return myDatenumEngine->looseDateString(myDisplayFormat);
}

// Free Format Datenum String - Overload 2 //
std::string PriceContainer::getCustomDateString(std::string* dateString)
{
    // In this function, we allow for any date generation, not bound to mapping
    myDatenumEngine->setDateString(dateString);
	return myDatenumEngine->looseDateString(myDisplayFormat);
}

// Free Format Datenum String - Overload 3 //
std::string PriceContainer::getCustomDateString(std::map<double, Price>::iterator it)
{
    // Since they gave us an iter, this is a specific date they want
    if (it != myDataMap.end())
    {
        // Found it
        myDatenumEngine->setDatenum(it->first);
	    return myDatenumEngine->looseDateString(myDisplayFormat);
    }
    else
    {
        // Not found
        myErrorString += "PriceContainer::getCustomDateString 3 - Failed to get datestring: bad iter\n";
        return "";
    }
}

// getHigh - Overload 1 //
float PriceContainer::getHigh(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getHigh 1 - Failed to get high price for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getHigh();
}

// getHigh - Overload 2 //
float PriceContainer::getHigh(std::string* dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getHigh 2 - Failed to get high price for " + 
                *dateStr + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getHigh();
}

// getHigh - Overload 3 //
float PriceContainer::getHigh(std::map<double, Price>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "PriceContainer::getHigh 3 - Failed to get high price for iter.  Bad iter.\n";
        return -1;
    }
    
    // The iter was good return the value
    return it->second.getHigh();
}

// getLow - Overload 1 //
float PriceContainer::getLow(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getLow 1 - Failed to get low price for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getLow();
}

// getLow - Overload 2 //
float PriceContainer::getLow(std::string* dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getLow 2 - Failed to get low price for " 
                + *dateStr + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getLow();
}

// getLow - Overload 3 //
float PriceContainer::getLow(std::map<double, Price>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "PriceContainer::getLow 3 - Failed to get low price for iter.  Bad iter.\n";
        return -1;
    }
    
    // The iter was good return the value
    return it->second.getLow();
}

// getOpen - Overload 1 //
float PriceContainer::getOpen(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getOpen 1 - Failed to get open price for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getOpen();
}

// getOpen - Overload 2 //
float PriceContainer::getOpen(std::string* dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getOpen 2 - Failed to get open price for " 
                + *dateStr + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getOpen();
}

// getOpen - Overload 3 //
float PriceContainer::getOpen(std::map<double, Price>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "PriceContainer::getOpen 3 - Failed to get open price for iter.  Bad iter.\n";
        return -1;
    }
    
    // The iter was good return the value
    return it->second.getOpen();
}

// getClose - Overload 1 //
float PriceContainer::getClose(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getClose 1 - Failed to get close price for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getClose();
}

// getClose - Overload 2 //
float PriceContainer::getClose(std::string* dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getClose 2 - Failed to get close price for " + 
                *dateStr + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getClose();
}

// getClose - Overload 3 //
float PriceContainer::getClose(std::map<double, Price>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "PriceContainer::getClose 3 - Failed to get close price for iter.  Bad iter.\n";
        return -1;
    }
    
    // The iter was good return the value
    return it->second.getClose();
}

// getClose (Adjusted) - Overload 1 //
float PriceContainer::getAdjusted(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getAdjusted 1 - Failed to get adjusted price for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getAdjusted();
}

// getClose (Adjusted) - Overload 2 //
float PriceContainer::getAdjusted(std::string* dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getAdjusted 2 - Failed to get adjusted price for " + 
                *dateStr + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getAdjusted();
}

// getClose (Adjusted) - Overload 3 //
float PriceContainer::getAdjusted(std::map<double, Price>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "PriceContainer::getAdjusted 3 - Failed to get adjusted price for iter.  Bad iter.\n";
        return -1;
    }
    
    // The iter was good return the value
    return it->second.getAdjusted();
}

// getVolume - Overload 1 //
long PriceContainer::getVolume(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getVolume 1 - Failed to get trade volume for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getVolume();
}

// getVolume - Overload 2 //
long PriceContainer::getVolume(std::string* dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getVolume 2 - Failed to get volume for " + 
                *dateStr + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getVolume();
}

// getVolume - Overload 3 //
long PriceContainer::getVolume(std::map<double, Price>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "PriceContainer::getVolume 3 - Failed to get volume for iter.  Bad iter.\n";
        return -1;
    }
    
    // The iter was good return the value
    return it->second.getVolume();
}

// getIncrement - Overload 1 //
char PriceContainer::getIncrement(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getIncrement 1 - Failed to get increment for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getIncrement();
}

// getIncrement - Overload 2 //
char PriceContainer::getIncrement(std::string* dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "PriceContainer::getIncrement 2 - Failed to get increment for " + 
                *dateStr + ".  Not found in container.\n";
        return '-';
    }
      
    // The iter was good return the value
    return lastIter->second.getIncrement();
}

// getIncrement - Overload 3 //
char PriceContainer::getIncrement(std::map<double, Price>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "PriceContainer::getIncrement 3 - Failed to get increment for iter.  Bad iter.\n";
        return '-';
    }
    
    // The iter was good return the value
    return it->second.getIncrement();
}

/********************* Functional *********************************/

// getEpochDouble //
double PriceContainer::getEpochDouble(long seconds)
{
    double returnVal = myDatenumEngine->epochLongToDouble(seconds);
    if(myDatenumEngine->errorFound())
    {
        myErrorString += myDatenumEngine->errorString();
        myErrorString += "PriceContainer::getEpochDouble - Failed to parse Linux epoch to datenum for epoch: ";
        myErrorString += std::to_string(seconds) + "\n";
        myDatenumEngine->clearError();
        return -1;
    }
    return returnVal;
}

// getEpochLong //
long PriceContainer::getEpochLong(double days)
{
    long returnVal = myDatenumEngine->epochDoubleToLong(days);
    if(myDatenumEngine->errorFound())
    {
        myErrorString += myDatenumEngine->errorString();
        myErrorString += "PriceContainer::getEpochLong - Failed to parse datenum to Linux epoch for datenum: ";
        myErrorString += std::to_string(days) + "\n";
        myDatenumEngine->clearError();
        return -1;
    }
    return returnVal;
}

// Add Increment - Overload 1//
bool PriceContainer::add(double dateNumber, float openPrice, float closePrice, 
         float highPrice, float lowPrice, float adjustedPrice,
         int totalVol, char incSize)
{
    // Try to create the price container
    Price priceContainer(dateNumber, openPrice, 
        closePrice, highPrice, lowPrice, adjustedPrice, totalVol, incSize);
    priceContainer.setDateStrings(myDatenumEngine->getDateString(),
                                  myDatenumEngine->looseDateString(myDisplayFormat));
    
    // Check to see if the creation was successful
    if (priceContainer.errorFound())
    {
        myErrorString += priceContainer.errorString();
        myErrorString += "PriceContainer::add 1 - Failed to add price container for datenum: " ;
        myErrorString += std::to_string(dateNumber) + "\n";
        return false;
    }
    
    // Add it to the map and notify requester
    ContainerTemplate::add( dateNumber,priceContainer );
    return true;
}

// Add Increment - Overload 2//
bool PriceContainer::add(std::string* dateStr, float openPrice, float closePrice, 
         float highPrice, float lowPrice, float adjustedPrice,
         int totalVol, char incSize)
{
    // Try to parse the datestring as a datenum, the key of the map
    myDatenumEngine->setDateString(dateStr);
    if(myDatenumEngine->errorFound())
    {
        myErrorString += myDatenumEngine->errorString();
        myErrorString += "PriceContainer::add 2 - Failed to convert date string: " + 
                *dateStr + " to datenum.\n";
        myDatenumEngine->clearError();
        return false;
    }
    
    // Try to create the price container
    Price priceContainer(myDatenumEngine->getDatenum(), openPrice, 
        closePrice, highPrice, lowPrice, adjustedPrice, totalVol, incSize);
    priceContainer.setDateStrings(myDatenumEngine->getDateString(),
                                  myDatenumEngine->looseDateString(myDisplayFormat));
    
    // Check to see if the creation was successful
    if (priceContainer.errorFound())
    {
        myErrorString += priceContainer.errorString();
        myErrorString += "PriceContainer::add 2 - Failed to add price container for date string: " + 
                *dateStr + "\n";
        return false;
    }
    
    // Add it to the map and notify requester
    ContainerTemplate::add( myDatenumEngine->getDatenum(),priceContainer );
    
    return true;
}

// fetchByString //
void PriceContainer::fetchByString(std::string* dateStr)
{
    // If the last object handled was this let's skip the work
    if (dateStr->compare(lastDateStr) == 0 )
        return; 
    
    // Run the datenumEngine to get new dates
    myDatenumEngine->setDateString(dateStr);
    
    // Exit if error
    if (myDatenumEngine->errorFound())
    {
        myErrorString += myDatenumEngine->errorString();
        myErrorString += "PriceContainer::fetchByString - Failed to get datenum for dateString " + 
                *dateStr + "\n";
        myDatenumEngine->clearError();
        lastIter = myDataMap.end();
    }
    else
    {
        // Get the iter
        ContainerTemplate::getIter(myDatenumEngine->getDatenum());
    }

    // Set the string based upon findings
    if (lastIter == myDataMap.end())
        lastDateStr = "";
    else
        lastDateStr = myDatenumEngine->getDateString();
}

// fetchByString //
void PriceContainer::fetchByNumber(double datenum)
{
    // If the last object handled was this let's skip the work
    if (datenum == lastDatenum)
        return;
    
    // Try to find it in my map
    lastIter = ContainerTemplate::getIter(datenum);
    
    // Set the string based upon findings
    if (lastIter == myDataMap.end())
        lastDateStr = "";
    else
        lastDateStr = lastIter->second.getDateStr();
}
