#ifndef PRICE_H
#include "Price.h"
#endif

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
	                           long totalVol, char incSize) : Price()
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
    {
		this->myHigh = -1;
        myErrorString += "Price::setHigh - bad price: " + std::to_string(highPrice) + "\n";
    }
}

// setLow //
void Price::setLow(float lowPrice)
{
	if ( goodPrice(lowPrice) )
		this->myLow = lowPrice;

	else
    {
		this->myLow = -1;
        myErrorString += "Price::setLow - bad price: " + std::to_string(lowPrice) + "\n";
    }
}

// setOpen //
void Price::setOpen(float openPrice)
{
	if ( goodPrice(openPrice) )
		this->myOpen = openPrice;
	else
    {
		this->myOpen = -1;
        myErrorString += "Price::setOpen - bad price: " + std::to_string(openPrice) + "\n";
    }
}

// setClose //
void Price::setClose(float closePrice)
{
	if ( goodPrice(closePrice) )
		this->myClose = closePrice;
	else
    {
		this->myClose = -1;
        myErrorString += "Price::setClose - bad price: " + std::to_string(closePrice) + "\n";
    }
}

// setAdjusted //
void Price::setAdjusted(float adjustedPrice)
{
	if (goodPrice(adjustedPrice))
		this->myAdjusted = adjustedPrice;
	else
    {
		this->myAdjusted = -1;
        myErrorString += "Price::setAdjusted - bad price: " + std::to_string(adjustedPrice) + "\n";
    }
}

// setVolume //
void Price::setVolume(long totalVol)
{
	if (goodVolume(totalVol))
		this->myVolume = totalVol;
	else
    {
		this->myVolume = -1;
        myErrorString += "Price::setVolume - bad volume: " + std::to_string(totalVol) + "\n";
    }
}

// setIncrement //
void Price::setIncrement(char increment)
{
	if ( goodIncrement(increment) )
		this->myIncrement = increment;
	else
    {
		this->myIncrement = '\0';
        myErrorString += "Price::setIncrement - bad increment: ";
        myErrorString += increment + "\n";
    }
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
long Price::getVolume()
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
bool Price::goodVolume(long totalVolume)
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
		return false;
	else if (this->myClose == -1)
		return false;
	else if (this->myOpen == -1)
		return false;
	else if (this->myHigh == -1)
		return false;
	else if (this->myLow == -1)
		return false;
	else if (this->myVolume == -1)
		return false;
	else if (this->myIncrement == '\0')
		return false;

	return true;
}
