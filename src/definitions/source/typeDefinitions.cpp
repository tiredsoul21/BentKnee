#ifndef TYPEDEFINITIONS_H
#include "typeDefinitions.h"
#endif

std::string TypeDefinitions::periodTypeMap(TD_PeriodType period)
{
    switch (period) {
        case TD_PeriodType::day:
            return "day";
        case TD_PeriodType::month:
            return "month";
        case TD_PeriodType::year:
            return "year";
        case TD_PeriodType::ytd:
            return "ytd";
        default:
            return "BAD";
    }
}

std::string TypeDefinitions::frequencyTypeMap(TD_FrequencyType frequency)
{
    switch (frequency) {
        case TD_FrequencyType::minute:
            return "minute";
        case TD_FrequencyType::daily:
            return "daily";
        case TD_FrequencyType::weekly:
            return "weekly";
        case TD_FrequencyType::monthly:
            return "monthly";
        default:
            return "BAD";
    }
}
