#include <iostream>
#include "PriceContainer.h"

/*********************** CONSTRUCTORS ******************************/

PriceContainer::PriceContainer()
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

PriceContainer::PriceContainer(double dateNumber, float openPrice, 
	                           float closePrice, float highPrice, 
	                           float lowPrice, float adjustedPrice,
	                           int totalVol, char incSize) : PriceContainer()
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
PriceContainer::~PriceContainer(){ }

/*********************** SETTERS ***********************************/

// setDate //
void PriceContainer::setDate(double dateNumber)
{
		this->myDatenum = dateNumber;
}

void PriceContainer::setDateStrings(std::string properName, std::string displayName)
{
    this->myDateString = properName;
    this->myDisplayString = displayName;
}

// setHigh //
void PriceContainer::setHigh(float highPrice)
{
	if ( goodPrice(highPrice) )
		this->myHigh = highPrice;
	else
		this->myHigh = -1;
}

// setLow //
void PriceContainer::setLow(float lowPrice)
{
	if ( goodPrice(lowPrice) )
		this->myLow = lowPrice;
	else
		this->myLow = -1;
}

// setOpen //
void PriceContainer::setOpen(float openPrice)
{
	if ( goodPrice(openPrice) )
		this->myOpen = openPrice;
	else
		this->myOpen = -1;
}

// setClose //
void PriceContainer::setClose(float closePrice)
{
	if ( goodPrice(closePrice) )
		this->myClose = closePrice;
	else
		this->myClose = -1;
}

// setAdjusted //
void PriceContainer::setAdjusted(float adjustedPrice)
{
	if (goodPrice(adjustedPrice))
		this->myAdjusted = adjustedPrice;
	else
		this->myAdjusted = -1;
}

// setVolume //
void PriceContainer::setVolume(int totalVol)
{
	if (goodVolume(totalVol))
		this->myVolume = totalVol;
	else
		this->myVolume = -1;
}

// setIncrement //
void PriceContainer::setIncrement(char increment)
{
	if ( goodIncrement(increment) )
		this->myIncrement = increment;
	else
		this->myIncrement = '\0';
}

/*********************** GETTERS ***********************************/

// getDateNum //
double PriceContainer::getDatenum()
{
	return this->myDatenum;
}

// getDateStr //
std::string PriceContainer::getDateStr()
{
	return this->myDateString;
}

// getHigh //
float PriceContainer::getHigh()
{
	return this->myHigh;
}

// getLow //
float PriceContainer::getLow()
{
	return this->myLow;
}

// getOpen //
float PriceContainer::getOpen()
{
	return this->myOpen;
}

// getClose //
float PriceContainer::getClose()
{
	return this->myClose;
}

// getAdjusted //
float PriceContainer::getAdjusted()
{
	return this->myAdjusted;
}

// getVolume //
int PriceContainer::getVolume()
{
	return this->myVolume;
}

// getIncrement //
char PriceContainer::getIncrement()
{
	return this->myIncrement;
}

// selectData //
float PriceContainer::selectData(TypeDefinitions::PriceType selected)
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
bool PriceContainer::goodDatenum(double dateNumber)
{
	//Checks if the dateNumber is positive
	if (dateNumber < 0)
	{
		return false;
	}
	return true;
}

// goodPrice //
bool PriceContainer::goodPrice(float price)
{
	//Checks if the price given is positive
	if (price < 0)
	{
		return false;
	}
	return true;
}

// goodVolume //
bool PriceContainer::goodVolume(int totalVolume)
{
	//Checks if the volume given is positive
	if (totalVolume < 0)
	{
		return false;
	}
	return true;
}

// goodIncrement //
bool PriceContainer::goodIncrement(char increment)
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
bool PriceContainer::goodObject()
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
