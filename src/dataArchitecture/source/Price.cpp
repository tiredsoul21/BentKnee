#include <iostream>
#include "Price.h"

/*********************** CONSTRUCTORS ******************************/

Price::Price()
{
	// Object initialized with empty or trash values
	myDatenum = -1;
	myDateString = "";
	myLow = -1;
	myHigh = -1;
	myOpen = -1;
	myClose = -1;
	myVolume = -1;
	myAdjusted = -1;
	myIncrement = '\0';
	initComplete = false;
}

Price::Price(double dateNumber, float openPrice, 
	                           float closePrice, float highPrice, 
	                           float lowPrice, float adjustedPrice,
	                           int totalVol, char incSize) : Price()
{
	// Object initialized and contents validates
	setDate(dateNumber);

	setOpen(openPrice);
	setClose(closePrice);
	setLow(lowPrice);
	setHigh(highPrice);
	setAdjusted(adjustedPrice);
	setIncrement(incSize);
	setVolume(totalVol);

	if (goodObject())
	{
		this->initComplete = true;
	}
	else
	{
		this->initComplete = false;
		delete this;
	}
}

/*********************** DESTRUCTORS *******************************/

// Default Constructor //
Price::~Price(){ }

/*********************** SETTERS ***********************************/

// setDate //
void Price::setDate(double dateNumber)
{
		this->myDatenum = dateNumber;
}

void Price::setDateStrings(std::string properName, std::string displayName)
{
    this->myDateString = properName;
    this->myDisplayString = displayName;
}

// setHigh //
void Price::setHigh(float highPrice)
{
	if ( goodPrice(highPrice) )
		this->myHigh = highPrice;
	else
		this->myHigh = -1;
}

// setLow //
void Price::setLow(float lowPrice)
{
	if ( goodPrice(lowPrice) )
		this->myLow = lowPrice;
	else
		this->myLow = -1;
}

// setOpen //
void Price::setOpen(float openPrice)
{
	if ( goodPrice(openPrice) )
		this->myOpen = openPrice;
	else
		this->myOpen = -1;
}

// setClose //
void Price::setClose(float closePrice)
{
	if ( goodPrice(closePrice) )
		this->myClose = closePrice;
	else
		this->myClose = -1;
}

// setAdjusted //
void Price::setAdjusted(float adjustedPrice)
{
	if (goodPrice(adjustedPrice))
		this->myAdjusted = adjustedPrice;
	else
		this->myAdjusted = -1;
}

// setVolume //
void Price::setVolume(int totalVol)
{
	if (goodVolume(totalVol))
		this->myVolume = totalVol;
	else
		this->myVolume = -1;
}

// setIncrement //
void Price::setIncrement(char increment)
{
	if ( goodIncrement(increment) )
		this->myIncrement = increment;
	else
		this->myIncrement = '\0';
}

/*********************** GETTERS ***********************************/

// getDateNum //
double Price::getDatenum()
{
	return this->myDatenum;
}

// getDateStr //
std::string Price::getDateStr()
{
	return this->myDateString;
}

// getHigh //
float Price::getHigh()
{
	return this->myHigh;
}

// getLow //
float Price::getLow()
{
	return this->myLow;
}

// getOpen //
float Price::getOpen()
{
	return this->myOpen;
}

// getClose //
float Price::getClose()
{
	return this->myClose;
}

// getAdjusted //
float Price::getAdjusted()
{
	return this->myAdjusted;
}

// getVolume //
int Price::getVolume()
{
	return this->myVolume;
}

// getIncrement //
char Price::getIncrement()
{
	return this->myIncrement;
}

// selectData //
float Price::selectData(TypeDefinitions::PriceType selected)
{
	switch (selected)
	{
	case TypeDefinitions::PriceType::Close:
		return this->myClose;
	case TypeDefinitions::PriceType::Open:
		return this->myOpen;
	case TypeDefinitions::PriceType::High:
		return this->myHigh;
	case TypeDefinitions::PriceType::Low:
		return this->myLow;
	case TypeDefinitions::PriceType::Adjusted:
		return this->myAdjusted;
	default:
		// Error handling left to handler
		return -1;
	}
}

/*********************** Private Methods ****************************/

// goodDateNum //
bool Price::goodDatenum(double dateNumber)
{
	//Checks if the dateNumber is positive
	if (dateNumber < 0)
	{
		return false;
	}
	return true;
}

// goodPrice //
bool Price::goodPrice(float price)
{
	//Checks if the price given is positive
	if (price < 0)
	{
		return false;
	}
	return true;
}

// goodVolume //
bool Price::goodVolume(int totalVolume)
{
	//Checks if the volume given is positive
	if (totalVolume < 0)
	{
		return false;
	}
	return true;
}

// goodIncrement //
bool Price::goodIncrement(char increment)
{
	//Checks if the dateNumber is positive
	if (increment != 'Y' &&
		increment != 'M' &&
		increment != 'w' &&
		increment != 'd' &&
		increment != 'h' &&
		increment != 'm' &&
		increment != 's' &&
		increment != 'o')
	{
		return false;
	}
	return true;
}

// goodObject //
bool Price::goodObject()
{
	if (this->myDatenum == -1)
	{
		myErrorString += "Initialization failed: datenum found negative.\n";
		return false;
	}
	else if (this->myClose == -1)
	{
		myErrorString += "Initialization failed: closing price found negative.  (" + std::to_string(this->myClose) + ")\n";
		return false;
	}
	else if (this->myOpen == -1)
	{
		myErrorString += "Initialization failed: opening price found negative.  (" + std::to_string(this->myOpen) + ")\n";
		return false;
	}
	else if (this->myHigh == -1)
	{
		myErrorString += "Initialization failed: high price found negative.  (" + std::to_string(this->myHigh) + ")\n";
		return false;
	}
	else if (this->myLow == -1)
	{
		myErrorString += "Initialization failed: low price found negative.  (" + std::to_string(this->myLow) + ")\n";
		return false;
	}
	else if (this->myVolume == -1)
	{
		myErrorString += "Initialization failed: volume found negative.  (" + std::to_string(this->myVolume) + ")\n";
		return false;
	}
	else if (this->myIncrement == '\0')
	{
		myErrorString += "Initialization failed: invalid increment.  Use (Y/M/w/d/h/m/s).  (" + std::to_string(this->myIncrement) + ")\n";
		return false;
	}

	return true;
}
