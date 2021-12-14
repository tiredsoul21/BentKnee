/*
 * This Class is used to house price data for a single increment,
 */

#ifndef PRICE_H
#define PRICE_H

#ifndef TYPEDEFINITIONS_H
#include "typeDefinitions.h"
#endif

#ifndef CLASSTEMPLATE_H
#include "ClassTemplate.h"
#endif

#include <string>
#include <vector>

class Price : public ClassTemplate
{
public: // Public Members

public: // Public Methods

	/*********************** CONSTRUCTORS ******************************/

	// Default Constructor //
	/*--------------------------------------------------------------
	 * Description - sets all the data for the container to empty or 
	 *	trash values
     * Input(s):
     *   void
	 * Output(s):
	 *   Price - an object containing pricing data for a single
	 *	increment
	 ---------------------------------------------------------------*/
	Price();

	// Primed Constructor //
	/*--------------------------------------------------------------
	 * Description - sets all the data for the container. Does data
	 *	validation to insure data container is complete
     * Input(s):
     *   void
	 * Output(s):
	 *   Price - an object containing pricing data for a single
	 *	increment
	 ---------------------------------------------------------------*/
	Price(double dateNumber, float openPrice, float closePrice, 
		           float highPrice, float lowPrice, float adjustedPrice,
		           int totalVol, char incSize);

	/*********************** DESTRUCTORS *******************************/

	// Default Destructor //
	~Price();

	/*********************** SETTERS ***********************************/
    
    // set Date Strings//
	/*--------------------------------------------------------------
	 * Description - sets the dateNum value for a time increment
	 * Input(s):
     *   string - the proper & full date time stamp
     *   string - the display date (formatted how you 
     * Output(s):
     *   void
	 ---------------------------------------------------------------*/    
    void setDateStrings(std::string properName, std::string displayName);

	/*********************** GETTERS ***********************************/

	// getDateNum //
	/*--------------------------------------------------------------
	 * Description - sets all the data for the container by recursively
	 * calling the singular sets methods
	 * Output(s):
	 *   double - a value for a date with fixed start point (epoch)
	 *	  format: day.fractionalDay.
	 *	  smallest increment is 1 second ( 1.1574-5)
	 ---------------------------------------------------------------*/
	double getDatenum();

	// getDateStr //
	/*--------------------------------------------------------------
	 * Description - returns the date & time in the form of a string
	 * Input(s):
	 *   void
	 * Output(s):
	 *   string - A date and/or time string containing increments value
	 ---------------------------------------------------------------*/
	std::string getDateStr();

	// getHigh //
	/*--------------------------------------------------------------
	 * Description - returns the high price in the increment
     * Input(s):
     *   void
	 * Output(s):
	 *   float - a value of the highest price during an increment
	 ---------------------------------------------------------------*/
	float getHigh();

	// getLow //
	/*--------------------------------------------------------------
	 * Description - returns the low price in the increment
     * Input(s):
     *   void
	 * Output(s):
	 *   float - a value of the lowest price during an increment
	 ---------------------------------------------------------------*/
	float getLow();

	// getOpen //
	/*--------------------------------------------------------------
	 * Description - returns the opening price of the increment
     * Input(s):
     *   void
	 * Output(s):
	 *   float - a value of the opening price during an increment
	 ---------------------------------------------------------------*/
	float getOpen();

	// getClose //
	/*--------------------------------------------------------------
	* Description - returns the close price of the increment
	* Output(s):
	*   float - a value of the closing price during an increment
	---------------------------------------------------------------*/
	float getClose();

	// getClose (Adjusted) //
	/*--------------------------------------------------------------
	 * Description - returns the adjusted close price of the increment
     * Input(s):
     *   void
	 * Output(s):
	 *   float - a value of the adjusted closing price during an increment
	 ---------------------------------------------------------------*/
	float getAdjusted();

	// getVolume //
	/*--------------------------------------------------------------
	 * Description - returns the total trade volume of the increment
     * Input(s):
     *   void
	 * Output(s):
	 *   int - an value representing total trade volume
	 ---------------------------------------------------------------*/
	int getVolume();

	// getIncrement //
	/*--------------------------------------------------------------
	 * Description - returns the increment type for the data object
     * Input(s):
     *   void
	 * Output(s):
	 *   char - a char in (Y/M/w/d/h/m/s)
	 ---------------------------------------------------------------*/
	char getIncrement();

	// Select Data //
	/*--------------------------------------------------------------
	 * Description - Opens a price container, and retrieves the desired
	 *   price data.
	 * Input(s):
	 *   PriceType - selected data to retrieve
	 * Output(s):
	 *   float - single price datum for the iterator supplied
	 ---------------------------------------------------------------*/
	float selectData(TypeDefinitions::PriceType selected);

private: // Private Members

	// dateString - a string holding the last saved date string
	std::string myDateString;
	std::string myDisplayString;

	// dateNum - a double containing the last entered date for the object
	double myDatenum;

	// low - the lowest price value during an increment
	float myLow;

	// high - the highest price value during an increment
	float myHigh;

	// open - the opening value during an increment (first)
	float myOpen;

	// close - the closing value during an increment (last)
	float myClose;

	// adjusted close - the adjusted closing value during an increment
	float myAdjusted;

	// volume - the total trade volume of an increment
	int myVolume;

	// increment - the increment being represented in this object (Y/M/w/d/h/m/s)
	char myIncrement;

	// initComplete - a boolean value indicating the completeness of the six fields
	bool initComplete;

private: // Private Methods

	/*********************** SETTERS ***********************************/

	// set Date //
	/*--------------------------------------------------------------
	 * Description - sets the dateNum value for a time increment
	 * Input(s):
	 *   double - a value for a date with fixed start point (epoch)
	 *	   format: day.fractionalDay.
	 *	   smallest increment is 1 second ( 1.1574e-5)
     * Output(s):
     *   void
	 ---------------------------------------------------------------*/
    void setDate(double dateNumber);    

	// setHigh //
	/*--------------------------------------------------------------
	 * Description - sets the highest price during a time increment
	 * Input(s):
	 *   float - a value of the highest price during an increment
     * Output(s):
     *   void
	 ---------------------------------------------------------------*/
	void setHigh(float highPrice);

	// setLow //
	/*--------------------------------------------------------------
	 * Description - sets the lowest price of a time increment
	 * Input(s):
	 *   float - a value of the lowest price during an increment
     * Output(s):
     *   void
	 ---------------------------------------------------------------*/
	void setLow(float lowPrice);

	// setOpen //
	/*--------------------------------------------------------------
	 * Description - sets the open price of a time increment
	 * Input(s):
	 *   float - a value of the opening price during an increment
     * Output(s):
     *   void
	 ---------------------------------------------------------------*/
	void setOpen(float openPrice);

	// setClose //
	/*--------------------------------------------------------------
	 * Description - sets the closing price of a time increment
	 * Input(s):
	 *   float - a value of the closing price during an increment
     * Output(s):
     *   void
	---------------------------------------------------------------*/
	void setClose(float closePrice);

	// setAdjusted //
	/*--------------------------------------------------------------
	 * Description - sets the adjusted closing price of a time increment
	 * Input(s):
	 *   float - a value of the closing price during an increment
     * Output(s):
     *   void
	 ---------------------------------------------------------------*/
	void setAdjusted(float adjustedPrice);

	// setVolume //
	/*--------------------------------------------------------------
	 * Description - sets the total trade volume during a time increment
	 * Input(s):
	 *   int - a value of total trade volume
     * Output(s):
     *   void
	 ---------------------------------------------------------------*/
	void setVolume(int volume);

	// setIncrement //
	/*--------------------------------------------------------------
	 * Description - stores the value of the increment type for the object
	 * Input(s):
	 *   char - an increment in (Y/M/w/d/h/m/s)
     * Output(s):
     *   void
	 ---------------------------------------------------------------*/
	void setIncrement(char increment);

	/*********************** Validation *********************************/

	// goodDateNum //
	/*--------------------------------------------------------------
	 * Description - checks that the dateNumber is valid.  
	 *	Primarily, this checks for negative values
     * Input(s):
     * double - a value for a date with fixed start point (epoch)
	 *	 format: day.fractionalDay.
	 *	 smallest increment is 1 second ( 1.1574e-5)
	 * Output(s): 
	 *   bool - a true of false to the statement, "This 'thing' is valid"
	 ---------------------------------------------------------------*/
	bool goodDatenum(double dateNumber);

	// goodPrice //
	/*--------------------------------------------------------------
	 * Description - checks that the prive value given is valid.
	 *	Primarily, this checks for negative values
     * Input(s):
     *   float - a value of the price to validate
	 * Output(s):
	 *   bool - a true of false to the statement, "This 'thing' is valid"
     ---------------------------------------------------------------*/
	bool goodPrice(float price);

	// goodVolume //
	/*--------------------------------------------------------------
	 * Description - checks that the volume is valid.  Primarily checks
	 *	that the value is positive
	 * Input(s):
     *   int - a value of total trade volume
	 * Output(s):
	 *   bool - a true of false to the statement, "This 'thing' is valid"
	 ---------------------------------------------------------------*/
	bool goodVolume(int volume);

	// goodIncrement //
	/*--------------------------------------------------------------
	 * Description - checks that the Increment given is valid.
	 *	Primarily, this checks is input in the set (Y/M/w/d/h/m/s)
     * Input(s):
     *   char - an increment in (Y/M/w/d/h/m/s)
	 * Output(s):
	 *   bool - a true of false to the statement, "This 'thing' is valid"
	 ---------------------------------------------------------------*/
	bool goodIncrement(char increment);

	// goodObject //
	/*--------------------------------------------------------------
	 * Description - checks that the object is wholly valid.
     * Inputs(s):
     *   void
	 * Output(s):
	 *   bool - a true of false to the statement, "This 'thing' is valid"
	 ---------------------------------------------------------------*/
	bool goodObject();

};

#endif