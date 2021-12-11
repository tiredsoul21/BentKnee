#ifndef TYPEDEFINITIONS_H
#define TYPEDEFINITIONS_H

#include <string>

namespace TypeDefinitions {

    enum class AverageTypes {
        null = 0,
        simpleMovingAverage = 1,
        linearWeightedAverage = 2,
        exponentialMovingAverage = 3
    };



    enum class PriceType {
        Close = 0,
        Open = 1,
        Low = 2,
        High = 3,
        Adjusted = 4
    };

    enum class TD_PeriodType {
        day = 0,
        month = 1,
        year = 2,
        ytd = 3

    };

    enum class TD_FrequencyType {
        minute = 0,
        daily = 1,
        weekly = 2,
        monthly = 3

    };

    // TD Period Type Map //
    /*--------------------------------------------------------------
    * Description - takes and enumerated value and returns the string
    *
    * Output(s):
    *   string - representing the enumeration desired
    *
    * Input(s):
    *   TD_PeriodType - an enumeration of periods accepted by TD
    ---------------------------------------------------------------*/
    std::string periodTypeMap(TD_PeriodType);

    // TD Period Type Map //
    /*--------------------------------------------------------------
    * Description - takes and enumerated value and returns the string
    *
    * Output(s):
    *   string - representing the enumeration desired
    *
    * Input(s):
    *   TD_FrequencyType - an enumeration of frequencies accepted by TD
    ---------------------------------------------------------------*/
    std::string frequencyTypeMap(TD_FrequencyType);
}


#endif