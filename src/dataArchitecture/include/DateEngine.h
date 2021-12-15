/*
 * This class is intended to be a utility class.  Typical 
 * utility would be the the conversion and translation of datenums
 * and strings with multiple overloaded functionality.  This is 
 * owned by other classes, and as used as an engine.
 */

#ifndef DATEENGINE_H
#define DATEENGINE_H

#ifndef CLASSTEMPLATE_H
#include "ClassTemplate.h"
#endif

#include <string>
#include <map>

class DateEngine : public ClassTemplate
{
public: // Public Members

public: // Public Methods

    /*********************** CONSTRUCTORS ******************************/

    // Default Constructor //
    DateEngine();

    // Date String Constructor //
    DateEngine(std::string* dateString, std::string* dateFormat);

    // Date double Constructor //
    DateEngine(double datenum);

    /*********************** DESTRUCTORS *******************************/

    // Default Destructor //
    ~DateEngine();

    /************************** SETTERS ********************************/

    // Set Date Format //
    /*--------------------------------------------------------------
     * Description - Used to set the date string format used to set
     * the internal dates time for conversion or used to set the
     * desired output.  Must contain largest increments. For example, if using 
     * minute resolution, must have Y/M/D/h also, seconds is optional
     * Input(s):
     *   string - representation of the desired formation.
     *     (Y / M / D / h / m / s / '/' / :)
     * Output(s):
     *   Void
     ---------------------------------------------------------------*/
    bool setDateFormat(std::string* dateFormat);

    // Set Datenum //
    /*--------------------------------------------------------------
     * Description - Converts a datenum in the setting of
     * day.partialday.  values strictly less than day are rounded down.
     * (IE - 24.999999 != 25, but next second down).  Smallest accuracy
     * is seconds.  This value will overwrite values entered by 
     * setDateString.  This is the number of days since 1970/01/01.
     * day - integer value of decimal
     *   hours  - 2.16667e-2
     *   minute - 6.94444e-4
     *   second - 1.15741e-5
     * Input(s):
     *   double - representing the day and fractional day in decimal
     * Output(s):
     *   bool - return true is date format was accepted
     ---------------------------------------------------------------*/
    void setDatenum(double datenum);

    // Set Date String //
    /*--------------------------------------------------------------
     * Description - Converts a date string into the setting of
     * day.partialday.  Smallest accuracy is seconds.  This value 
     * will overwrite values entered by setDatenum.
     * day - integer value of decimal
     *   hours  - 2.16667e-2
     *   minute - 6.94444e-4
     *   second - 1.15741e-5
     * Input(s):
     *   string - representing the time frame of an increment
     * Output(s):
     *   Void
     ---------------------------------------------------------------*/
    void setDateString(std::string* dateString);

    /************************** GETTERS ********************************/

    // Get Date Format //
    /*--------------------------------------------------------------
     * Description - Used to get the date string format used to set
     * the internal dates time for conversion or used to set the
     * desired output.
     * Input(s):
     *   Void
     * Output(s):
     *   string - representation of the desired formation.
     *     (Y / M / D / h / m / s / '/' / :)
     ---------------------------------------------------------------*/
    std::string getDateFormat();

    // Get Datenum //
    /*--------------------------------------------------------------
     * Description - Get the datenum in the setting of
     * day.partialday. Smallest accuracy is seconds. This is the 
     * number of days since 1970/01/01.
     * day - integer value of decimal
     *   hours  - 2.16667e-2
     *   minute - 6.94444e-4
     *   second - 1.15741e-5
     * Input(s):
     *   Void
     * Output(s):
     *   double - representing the day and fractional day in decimal
     ---------------------------------------------------------------*/
    double getDatenum();

    // Get Date String //
    /*--------------------------------------------------------------
     * Description - Gets the date string into the setting of
     * the provide format.  Smallest accuracy is seconds.
     * day - integer value of decimal
     *   hours  - 2.16667e-2
     *   minute - 6.94444e-4
     *   second - 1.15741e-5
     * Input(s):
     *   Void
     * Output(s):
     *   string - representing the time frame of an increment
     ---------------------------------------------------------------*/
    std::string getDateString();

    // Get TimeUnit //
    /*--------------------------------------------------------------
     * Description - Get unit of time associated with the provided 
     * time.
     * Input(s):
     *   Void
     * Output(s):
     *   int - representing the time frame of an increment
     ---------------------------------------------------------------*/
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMinute();
    int getSecond();

    // Get Epoch TimeUnit //
    /*--------------------------------------------------------------
     * Description - Get epoch time associated with the provided
     * time.
     * Input(s):
     *   Void
     * Output(s):
     *   long - representing the number of time units since 1970/01/01
    ---------------------------------------------------------------*/
    long getEpochYears();
    long getEpochMonths();
    long getEpochWeeks();
    long getEpochDays();
    long getEpochHours();
    long getEpochMinutes();
    long getEpochSeconds();
    
    /************************ FUNCTIONAL ******************************/
    
    // Free Format Date String //
    /*--------------------------------------------------------------
     * Description - Returns a rigid interpretation of date string
     * to the user.  Does not check formatting, not sets internals,
     * strictly a set function that populates what it can.
     * Input(s):
     *   string - expected format the for the desired output
     * Output(s):
     *   string - representing the time frame of an increment
     ---------------------------------------------------------------*/
    std::string looseDateString(std::string givenFormat);
    
    // Epoch Long to Double //
    /*--------------------------------------------------------------
     * Description - Takes a standard epoch second and converts it to
     *   locally used datenum format <day>.<partialday>
     * Input(s):
     *   Long - a value representing seconds since epoch
     * Output(s):
     *   Double - represents current day since epoch
     ---------------------------------------------------------------*/
    double epochLongToDouble(long seconds);

    // Epoch Double to Long //
    /*--------------------------------------------------------------
     * Description - Takes a locally used datenum format <day>.<partialday>
     *   and converts it to a standard epoch time
     * Input(s):
     *   double - represents current day since epoch
     * Output(s):
     *   long - a value representing seconds since epoch
     ---------------------------------------------------------------*/
    long epochDoubleToLong(double day);

    // Get Leap Seconds Since //
    /*--------------------------------------------------------------
     * Description - Takes a month and year and returns elapsed leap seconds
     * Input(s):
     *   int - year for current epoch
     *   int - month for current epoch
     * Output(s):
     *   int - integer value for leap seconds occured since epoch
     ---------------------------------------------------------------*/
    int getLeapSecondsSince(int year, int month);

    /************************ FUNCTIONAL *******************************/

private: // Private Members

    // String representing input/output string date
    std::string myDateStr;

    // String format of input/output string
    std::string myFormat;

    // My conversion or user provided date number
    double myDatenum;

    // A duplicate datenum, stored internally to determine if the
    //   change was a string of double change
    bool myFormatChange;

    // An integer to store the size of the year in format
    int myYearSize;

    // User provided data broken up into units
    int myYear;
    int myMonth;
    int myDay;
    int myHour;
    int myMinute;
    int mySecond;

    // Generated data from user provided double / string epoch times
    long myEpochYears;
    long myEpochMonths;
    // Weeks are offset by 3 days, to alight with first Sunday in 1970
    // Days prior are 0th weeks, and Sunday the 4th starts week 1
    long myEpochWeeks;
    long myEpochDays;
    long myEpochHours;
    long myEpochMinutes;
    long myEpochSeconds;

    std::map<int, int> myLeapSecondMap = std::map<int, int>({ 
        { 1970,0 }, { 1971,0 }, { 1972,3 }, { 1973,1 }, { 1974,1 },
        { 1975,1 }, { 1976,1 }, { 1977,1 }, { 1978,1 }, { 1979,1 },
        { 1980,0 }, { 1981,2 }, { 1982,2 }, { 1983,2 }, { 1984,0 },
        { 1985,2 }, { 1986,0 }, { 1987,1 }, { 1988,0 }, { 1989,1 },
        { 1990,1 }, { 1991,0 }, { 1992,2 }, { 1993,2 }, { 1994,2 },
        { 1995,1 }, { 1996,0 }, { 1997,2 }, { 1998,1 }, { 1999,0 },
        { 2000,0 }, { 2001,0 }, { 2002,0 }, { 2003,0 }, { 2004,0 },
        { 2005,1 }, { 2006,0 }, { 2007,0 }, { 2008,1 }, { 2009,0 },
        { 2010,0 }, { 2011,0 }, { 2012,2 }, { 2013,0 }, { 2014,0 },
        { 2015,2 }, { 2016,1 }, { 2017,0 }, { 2018,0 }, { 2019,0 },
        { 2020,0 }, { 2021,0 }, { 2022,0 }, { 2023,0 }, { 2024,0 }, });
    

    // A bool expression indicating tradability of the time
    bool tradeDay;
    bool tradeTime;

private: // Private Methods

    // Generate My String //
    /*--------------------------------------------------------------
     * Description - Does the physical construction of the string
     *    here, the format is arbitrary and assumed correct
     * Inputs(s):
     *   string - represents the desired format
     * Output(s):
     *   Void
     ---------------------------------------------------------------*/
    void generateMyString(std::string givenFormat, std::string &outputString);

    // Write Date String //
    /*--------------------------------------------------------------
     * Description - Converts Datenum to DateString & calculates 
     *   internal data elements
     * Input(s):
     *   Void
     * Output(s):
     *   Void
     ---------------------------------------------------------------*/
    void writeDateString();

    // Read Date String //
    /*--------------------------------------------------------------
     * Description - Converts DateString to Datenum & calculates 
     *   internal data elements
     * Input(s):
     *   Void
     * Output(s):
     *   Void
     ---------------------------------------------------------------*/
    void readDateString();

    // Is Leap Year //
    /*--------------------------------------------------------------
     * Description - Simple function that returns true if provided 
     * year is a leap year
     * Input(s):
     *   int - year value
     * Output(s):
     *   bool - true = leap year :: false = common year
     ---------------------------------------------------------------*/
    bool isLeapyear(int givenYear);

    // Valid Format //
    /*--------------------------------------------------------------
     * Description - A function that checks the input characters, to
     *   determine if they're in the predefined set
     * Output(s):
     *   bool - true = valid format :: false = invalid format
     * Input(s):
     *   string - date format in: (YMDhms:/)
     ---------------------------------------------------------------*/
    bool validFormat(std::string* givenFormat);

    // Valid Date //
    /*--------------------------------------------------------------
    * Description - A function that checks the input characters, to
    *   determine if they're in the predefined set
    * Input(s):
    *   string - date in (0-9:/)
    *   string - date format previously verified
    * Output(s):
    *   bool - true = valid format :: false = invalid format
    ---------------------------------------------------------------*/
    bool validDate(std::string* givenDate,  std::string givenFormat);
};

#endif