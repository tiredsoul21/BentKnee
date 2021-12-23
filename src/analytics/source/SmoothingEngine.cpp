#ifndef SMOOTHINGENGINE_H
#include "SmoothingEngine.h"
#endif

/*********************** CONSTRUCTORS ******************************/

// Default //
SmoothingEngine::SmoothingEngine() { }

// Initializes smoothing type //
SmoothingEngine::SmoothingEngine(Definitions::SmoothingType smoothingType)
{
    mySmoothingType = smoothingType;
}

/*********************** DESTRUCTORS *******************************/

SmoothingEngine::~SmoothingEngine() { } 

/************************ FUNCTIONAL *******************************/

// nextEntry - Overload 2 //
float SmoothingEngine::nextEntry(float val)
{
    return mapEntry(val);
}

// nextEntry - Overload 1 //
double SmoothingEngine::nextEntry(double val)
{
    return mapEntry(val);
}

// nextEntry //
template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
T SmoothingEngine::mapEntry(T datum)
{
    switch (mySmoothingType)
	{
	case Definitions::SmoothingType::MovingAverage:
		return movingAverage(datum);
	case Definitions::SmoothingType::Exponential:
		return exponential(datum);
	case Definitions::SmoothingType::DoubleExponential:
		return doubleExponential(datum);
	case Definitions::SmoothingType::HoltWinters:
		return holtWinters(datum);
	}
    
    // This will never be reached, but...
    return datum;
}

// Exponential Smoothing //
template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
T SmoothingEngine::exponential(T datum)
{
    mature++;
    
    // There is no known level of maturity however, if significance
    // Is found in historic data, then there ought to be some relative
    // To the amount of significance placed.
    int maturePoint = round(averageSize * historicSig);
    if (mature == maturePoint)
        isMature = true;

    double historicNext;
    if (mature == 1)
    {
        // S0 = x0
        historicNext = datum;
    }
    else
    {
        // St = (1-α)xt-1 + αst-1, t > 0
        historicNext = historicSig*historicLast + (1-historicSig)*datum;
    }
    historicLast = historicNext;
    
    return (T)historicLast;
}

// Moving Average //
template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
T SmoothingEngine::movingAverage(T datum)
{
    mature++;
    double returnValue;

    if (isMature)
    {
        // Calculate the index to be replaced
        int lastIndex = (mature - 1) % averageSize;

        // Calculate the volume sums
        dataSum += datum - data[lastIndex];

        // Store the volumes for later
        returnValue = dataSum / averageSize;
    }
    else
    {
        if (mature == averageSize)
            isMature = true;

        // Calculate the volume sums
        dataSum += datum;

        // Store the volumes for later
        returnValue = dataSum / averageSize;
    }

    return (T)returnValue;
}

// Double Exponential //
template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
T SmoothingEngine::doubleExponential(T datum)
{
    mature++;
    
    // There is no known level of maturity however, if significance is found in 
    // historic/trend data, then there ought to be some relative
    // to the amount of significance placed.
    int maturePoint = std::max(round(averageSize * historicSig),
                               round(averageSize * trendSig));
    if (mature == maturePoint)
        isMature = true;

    double historicNext, trendNext;
    if (mature == 1)
    {
        // S0 = x0
        historicNext = datum;
        trendNext = 0;
    }
    else
    {
        // St = (1-α)xt-1 + αst-1, t > 0
        historicNext = historicSig*historicLast + (1-historicSig)*datum;
        // Bt = b (At - At-1) + (1 - b) Bt-1 0< b <= 1
        trendNext = trendSig*historicLast + (1-trendSig)*(historicNext - historicLast);
    }
    historicLast = historicNext;
    trendLast = trendNext;

    return (T)(historicLast + trendLast);
}

// Holt Winters //
template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
T SmoothingEngine::holtWinters(T datum)
{
    mature++;

    double historicNext, trendNext, seasonalNext, returnVal;
    if (mature == 1)
    {
        // Initialize my variables
        historicNext = datum;
        trendNext = 0;
        // We will store up the data for now to calculate the seasonal stuff later
        
        data[0] = datum;
        dataSum += datum;
        
        returnVal = historicNext;
    }
    else if (mature <= periodicity)
    {
        // St = (1-α)xt-1 + αst-1, t > 0
        historicNext = historicSig*historicLast + (1-historicSig)*datum;
        // Bt = b (At - At-1) + (1 - b) Bt-1 0< b <= 1
        trendNext = trendSig*trendLast + (1-trendSig)*(historicNext - historicLast);
        
        data[mature - 1] = datum;
        dataSum += datum;
        
        returnVal = historicNext + trendNext;
    }
    if (mature == periodicity + 1)
    {
        isMature = true;
        // Run through and estimate the initial seasonality
        for (int i = 0; i < periodicity; i++)
            data[i] = data[i]/dataSum*periodicity;
    }
    if (mature > periodicity)
    {
        // Calculate the index to be replaced
        int lastIndex = (mature - 1) % periodicity;
        
        historicNext = historicSig*(historicLast + trendLast) +
                (1-historicSig)*datum/data[lastIndex];
        trendNext = trendSig*trendLast +
                (1-trendSig)*(historicNext-historicLast);
        seasonalNext = seasonalSig*data[lastIndex] +
                (1-seasonalSig)*datum/historicNext;
        
        returnVal = (historicNext + trendNext)*data[lastIndex];
        data[lastIndex] = seasonalNext;
    }
    
    historicLast = historicNext;
    trendLast = trendNext;
    
    return (T)returnVal;
}

/************************* SETTERS *********************************/

// setAverageSize //
void SmoothingEngine::setAverageSize(int size)
{
    if ( size > 0 && size <= MAX_SIZE )
        averageSize = size;
}

// Set Smoothing Type //    
void SmoothingEngine::setSmoothingType(Definitions::SmoothingType type)
{
    mySmoothingType = type;
    dataSum = 0;
    mature = 0;
    isMature = false;
}

// Set Historical Significance //    
void SmoothingEngine::setHistoricalSig(float sig)
{
    if (sig >= 0 && sig <= 1)
        historicSig = sig;
}

// Set Trend Significance //    
void SmoothingEngine::setTrendSig(float sig)
{
    if (sig >= 0 && sig <= 1)
        trendSig = sig;
}

// Set Seasonal Significance //    
void SmoothingEngine::setSeasonalSig(float sig)
{
    if (sig >= 0 && sig <= 1)
        seasonalSig = sig;
}

// Set Periodicity //
void SmoothingEngine::setPeriod(int period)
{
    // 5 is an arbitrary number, and may be lessened...
    if (period >= 5 && period <= MAX_SIZE){
        periodicity = period;
    }
}

/************************* GETTERS *********************************/

// Get Average Size //    
int SmoothingEngine::getAverageSize()
{
    return averageSize;
}

// Get Smoothing Type //    
Definitions::SmoothingType SmoothingEngine::getSmoothingType()
{
    return mySmoothingType;
}

// Get Historical Significance //    
float SmoothingEngine::getHistoricSig()
{
    return historicSig;
}

// Get Trend Significance //    
float SmoothingEngine::getTrendSig()
{
    return trendSig;
}

// Get Seasonal Significance //    
float SmoothingEngine::getSeasonalSig()
{
    return seasonalSig;
}

// Get Periodicity //
int SmoothingEngine::getPeriod()
{
    return periodicity;
}