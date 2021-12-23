#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>

class Definitions
{
    
public:

    // Type for my smoothing type selection
    enum class SmoothingType
    {
        MovingAverage = 0,
        Exponential = 1,
        DoubleExponential = 2,
        HoltWinters = 3
    };



    enum class PriceType
    {
        Close = 0,
        Open = 1,
        Low = 2,
        High = 3,
        Adjusted = 4
    };

    enum class TD_PeriodType
    {
        day = 0,
        month = 1,
        year = 2,
        ytd = 3

    };

    enum class TD_FrequencyType
    {
        minute = 0,
        daily = 1,
        weekly = 2,
        monthly = 3

    };

    // TD Period Type Map //
    /*--------------------------------------------------------------
    * Description - takes and enumerated value and returns the string
    * Input(s):
    *   TD_PeriodType - an enumeration of periods accepted by TD
    * Output(s):
    *   string - representing the enumeration desired
    ---------------------------------------------------------------*/
    std::string periodTypeMap(TD_PeriodType period);

    // Frequency Type Map //
    /*--------------------------------------------------------------
    * Description - takes and enumerated value and returns the string
    * Input(s):
    *   TD_FrequencyType - an enumeration of frequencies accepted by TD
    * Output(s):
    *   string - representing the enumeration desired
    ---------------------------------------------------------------*/
    std::string frequencyTypeMap(TD_FrequencyType frequency);
};


#endif
