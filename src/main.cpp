/*
 * For now, this is used for testing and development of components.
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

#include "PriceContainer.h"
#include "ChaikinMoneyFlow.h"

void parseCSV(PriceContainer* container);

int main()
{
    std::string inputFormat = "YYYYMMDD hhmmss";
    std::string displayFormat = "YYYY-MM-DD";
    std::string goodDateStr = "02222000 000000";
    std::cout << "Start-------------------" << std::endl;
    PriceContainer container;
    container.setInputDateFormat(&inputFormat);
    container.setDisplayDateFormat(&displayFormat);
    
    std::cout << "Parse-------------------" << std::endl;
    parseCSV(&container);
    ChaikinMoneyFlow cmf = ChaikinMoneyFlow(&container, 21);
    
    for (auto it = cmf.begin(); it !=  cmf.end(); it++)
    {
        std::cout << std::to_string(it->first) << "\t";
        std::cout << std::to_string(it->second.getChaikinMoneyFlow());
        std::cout << std::endl;
    }
    
    std::cout << "Report------------------" << std::endl;
    
    
    std::cout << "Error-------------------" << std::endl;
    if (container.errorFound())
        std::cout << container.errorString();
    
    return 0;
}

void parseCSV(PriceContainer* container)
{
    std::ifstream  data("C:/Users/derri/Downloads/QQQ.csv");
    std::string line;
    
    bool isHeader=true;
    while(std::getline(data,line))
    {
        if (!isHeader)
        {
            std::stringstream lineStream(line);
            std::string cell;
            std::string::size_type sz;

            std::string tempStr, tempDate, date;
            std::getline(lineStream,tempDate,',');

            std::stringstream dateStream(tempDate);
            std::getline(dateStream,tempStr,'-');
            date += std::string(2 - std::min(2, (int)tempStr.length()), '0') + tempStr;
            std::getline(dateStream,tempStr,'-');
            date += std::string(2 - std::min(2, (int)tempStr.length()), '0') + tempStr;
            std::getline(dateStream,tempStr,'-');
            date += tempStr+ " 000000";
            
            std::getline(lineStream,cell,',');
            float open = std::stof(cell, &sz);
            std::getline(lineStream,cell,',');
            float high = std::stof(cell, &sz);
            std::getline(lineStream,cell,',');
            float low = std::stof(cell, &sz);
            std::getline(lineStream,cell,',');
            float close = std::stof(cell, &sz);
            std::getline(lineStream,cell,',');
            float adjusted = std::stof(cell, &sz);
            std::getline(lineStream,cell,',');
            int volume = std::stoi(cell, &sz);
            container->add(&date, open, close, high, low, adjusted, volume, 'd');
        }
        isHeader = false;
    }
};