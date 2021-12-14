#include "DateEngine.h"

#include <iostream>

/*********************** CONSTRUCTORS ******************************/

// DateEngine() -- default
DateEngine::DateEngine()
{
    myDateStr = "1970/01/01 00:00:00";
    myFormat = "MM/DD/YYYY hh:mm:ss";
    myYearSize = 4;
    myFormatChange = false;

    myDatenum = 0;

    myYear = 1970;
    myMonth = 1;
    myDay = 1;
    myHour = 0;
    myMinute = 0;
    mySecond = 0;

    myEpochYears = 0;
    myEpochMonths = 0;
    myEpochWeeks = 0;
    myEpochDays = 0;
    myEpochHours = 0;
    myEpochMinutes = 0;
    myEpochSeconds = 0;
}

// Datenum(string, string) //
DateEngine::DateEngine(std::string dateString, std::string dateFormat) : DateEngine()
{
    // We're going validate the format, then the string 
    setDateFormat(dateFormat);

    if ( !errorFound() )
        setDateString(dateString);
    if ( !errorFound() )
        readDateString();
}

// DateEngine(double) //
DateEngine::DateEngine(double datenum) : DateEngine()
{
    setDatenum(datenum);
}

/*********************** DESTRUCTORS *******************************/

DateEngine::~DateEngine(){ }

/************************** SETTERS ********************************/

// setDateFormat //
bool DateEngine::setDateFormat(std::string dateFormat)
{
    if (validFormat(dateFormat))
    {
        if (dateFormat.compare(this->myFormat))
        {
            this->myFormat = dateFormat;
            myFormatChange = true;
            writeDateString();
        }
        return true;
    }
    else
    {
        return false;
        // There is nothing to do here, error added by valid function
    }
}

// setDatenum //
void DateEngine::setDatenum(double datenum)
{
    if (datenum > 0)
    {
        // Let's not waste time
        if (datenum != this->myDatenum)
        {
            this->myDatenum = datenum;
            writeDateString();
        }
    }
    else
    {
        this->myErrorString += "Failed to load date data, bad datenum given < 0\n";
    }
}

// setDateString //
void DateEngine::setDateString(std::string dateString)
{
    // We're going validate the format, then the string 
    if (validDate(dateString, myFormat) )
    {
        if (dateString.compare(this->myDateStr))
        {
            myDateStr = dateString;
            readDateString();
        }
    }
    else
    {
        // Nothing to do here, error handling done in valid*
    }
}

/************************** GETTERS ********************************/

// getDateFormat //
std::string DateEngine::getDateFormat()
{
    return this->myFormat;
}

// getDatenum //
double DateEngine::getDatenum()
{
    return this->myDatenum;
}

// getDateString //
std::string DateEngine::getDateString()
{
    return this->myDateStr;
}

// getYear //
int DateEngine::getYear()
{
    return this->myYear;
}

// getMonth //
int DateEngine::getMonth()
{
    return this->myMonth;
}

// getDay //
int DateEngine::getDay()
{
    return this->myDay;
}

// getHour //
int DateEngine::getHour()
{
    return this->myHour;
}

// getMinute //
int DateEngine::getMinute()
{
    return this->myMinute;
}

// getSecond //
int DateEngine::getSecond()
{
    return this->mySecond;
}

// getEpochYears //
long DateEngine::getEpochYears()
{
    return this->myEpochYears;
}

// getEpochMonths //
long DateEngine::getEpochMonths()
{
    return this->myEpochMonths;
}

// getEpochWeeks //
long DateEngine::getEpochWeeks()
{
    return this->myEpochWeeks;
}

// getEpochDays //
long DateEngine::getEpochDays()
{
    return this->myEpochDays;
}

// getEpochHours //
long DateEngine::getEpochHours()
{
    return this->myEpochHours;
}

// getEpochMinutes //
long DateEngine::getEpochMinutes()
{
    return this->myEpochMinutes;
}

// getEpochSeconds //
long DateEngine::getEpochSeconds()
{
    return this->myEpochSeconds;
}

/************************ FUNCTIONAL ******************************/

// looseDateString //
std::string DateEngine::looseDateString(std::string givenFormat)
{
    std::string returnString = "";
    generateMyString(givenFormat, returnString);
    return returnString;
}

// readDateString //
void DateEngine::readDateString()
{
    for (unsigned int i = 0; i < this->myDateStr.length(); ++i)
    {
        // If the next field expected is the year...
        if (this->myFormat[i] == 'Y')
        {
            // If string is size 4, parse as size 4
            if (myYearSize == 4)
                this->myYear = std::stoi(this->myDateStr.substr(i, 4));

            // If string is size 2, parse as size 2
            if (myYearSize == 2)
            {
                this->myYear = std::stoi(this->myDateStr.substr(i, 2));
                // We make a bold assumption, that if the year is < 40, you're
                // referring to 20**,  >=40 19**
                if (this->myYear < 40)
                    this->myYear += 2000;
                else
                    this->myYear += 1900;
            }

            // Move the index past the year
            i = i + myYearSize - 1;
        }
        
        // If the next field expected is the month...
        if (this->myFormat[i] == 'M')
        {
            this->myMonth = std::stoi(this->myDateStr.substr(i, 2));
            i++;
        }
        
        // If the next field expected is the day...
        if (this->myFormat[i] == 'D')
        {
            this->myDay = std::stoi(this->myDateStr.substr(i, 2));
            i++;
        }
        
        // If the next field expected is the hour...
        if (this->myFormat[i] == 'h')
        {
            this->myHour = std::stoi(this->myDateStr.substr(i, 2));
            i++;
        }
        
        // If the next field expected is the minute...
        if (this->myFormat[i] == 'm')
        {
            this->myMinute = std::stoi(this->myDateStr.substr(i, 2));
            i++;
        }
        
        // If the next field expected is the second...
        if (this->myFormat[i] == 's')
        {
            this->mySecond = std::stoi(this->myDateStr.substr(i, 2));
            i++;
        }
        
        // Other fields/markers are thus ignored
    }
    
    // Calculate my internal values
    myEpochYears = myYear - 1970;
    myEpochMonths = 12 * myEpochYears + myMonth;
    myEpochDays = myDay - 1; // initialize days with days had this month so far (excludes current)
    myEpochSeconds = 0;
    
    // Accumulates the days since 1970 of full years
    for (int thisYear = 1970; thisYear < myYear; ++thisYear)
    {
        bool leapYear = isLeapyear(thisYear);

        // Accumulate days from past years
        if (leapYear)
            myEpochDays += 366;
        else
            myEpochDays += 365;
    }

    int thisMonth = 1;

    // Accumulates the days of the partial year
    while (thisMonth < myMonth)
    {
        // Add days accumulated this year so far
        if (thisMonth == 4 || thisMonth == 6 || thisMonth == 9 || thisMonth == 11)
        {
            myEpochDays = myEpochDays + 30;
        }
        else if (thisMonth == 2)
        {
            if (isLeapyear(myYear))
                myEpochDays = myEpochDays + 29;
            else
                myEpochDays = myEpochDays + 28;
        }
        else
        {
            myEpochDays = myEpochDays + 31;
        }
        thisMonth++;
    }

    // Whole value of days/7 offset by 3 days see .h note
    myEpochWeeks = (myEpochDays + 3) / 7;

    myEpochHours = myEpochDays*24 + myHour;
    myEpochMinutes = myEpochHours*60 + myMinute;
    myEpochSeconds = myEpochSeconds + myEpochMinutes*60 + mySecond;

    // Datenum is the integer day + fractional day (decimal > 1)
    myDatenum = myEpochDays + (double)myHour/24 + (double)myMinute/1440 + (double)mySecond/86400;
}

// writeDateString //
void DateEngine::writeDateString()
{
    // First we'll Check if it's just a format change.  If so, only need to do the string.
    //   Will skip to the bottom

    if (!myFormatChange)
    {
        // Here on out, we recalculate internals
        // Flag used to break loops
        bool fragmentedUnit = false;

        // Used to store internal date info
        double localDatenum = myDatenum;

        // Whole value of localDatenum is the epochDay
        myEpochDays = (long)localDatenum;

        // Whole value of days/7 offset by 3 days see .h note
        myEpochWeeks = (myEpochDays + 3) / 7;

        // Starting at 1970, we calculate how many years in datenum
        int thisYear = 1970;
        bool leapYear = isLeapyear(thisYear);
        while (!fragmentedUnit)
        {
            if (leapYear && (int)localDatenum > 366)
            {
                thisYear++;
                localDatenum -= 366;
            }
            else if (!leapYear && (int)localDatenum > 365)
            {
                thisYear++;
                localDatenum -= 365;
            }
            else
            {
                // the relationship between epoch years and current year is nil
                fragmentedUnit = true;
            }
            leapYear = isLeapyear(thisYear);
        }
        myYear = thisYear;
        myEpochYears = myYear - 1970;

        // Calculates the month and day
        fragmentedUnit = false;
        int thisMonth = 1;
        while (!fragmentedUnit)
        {
            int daysThisMonth = 31;
            if (thisMonth == 4 || thisMonth == 6 || thisMonth == 9 || thisMonth == 11)
            {
                daysThisMonth = 30;
            }
            else if (thisMonth == 2)
            {
                if (isLeapyear(myYear))
                    daysThisMonth = 29;
                else
                    daysThisMonth = 28;
            }
            else
            {
                // Nothing to do here, the rest have 31, and we already set that
            }

            if ((int)localDatenum > daysThisMonth)
            {
                localDatenum -= daysThisMonth;
                thisMonth++;
            }
            else
            {
                fragmentedUnit = true;
                //The rest of the whole number is the day of the month
                myDay = (int)localDatenum + 1;
                localDatenum -= (int)localDatenum;
            }
        }
        myMonth = thisMonth;
        myEpochMonths = 12 * myEpochYears + myMonth;

        if (localDatenum == 0)
        {
            // Catches undefined potential
            myHour = 0;
            myMinute = 0;
            mySecond = 0;
        }
        else
        {
            // Calculates the number of hours and removes it from local datenum
            myHour = (int)(24 * localDatenum);
            localDatenum -= myHour / 24.0;
            // Calculates the number of minutes and removes it from the local datenum
            myMinute = (int)(1440 * localDatenum);
            localDatenum -= myMinute / 1440.0;
            // What's left (if anything) is seconds
            mySecond = (int)(86400 * localDatenum) + 1;
        }
        // Finishes calculating epochs
        myEpochHours = myEpochDays * 24 + myHour;
        myEpochMinutes = myEpochHours * 60 + myMinute;
        myEpochSeconds = myEpochMinutes * 60 + mySecond;

        // Anything anything left in localDatenum is partial seconds or error, and we don't handle this 
    }

    // Now I will clear & write the new dateString
    myDateStr = "";
    generateMyString(myFormat, myDateStr);

    return;
}

// generateMyString //
void DateEngine::generateMyString(std::string givenFormat, std::string &outputString)
{
    // If we've made it here the format is already validated
    for (unsigned int i = 0; i < givenFormat.length(); ++i)
    {
        // Assign the given values
        if (givenFormat[i] == 'Y')
        {
            if (myYearSize == 4)
                outputString += std::to_string(myYear);
            else
                // I only care to take the last two of the year in this case
                outputString += std::to_string(myYear).substr(2, 2);

            i = i + myYearSize - 1;
        }
        else if (givenFormat[i] == 'M')
        {
            if (std::to_string(myMonth).length() < 2)
                outputString += "0" + std::to_string(myMonth);
            else
                outputString += std::to_string(myMonth);
            i++;
        }
        else if (givenFormat[i] == 'D')
        {
            if (std::to_string(myDay).length() < 2)
                outputString += "0" + std::to_string(myDay);
            else
                outputString += std::to_string(myDay);
            i++;
        }
        else if (givenFormat[i] == 'h')
        {
            if (std::to_string(myHour).length() < 2)
                outputString += "0" + std::to_string(myHour);
            else
                outputString += std::to_string(myHour);
            i++;
        }
        else if (givenFormat[i] == 'm')
        {
            if (std::to_string(myMinute).length() < 2)
                outputString += "0" + std::to_string(myMinute);
            else
                outputString += std::to_string(myMinute);
            i++;
        }
        else if (givenFormat[i] == 's')
        {
            if (std::to_string(mySecond).length() < 2)
                outputString += "0" + std::to_string(mySecond);
            else
                outputString += std::to_string(mySecond);
            i++;
        }
        else
        {
            // If none of they above, it must be a formatting character
            outputString += givenFormat[i];
        }
    }
}

// isLeapYear //
bool DateEngine::isLeapyear(int givenYear)
{
    // There is a leap year every year divisible by
    // four except for years which are both divisible
    // by 100 and not divisible by 400
    if (givenYear % 4 != 0)
        return false;
    else if (givenYear % 100 != 0)
        return true;
    else if (givenYear % 400 != 0)
        return false;
    else
        return true;
}

// validFormat //
bool DateEngine::validFormat(std::string givenFormat)
{
    // Count format tokens for date
    int yearCount = 0;      // must be 2 or 4
    int monthCount = 0;     // must be 2
    int dayCount = 0;       // must be 2
    int hourCount = 0;      // must be 2
    int minuteCount = 0;    // must be 2
    int secondCount = 0;    // must be 2

    // Used to find fragmented date formats
    char activeChar = 'x';
    bool yearFlag = false;
    bool monthFlag = false;
    bool dayFlag = false;
    bool hourFlag = false;
    bool minuteFlag = false;
    bool secondFlag = false;

    std::string localString = "";

    // Check String length
    if (givenFormat.length() == 0)
    {
        myErrorString += "No date format given!\n";
        return false;
    }

    // Looping through the provided format
    std::string validChars = "YDMhms:/ -";
    for (unsigned int i = 0; i < givenFormat.length(); ++i)
    {
        // We are going to double loop through the strings and make sure
        //   the givenFormat is in the set of expected characters
        if (validChars.find(givenFormat[i], 0) == std::string::npos)
        {
            // This char is not in the valid charset
            localString += "Error: Character: '";
            localString += givenFormat[i];
            localString += "' not a valid character.\n";
        }

        if (activeChar != givenFormat[i])
        {
            // Entering the if below means we're leaving that format, mark as complete (true)
            if (activeChar == 'Y')
                yearFlag = true;
            else if (activeChar == 'M')
                monthFlag = true;
            else if (activeChar == 'D')
                dayFlag = true;
            else if (activeChar == 'h')
                hourFlag = true;
            else if (activeChar == 'm')
                minuteFlag = true;
            else if (activeChar == 's')
                secondFlag = true;

            // Update the active char
            activeChar = givenFormat[i];
        }

        // Count token characters
        if (givenFormat[i] == 'Y' && !yearFlag)
            yearCount++;
        else if (givenFormat[i] == 'M' && !monthFlag)
            monthCount++;
        else if (givenFormat[i] == 'D' && !dayFlag)
            dayCount++;
        else if (givenFormat[i] == 'h' && !hourFlag)
            hourCount++;
        else if (givenFormat[i] == 'm' && !minuteFlag)
            minuteCount++;
        else if (givenFormat[i] == 's' && !secondFlag)
            secondCount++;
        // If we made it here, the char is valid, but the flag was hit
        // Meaning date format fragmentation was found
        else if (givenFormat[i] == 'Y' && yearFlag)
            localString += "Error: Date fragmentation occurred for: Y\n";
        else if (givenFormat[i] == 'M' && monthFlag)
            localString += "Error: Date fragmentation occurred for: M\n";
        else if (givenFormat[i] == 'D' && dayFlag)
            localString += "Error: Date fragmentation occurred for: D\n";
        else if (givenFormat[i] == 'h' && hourFlag)
            localString += "Error: Date fragmentation occurred for: h\n";
        else if (givenFormat[i] == 'm' && minuteFlag)
            localString += "Error: Date fragmentation occurred for: m\n";
        else if (givenFormat[i] == 's' && secondFlag)
            localString += "Error: Date fragmentation occurred for: s\n";
    }

    // Validate token counts 
    if (yearCount != 4 && yearCount != 2)
        localString += "Error: Year format incorrect, expected YY or YYYY\n";

    if (monthCount != 2)
        localString += "Error: Month format incorrect, expected MM\n";

    if (dayCount != 2)
        localString += "Error: Day format incorrect, expected DD\n";

    if (hourCount != 2 )
        localString += "Error: Hour format incorrect, expected hh\n";

    if (minuteCount != 2)
        localString += "Error: Minute format incorrect, expected mm\n";

    if (secondCount != 2)
        localString += "Error: Second format incorrect, expected ss\n";

    // We make sure there is at LEAST one data element
    //   That is, the user didn't send a string with only ' ', '/', or ':'
    if (yearCount + monthCount + dayCount + hourCount + minuteCount + secondCount == 0)
    {
        localString += "Error: string: '";
        localString += givenFormat;
        localString += "' contains no data elements (YMDhms).\n";
    }

    if (localString.length() > 0)
    {
        this->myErrorString += localString;
        return false;
    }

    // if the format is valid I will update my year format size here
    myYearSize = yearCount;

    return true;
}

// validDate //
bool DateEngine::validDate(std::string givenDate, std::string givenFormat)
{
    int testYear = -1;
    int testMonth = -1;
    int testDay = -1;
    int testHour = -1;
    int testMinute = -1;
    int testSecond = -1;

    // Local error collection string
    std::string localString = "";

    // check string length
    if (givenFormat.length() != givenDate.length())
    {
        myErrorString += "Error: date string inconsistent in length with format.\n";
        return false;
    }

    for (unsigned int i = 0; i < givenFormat.length(); ++i)
    {
        // Parse date string
        try
        {
            // Assign the given values
            if (givenFormat[i] == 'Y')
            {
                if (myYearSize == 4)
                    testYear = std::stoi(givenDate.substr(i, 4));

                if (myYearSize == 2)
                    testYear = std::stoi(givenDate.substr(i, 2));

                i = i + myYearSize - 1;
            }
            else if (givenFormat[i] == 'M')
            {
                testMonth = std::stoi(givenDate.substr(i, 2));
                i++;
            }
            else if (givenFormat[i] == 'D')
            {
                testDay = std::stoi(givenDate.substr(i, 2));
                i++;
            }
            else if (givenFormat[i] == 'h')
            {
                testHour = std::stoi(givenDate.substr(i, 2));
                i++;
            }
            else if (givenFormat[i] == 'm')
            {
                testMinute = std::stoi(givenDate.substr(i, 2));
                i++;
            }
            else if (givenFormat[i] == 's')
            {
                testSecond = std::stoi(givenDate.substr(i, 2));
                i++;
            }
            // If it's none of the above, it must be a special character
            else if (givenFormat[i] != givenDate[i])
            {
                localString += "Error: Invalid special character used in date string: '";
                localString += givenDate[i];
                localString += "'\n";
            }
        }
        catch (...)
        {
            localString += "Failed to parse string: String to number.  Check format\n";
            return false;
        }
    }

    // Validate year
    if (testYear != -1 && myYearSize == 4)
    {
        if (testYear < 1970 || testYear > 2039)
        {
            localString += "Year exceeds internal year limit: 1970-2039.\n";
        }
    }
    else if (testYear != -1 && myYearSize == 2)
    {
        if (testYear < 70 && testYear > 39)
        {
            localString += "Year exceeds internal year limit: 1970-2039.\n";
        }
    }

    // Validate month
    if (testMonth != -1 && (testMonth < 1 || testMonth > 12))
    {
        localString += "Month exceeds limit: 1-12.\n";
    }

    // Validate day 4,6,9,11
    if (testMonth == 4 || testMonth == 6 || testMonth == 9 || testMonth == 11)
    {
        if (testDay > 30 || testDay < 0)
        {
            localString += "Day exceeds limit: 1-30.\n";
        }
    }
    else if (testMonth == 1 || testMonth == 3 || testMonth == 5 || testMonth == 7 ||
             testMonth == 8 || testMonth == 10 || testMonth == 12)
    {
        if (testDay > 31 || testDay < 0)
        {
            localString += "Day exceeds limit: 1-31.\n";
        }
    }
    else if (testMonth == 2)
    {
        // Default: if year not passed, is to assume non-leap year
        bool leapYear = false;
        if (testYear > 70 && testYear < 101)
        {
            leapYear = isLeapyear(testYear + 1900);
        }
        else if (testYear >= 0 && testYear < 40)
        {
            leapYear = isLeapyear(testYear + 2000);
        }
        else if (testYear >= 0)
        {
            leapYear = isLeapyear(testYear);
        }
        if (leapYear)
        {
            if (testDay > 29 || testDay < 0)
            {
                localString += "Day exceeds limit: 1-29.\n";
            }
        }
        else
        {
            if (testDay != -1 && testYear == -1)
            {
                localString += "Day exceeds limit (ambiguous year): 1-28.\n";
            }
            else if (testDay != -1 && (testDay > 28 || testDay < 0) )
            {
                localString += "Day exceeds limit: 1-28.\n";
            }
        }
    }

    // Validate hours
    if (testHour != -1 && testHour < 0 && testHour > 23)
    {
        localString += "Hour exceeds limit: 0-23.\n";
    }    
    
    // Validate minutes
    if (testMinute != -1 && testMinute < 0 && testMinute > 59)
    {
        localString += "Minutes exceeds limit: 0-59.\n";
    }

    // Validate seconds
    if (testMinute != -1 && testSecond < 0 && testSecond > 59)
    {
        localString += "Seconds exceeds limit: 0-59.\n";
    }

    if (localString.length() > 0)
    {
        myErrorString += localString;
        return false;
    }

    return true;
}

// epochLongToDouble
double DateEngine::epochLongToDouble(long  seconds)
{
    // Get rough estimate of double
    double doubleDatenum = seconds / 86400.0;

    // Get leap seconds
    setDatenum(doubleDatenum);
    int leapSeconds = getLeapSecondsSince(getYear(), getMonth());

    // This MAY be off by 1 seconds
    return doubleDatenum - leapSeconds / 86400.0;
}

// epochLongToDouble
long DateEngine::epochDoubleToLong(double day)
{
    setDatenum(day);
    int leapSeconds = getLeapSecondsSince(getYear(), getMonth());
    return (long)(day * 86400 + leapSeconds);
}

int DateEngine::getLeapSecondsSince(int year, int month)
{
    int loopYear = 1970;
    int totalLeapSeconds = 0;
    
    // Add up previous years
    while (year > loopYear)
    {
        int intReturn = myLeapSecondMap.at(loopYear);
        if (intReturn == 3)
            totalLeapSeconds += 2;
        else if (intReturn > 0)
            totalLeapSeconds++;

        loopYear++;
    }

    // Check last year for June leap seconds
    if (myLeapSecondMap.at(loopYear) > 1 && month >= 6)
        totalLeapSeconds++;
    return totalLeapSeconds;
}
