#include <iostream>
#include "HistoryContainer.h"

/*********************** CONSTRUCTORS ******************************/

HistoryContainer::HistoryContainer()
{ 
    // Default Input Format
    myInputFormat = "MM/DD/YYYY hh:mm:ss";
    
    // Default Display Format
    myInputFormat = "YYYY-MM-DD";
    
    // Initialize the datenum engine
    myDatenumEngine = new Datenum();
    
    // Initialize these to 0
    lastIter = myDataMap.begin();
    lastDatenum = 0;
    lastDateStr = "01/01/1970 00:00:00";
}

/*********************** DESTRUCTORS *******************************/

// Default Constructor //
HistoryContainer::~HistoryContainer() { }

/*********************** SETTERS ***********************************/

// setDateFormat
void HistoryContainer::setInputDateFormat(std::string dateFormat)
{
    // If the date format is accepted by the engine, its a good date
    if( myDatenumEngine->setDateFormat(dateFormat) )
    {
        myInputFormat = dateFormat;
    }
    else
    {
        myErrorString += myDatenumEngine->errorString();
        myErrorString += "Error: Failed to set dateFormat, didn't pass DatenumEngine validation\n";
        myDatenumEngine->clearError();
    }
}

// setDateFormat
void HistoryContainer::setDisplayDateFormat(std::string dateFormat)
{
    // We don't really care if the user provides us garbage, the ambiguous 
    // assignment would just give them garbage back
    myDisplayFormat = dateFormat;
}

/*********************** GETTERS ***********************************/

// getIter - Overload 1 //
std::map<double, PriceContainer>::iterator HistoryContainer::getIter(std::string dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
        myErrorString += "Failed to get iter for " + dateStr + ".  Not found in container.\n";

    // This will ether be last or some other iter, always good
    return lastIter;
}

// getIter - Overload 2//
std::map<double, PriceContainer>::iterator HistoryContainer::getIter(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get iter for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
    }
        
    // This will ether be last or some other iter, always good
    return lastIter;
}

// getBeginIter //
std::map<double, PriceContainer>::iterator HistoryContainer::getBeginIter()
{
    return myDataMap.begin();
}

// getDateNum - Overload 1 //
double HistoryContainer::getDatenum(std::string dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        myErrorString += "Failed to get datenum for " + dateStr + ".  Not found in container.\n";
        return -1;
    }

    // Return the found datenum
    return lastDatenum;
}

// getDateNum - Overload 2 //
double HistoryContainer::getDatenum(std::map<double, PriceContainer>::iterator it)
{
    // This is easy, they already gave us an iter, just use it!
    if (it != myDataMap.end())
    {
        lastDatenum = it->first;
        lastDateStr = it->second.getDateStr();
        lastIter = it;
        return lastDatenum;
    }
    
    return -1;
}

// getDateStr - Overload 1//
std::string HistoryContainer::getDateStr(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get date string for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return "";
    }
      
    // This will ether be last or some other iter, always good
    return lastDateStr;
}

// getDateStr - Overload 2//
std::string HistoryContainer::getDateStr(std::map<double, PriceContainer>::iterator it)
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
    
    return "";
}

// Free Format Datenum String - Overload 1 //
std::string HistoryContainer::getCustomDateString(double dateNum)
{
    // In this function, we allow for any date generation, not bound to mapping
    myDatenumEngine->setDatenum(dateNum);
	return myDatenumEngine->looseDateString(myDisplayFormat);
}

// Free Format Datenum String - Overload 2 //
std::string HistoryContainer::getCustomDateString(std::string dateString)
{
    // In this function, we allow for any date generation, not bound to mapping
    myDatenumEngine->setDateString(dateString);
	return myDatenumEngine->looseDateString(myDisplayFormat);
}

// Free Format Datenum String - Overload 3 //
std::string HistoryContainer::getCustomDateString(std::map<double, PriceContainer>::iterator it)
{
    // Since they gave us an iter, this is a specific date they want
    if (it != myDataMap.end())
    {
        // Found it
        myDatenumEngine->setDatenum(it->first);
	    return myDatenumEngine->looseDateString(myDisplayFormat);
    }
    
    return "";
}

// getHigh - Overload 1 //
float HistoryContainer::getHigh(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get high price for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getHigh();
}

// getHigh - Overload 2 //
float HistoryContainer::getHigh(std::string dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get high price for " + dateStr + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getHigh();
}

// getHigh - Overload 3 //
float HistoryContainer::getHigh(std::map<double, PriceContainer>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "Failed to get high price for iter.  Bad iter.\n";
        return -1;
    }
    
    // The iter was good return the value
    return it->second.getHigh();
}

// getLow - Overload 1 //
float HistoryContainer::getLow(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get low price for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getLow();
}

// getLow - Overload 2 //
float HistoryContainer::getLow(std::string dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get low price for " + dateStr + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getLow();
}

// getLow - Overload 3 //
float HistoryContainer::getLow(std::map<double, PriceContainer>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "Failed to get low price for iter.  Bad iter.\n";
        return -1;
    }
    
    // The iter was good return the value
    return it->second.getLow();
}

// getOpen - Overload 1 //
float HistoryContainer::getOpen(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get open price for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getOpen();
}

// getOpen - Overload 2 //
float HistoryContainer::getOpen(std::string dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get open price for " + dateStr + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getOpen();
}

// getOpen - Overload 3 //
float HistoryContainer::getOpen(std::map<double, PriceContainer>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "Failed to get open price for iter.  Bad iter.\n";
        return -1;
    }
    
    // The iter was good return the value
    return it->second.getOpen();
}

// getClose - Overload 1 //
float HistoryContainer::getClose(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get close price for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getClose();
}

// getClose - Overload 2 //
float HistoryContainer::getClose(std::string dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get close price for " + dateStr + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getClose();
}

// getClose - Overload 3 //
float HistoryContainer::getClose(std::map<double, PriceContainer>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "Failed to get close price for iter.  Bad iter.\n";
        return -1;
    }
    
    // The iter was good return the value
    return it->second.getClose();
}

// getClose (Adjusted) - Overload 1 //
float HistoryContainer::getAdjusted(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get adjusted price for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getAdjusted();
}

// getClose (Adjusted) - Overload 2 //
float HistoryContainer::getAdjusted(std::string dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get adjusted price for " + dateStr + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getAdjusted();
}

// getClose (Adjusted) - Overload 3 //
float HistoryContainer::getAdjusted(std::map<double, PriceContainer>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "Failed to get adjusted price for iter.  Bad iter.\n";
        return -1;
    }
    
    // The iter was good return the value
    return it->second.getAdjusted();
}

// getVolume - Overload 1 //
int HistoryContainer::getVolume(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get trade volume for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getVolume();
}

// getVolume - Overload 2 //
int HistoryContainer::getVolume(std::string dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get volume for " + dateStr + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getVolume();
}

// getVolume - Overload 3 //
int HistoryContainer::getVolume(std::map<double, PriceContainer>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "Failed to get volume for iter.  Bad iter.\n";
        return -1;
    }
    
    // The iter was good return the value
    return it->second.getVolume();
}

// getIncrement - Overload 1 //
char HistoryContainer::getIncrement(double datenum)
{
    // Lookup by date string if it exists in map
    fetchByNumber(datenum);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get increment for datenum: ";
        myErrorString += std::to_string(datenum) + ".  Not found in container.\n";
        return -1;
    }
      
    // The iter was good return the value
    return lastIter->second.getIncrement();
}

// getIncrement - Overload 2 //
char HistoryContainer::getIncrement(std::string dateStr)
{
    // Lookup by date string if it exists in map
    fetchByString(dateStr);
    
    // Didn't find the requested data by key
    if (lastIter == myDataMap.end())
    {
        // Not found
        myErrorString += "Failed to get increment for " + dateStr + ".  Not found in container.\n";
        return '-';
    }
      
    // The iter was good return the value
    return lastIter->second.getIncrement();
}

// getIncrement - Overload 3 //
char HistoryContainer::getIncrement(std::map<double, PriceContainer>::iterator it)
{
    if (it ==  myDataMap.end())
    {
        // If iter was bad...
        myErrorString += "Failed to get increment for iter.  Bad iter.\n";
        return '-';
    }
    
    // The iter was good return the value
    return it->second.getIncrement();
}

/********************* Functional *********************************/

// getEpochDouble //
double HistoryContainer::getEpochDouble(long seconds)
{
    double returnVal = myDatenumEngine->epochLongToDouble(seconds);
    if(myDatenumEngine->errorFound())
    {
        myErrorString += myDatenumEngine->errorString();
        myErrorString += "Failed to parse Linux epoch to datenum for epoch: ";
        myErrorString += std::to_string(seconds);
        myErrorString += "\n";
        myDatenumEngine->clearError();
        return -1;
    }
    return returnVal;
}

// getEpochLong //
long HistoryContainer::getEpochLong(double days)
{
    long returnVal = myDatenumEngine->epochDoubleToLong(days);
    if(myDatenumEngine->errorFound())
    {
        myErrorString += myDatenumEngine->errorString();
        myErrorString += "Failed to parse datenum to Linux epoch for datenum: ";
        myErrorString += std::to_string(days);
        myErrorString += "\n";
        myDatenumEngine->clearError();
        return -1;
    }
    return returnVal;
}

// Add Increment //
bool HistoryContainer::add(double dateNumber, float openPrice, float closePrice, 
         float highPrice, float lowPrice, float adjustedPrice,
         int totalVol, char incSize)
{
    // Try to create the price container
    PriceContainer priceContainer(dateNumber, openPrice, 
        closePrice, highPrice, lowPrice, adjustedPrice, totalVol, incSize);
    priceContainer.setDateStrings(myDatenumEngine->getDateString(),
                                  myDatenumEngine->looseDateString(myDisplayFormat));
    
    // Check to see if the creation was successful
    if (priceContainer.errorFound())
    {
        myErrorString += priceContainer.errorString();
        myErrorString += "Failed to add price container for datenum: " ;
        myErrorString += std::to_string(dateNumber);
        myErrorString += "\n";
        priceContainer.clearError();
        return false;
    }
    
    // Add it to the map and notify requester
    myDataMap.insert( std::pair<double,PriceContainer>(dateNumber,priceContainer) );
    return true;
}

// Add Increment //
bool HistoryContainer::add(std::string dateString, float openPrice, float closePrice, 
         float highPrice, float lowPrice, float adjustedPrice,
         int totalVol, char incSize)
{
    // Try to parse the datestring as a datenum, the key of the map
    myDatenumEngine->setDateString(dateString);
    if(myDatenumEngine->errorFound())
    {
        myErrorString += myDatenumEngine->errorString();
        myErrorString += "Failed to convert date string: " + dateString + " to datenum.\n";
        myDatenumEngine->clearError();
        return false;
    }
    
    // Try to create the price container
    PriceContainer priceContainer(myDatenumEngine->getDatenum(), openPrice, 
        closePrice, highPrice, lowPrice, adjustedPrice, totalVol, incSize);
    priceContainer.setDateStrings(myDatenumEngine->getDateString(),
                                  myDatenumEngine->looseDateString(myDisplayFormat));
    
    // Check to see if the creation was successful
    if (priceContainer.errorFound())
    {
        myErrorString += priceContainer.errorString();
        myErrorString += "Failed to add price container for date string: " + dateString + "\n";
        priceContainer.clearError();
        return false;
    }
    
    // Add it to the map and notify requester
    myDataMap.insert( std::pair<double,PriceContainer>(myDatenumEngine->getDatenum(),
                                                       priceContainer) );
    return true;
}

// fetchByString //
void HistoryContainer::fetchByString(std::string dateStr)
{
    // If the last object handled was this let's skip the work
    if (lastDateStr.compare(dateStr) == 0 )
        return; 
    
    // Run the datenumEngine to get new dates
    myDatenumEngine->setDateString(dateStr);
    std::cout << "1 " << dateStr << " 1\n";
    
    // Exit if error
    if (myDatenumEngine->errorFound())
    {
        myErrorString += myDatenumEngine->errorString();
        myErrorString += "Failed to get datenum for dateString " + dateStr + "\n";
        myDatenumEngine->clearError();
        lastIter = myDataMap.end();
    }
    else
    {
        // Get the iter
        lastIter = myDataMap.find(myDatenumEngine->getDatenum());
    }
    
    if (lastIter == myDataMap.end())
    {
        // Not found!
        lastDatenum = -1;
        lastDateStr = "";
    }
    else
    {
        // Set my stored data markers to this new find
        lastDatenum = myDatenumEngine->getDatenum();
        lastDateStr = myDatenumEngine->getDateString();
    }
}

// fetchByString //
void HistoryContainer::fetchByNumber(double datenum)
{
    // If the last object handled was this let's skip the work
    if (datenum == lastDatenum)
        return;
    
    // Try to find it in my map
    lastIter = myDataMap.find(datenum);
    
    if (lastIter == myDataMap.end())
    {
        // Not found!
        lastDatenum = -1;
        lastDateStr = "";
    }
    else
    {
        // Found it.  Set my stored data markers to this new find
        lastDatenum = lastIter->second.getDatenum();
        lastDateStr = lastIter->second.getDateStr();
    }
}
