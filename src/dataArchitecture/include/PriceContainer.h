/*
 * This Class is used to house a series of price data.  The form is given
 * by a mapping, where the datenum forms the key, to the mapping for 
 * Prices
 */

#ifndef PRICECONTAINER_H
#define PRICECONTAINER_H

#ifndef DATEENGINE_H
#include "DateEngine.h"
#endif

#ifndef PRICE_H
#include "Price.h"
#endif

#ifndef CONTAINERTEMPLATE_H
#include "ContainerTemplate.h"
#endif

#ifndef CLASSTEMPLATE_H
#include "ClassTemplate.h"
#endif

#include <string>

#include <map>
#include <iterator>

class PriceContainer : public ContainerTemplate<Price>
{
public: // Public Members

public: // Public Methods

	/*********************** CONSTRUCTORS ******************************/

	// Default Constructor //
	/*--------------------------------------------------------------
	 * Description - Empty History 
     * Input(s):
     *   void
	 * Output(s):
	 *   PriceContainer - an object containing pricing data for a 
     *   range of increments
	 ---------------------------------------------------------------*/
	PriceContainer();

	/*********************** DESTRUCTORS *******************************/

	// Default Destructor //
	~PriceContainer();

	/*********************** SETTERS ***********************************/
    
	// set Input Date Format //
    /*--------------------------------------------------------------
     * Description - sets the date format for the data to be added
     * Input(s):
     *   string - a format that contains the format the output string
	 *		   that is desired.  Use (Y / M / D / h / m / s)
     --------------------------------------------------------------*/
    void setInputDateFormat(std::string* dateFormat);

    // set Display Date Format //
    /*--------------------------------------------------------------
     * Description - sets the date format for the display date for
     *   all the data to be added
     * Input(s):
     *   string - a format that contains the format the output string
	 *		   that is desired.  Use (Y / M / D / h / m / s)
     --------------------------------------------------------------*/
    void setDisplayDateFormat(std::string* dateFormat);
    
	/*********************** GETTERS ***********************************/
    
	// Get Iterator //
	/*--------------------------------------------------------------
	 * Description - get the iterator for a lookup value in History
     *   from a str / double
	 * Input(s) - Overload 1:
	 *   double - a datenum for the increment
     * Input(s) - Overload 2:
     *   string - the date string associated with the increment.  This
     *     should be of the same format used to program the Container
	 * Output(s):
	 *   map<double, Price>::iterator - iterator for the data 
     *   point if there is a match
	 ---------------------------------------------------------------*/
	std::map<double, Price>::iterator getIter(std::string* dateStr);
    std::map<double, Price>::iterator getIter(double datenum);
    
	// Get Date Number //
	/*--------------------------------------------------------------
	 * Description - gets the datenum from a reference str / iter
     * Input(s) - Overload 1:
     *   string - the date string associated with the increment.  This
     *     should be of the same format used to program the Container
     * Input(s) - Overload 2:
     *   map<double, Price>::iterator - iterator for the mapping
	 * Output(s):
	 *   double - a value for a date with fixed start point (epoch)
	 *	  format: day.fractionalDay.
	 *	  smallest increment is 1 second ( 1.1574-5)
	 ---------------------------------------------------------------*/
	double getDatenum(std::string* date);
    double getDatenum(std::map<double, Price>::iterator it);

	// Get Date String //
	/*--------------------------------------------------------------
	 * Description - returns the date & time in the form of a string
	 * Input(s) - Overload 1:
	 *   double - a datenum for the increment
     * Input(s) - Overload 2:
     *   map<double, Price>::iterator - iterator for the mapping
	 * Output(s):
	 *   string - A date and/or time string containing increments value
	 ---------------------------------------------------------------*/
	std::string getDateStr(double date);
	std::string getDateStr(std::map<double, Price>::iterator it);

	// Free Format Datenum String //
	/*--------------------------------------------------------------
	 * Description - Returns a loose interpretation of date string
	 *   to the user.  Does not check formatting, does not sets internals,
	 *   strictly a get function that populates what it can.
	 * Input(s) - Overload 1:
	 *   double - a datenum for the increment
     * Input(s) - Overload 2:
     *   string - the date string associated with the increment.  This
     *     should be of the same format used to program the Container
     * Input(s) - Overload 3:
     *   map<double, Price>::iterator - iterator for the mapping
	 * Output(s):
	 *   string - representing the time frame of an increment
	 ---------------------------------------------------------------*/
	std::string getCustomDateString(double dateNum);
	std::string getCustomDateString(std::string* dateString);
    std::string getCustomDateString(std::map<double, Price>::iterator it);

	// Get High //
	/*--------------------------------------------------------------
	 * Description - returns the high price in the increment
	 * Input(s) - Overload 1:
	 *   double - a datenum for the increment
     * Input(s) - Overload 2:
     *   string - the date string associated with the increment.  This
     *     should be of the same format used to program the Container
     * Input(s) - Overload 3:
     *   map<double, Price>::iterator - iterator for the mapping
	 * Output(s):
	 *   float - a value of the highest price during an increment
	 ---------------------------------------------------------------*/
	float getHigh(double date);
	float getHigh(std::string* dateString);
	float getHigh(std::map<double, Price>::iterator it);

	// Get Low //
	/*--------------------------------------------------------------
	 * Description - returns the low price in the increment
	 * Input(s) - Overload 1:
	 *   double - a datenum for the increment
     * Input(s) - Overload 2:
     *   string - the date string associated with the increment.  This
     *     should be of the same format used to program the Container
     * Input(s) - Overload 3:
     *   map<double, Price>::iterator - iterator for the mapping
	 * Output(s):
	 *   float - a value of the lowest price during an increment
	 ---------------------------------------------------------------*/
	float getLow(double date);
	float getLow(std::string* dateString);
	float getLow(std::map<double, Price>::iterator it);

	// Get Open //
	/*--------------------------------------------------------------
	 * Description - returns the opening price of the increment
	 * Input(s) - Overload 1:
	 *   double - a datenum for the increment
     * Input(s) - Overload 2:
     *   string - the date string associated with the increment.  This
     *     should be of the same format used to program the Container
     * Input(s) - Overload 3:
     *   map<double, Price>::iterator - iterator for the mapping
	 * Output(s):
	 *   float - a value of the opening price during an increment
	 ---------------------------------------------------------------*/
	float getOpen(double date);
	float getOpen(std::string* dateString);
	float getOpen(std::map<double, Price>::iterator it);

	// Get Close //
	/*--------------------------------------------------------------
	 * Description - returns the close price of the increment
	 * Input(s) - Overload 1:
	 *   double - a datenum for the increment
     * Input(s) - Overload 2:
     *   string - the date string associated with the increment.  This
     *     should be of the same format used to program the Container
     * Input(s) - Overload 3:
     *   map<double, Price>::iterator - iterator for the mapping
	* Output(s):
	*   float - a value of the closing price during an increment
	---------------------------------------------------------------*/
	float getClose(double date);
	float getClose(std::string* dateString);
	float getClose(std::map<double, Price>::iterator it);

	// Get Close (Adjusted) //
	/*--------------------------------------------------------------
	 * Description - returns the adjusted close price of the increment
	 * Input(s) - Overload 1:
	 *   double - a datenum for the increment
     * Input(s) - Overload 2:
     *   string - the date string associated with the increment.  This
     *     should be of the same format used to program the Container
     * Input(s) - Overload 3:
     *   map<double, Price>::iterator - iterator for the mapping
	 * Output(s):
	 *   float - a value of the adjusted closing price during an increment
	 ---------------------------------------------------------------*/
	float getAdjusted(double date);
	float getAdjusted(std::string* dateString);
	float getAdjusted(std::map<double, Price>::iterator it);

	// Get Volume //
	/*--------------------------------------------------------------
	 * Description - returns the total trade volume of the increment
	 * Input(s) - Overload 1:
	 *   double - a datenum for the increment
     * Input(s) - Overload 2:
     *   string - the date string associated with the increment.  This
     *     should be of the same format used to program the Container
     * Input(s) - Overload 3:
     *   map<double, Price>::iterator - iterator for the mapping
	 * Output(s):
	 *   int - an value representing total trade volume
	 ---------------------------------------------------------------*/
	int getVolume(double date);
	int getVolume(std::string* dateString);
	int getVolume(std::map<double, Price>::iterator it);

	// Get Increment //
	/*--------------------------------------------------------------
	 * Description - returns the increment type for the data object
	 * Input(s) - Overload 1:
	 *   double - a datenum for the increment
     * Input(s) - Overload 2:
     *   string - the date string associated with the increment.  This
     *     should be of the same format used to program the Container
     * Input(s) - Overload 3:
     *   map<double, Price>::iterator - iterator for the mapping
	 * Output(s):
	 *   char - a char in (Y/M/w/d/h/m/s)
	 ---------------------------------------------------------------*/
	char getIncrement(double date);
	char getIncrement(std::string* dateString);
	char getIncrement(std::map<double, Price>::iterator it);

    /********************* Functional *********************************/
    
	// Get Epoch Double //
	/*--------------------------------------------------------------
	 * Description - Takes a standard epoch second and converts it to
	 *   locally used datenum format <day>.<partialday>
	 * Input(s):
	 *   long - a value representing seconds since epoch
	 * Output(s):
	 *   double - represents current day since epoch
	 ---------------------------------------------------------------*/
	double getEpochDouble(long seconds);

	// Get Epoch Long //
	/*--------------------------------------------------------------
	 * Description - Takes a locally used datenum format <day>.<partialday>
	 *   and converts it to a standard epoch time
	 * Input(s):
	 *   double - represents current day since epoch
	 * Output(s):
	 *   long - a value representing seconds since epoch
	 ---------------------------------------------------------------*/
	long getEpochLong(double days);
    
    // Add Increment //
	/*--------------------------------------------------------------
	 * Description - sets all the data for a price container and adds
     *   the increment to the stack.
     * Input(s):
     *   double - dateNumber associated with the increment
     *   float - the open price for the increment
     *   float - the close price for the increment
     *   float - the high price for the increment
     *   float - the low price for the increment
     *   float - the adjusted price for the increment
     *   int - the total volume for the increment
     *   char - the increment size (Y/M/w/d/h/m/s)
	 * Output(s):
	 *   bool - a success bool for having added, true = added
	 *	increment
	 ---------------------------------------------------------------*/
	bool add(double dateNumber, float openPrice, float closePrice, 
		     float highPrice, float lowPrice, float adjustedPrice,
		     int totalVol, char incSize);
   
    // Add Increment //
	/*--------------------------------------------------------------
	 * Description - sets all the data for a price container and adds
     *   the increment to the stack.
     * Input(s):
     *   string - a date string associated with the increment
     *   float - the open price for the increment
     *   float - the close price for the increment
     *   float - the high price for the increment
     *   float - the low price for the increment
     *   float - the adjusted price for the increment
     *   int - the total volume for the increment
     *   char - the increment size (Y/M/w/d/h/m/s)
	 * Output(s):
	 *   bool - a success bool for having added, true = added
	 *	increment
	 ---------------------------------------------------------------*/
	bool add(std::string* dateString, float openPrice, float closePrice, 
		     float highPrice, float lowPrice, float adjustedPrice,
		     int totalVol, char incSize);
    
private: // Private Members
    
    // A Date Engine, used for the manipulate of dates
    DateEngine* myDatenumEngine;
    
    // String format of input/output string
    std::string myInputFormat;
    std::string myDisplayFormat;
    
    // Last looked up items, this is to save time and resources
    std::string lastDateStr;
    
private: // Private methods
    
    // Fetch By String //
	/*--------------------------------------------------------------
	 * Description - looks up the iter of the price unit associated 
     *   with the date string provided.  If nothing exists, then stores
     *   the end iter in lastIter.
     * Input(s):
     *   string - the date string associated with the increment.  This
     *     should be of the same format used to program the Container
	 * Output(s):
	 *   void
	 ---------------------------------------------------------------*/
    void fetchByString(std::string* dateStr);
    
    // Fetch By String //
	/*--------------------------------------------------------------
	 * Description - looks up the iter of the price unit associated 
     *   with the date number provided.  If nothing exists, then stores
     *   the end iter in lastIter.
	 * Input(s):
	 *   double - a datenum for the increment
	 * Output(s):
	 *   void
	 ---------------------------------------------------------------*/
    void fetchByNumber(double datenum);
};

#endif