/*
 * For now, this is used for testing and development of components.
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

#include "PriceContainer.h"

void parseCSV(PriceContainer* container);

int main()
{
    std::string inputFormat = "MMDDYYYY hhmmss";
    std::string displayFormat = "YYYY-MM-DD";
    std::string badDateStr1 = "02221985 000000";
    std::string badDateStr2 = "02222050 000000";
    std::string goodDateStr = "02222000 000000";
    std::cout << "Start-------------------" << std::endl;
    PriceContainer* container = new PriceContainer();
    container->setInputDateFormat(&inputFormat);
    container->setDisplayDateFormat(&displayFormat);
    
    std::cout << "Parse-------------------" << std::endl;
    parseCSV(container);
    
    std::cout << "Report------------------" << std::endl;
    auto iterBad = container->getIter(&badDateStr1);
    auto iterOne = container->getIter(&goodDateStr);
    auto iterTwo = container->getIter(14463);
    auto iterThree = container->getBeginIter();
    
    // Testing bad sets of getIter
    container->getIter(&badDateStr2); //bad
    container->getIter(1234432); //bad
    
    // Testing of Iter && getDatenum
    std::cout << container->getDatenum(iterBad) << "\n"; //bad
    std::cout << container->getDatenum(iterOne) << "\n"; //good
    std::cout << container->getDatenum(iterTwo) << "\n";//good
    std::cout << container->getDatenum(iterThree) << "\n";//good
    std::cout << container->getDatenum(&badDateStr1) << std::endl; //bad
    std::cout << container->getDatenum(&goodDateStr) << std::endl; //good
    std::cout << "-----------------------------------------\n";
    std::cout << container->getDateStr(14662) << std::endl; //good
    std::cout << container->getDateStr(iterOne) << std::endl; //good
    std::cout << "-----------------------------------------\n";
    std::cout << container->getCustomDateString(14662) << std::endl; //good
    std::cout << container->getCustomDateString(&goodDateStr) << std::endl; //good
    
    std::cout << "-----------------------------------------\n";
    std::cout << container->getLow(iterBad)<< std::endl; //bad
    std::cout << container->getHigh(iterBad)<< std::endl; //bad
    std::cout << container->getOpen(iterBad)<< std::endl; //bad
    std::cout << container->getClose(iterBad)<< std::endl; //bad
    std::cout << container->getAdjusted(iterBad)<< std::endl; //bad
    std::cout << container->getVolume(iterBad)<< std::endl; //bad
    std::cout << container->getIncrement(iterBad)<< std::endl; //bad
    std::cout << "-----------------------------------------\n";
    std::cout << container->getLow(iterOne) << std::endl; //good
    std::cout << container->getHigh(iterOne) << std::endl; //good
    std::cout << container->getOpen(iterOne) << std::endl; //good
    std::cout << container->getClose(iterOne) << std::endl; //good
    std::cout << container->getAdjusted(iterOne) << std::endl; //good
    std::cout << container->getVolume(iterOne) << std::endl; //good
    std::cout << container->getIncrement(iterOne) << std::endl; //good
    std::cout << "-----------------------------------------\n";
    std::cout << container->getLow(&goodDateStr) << std::endl; //good
    std::cout << container->getHigh(&goodDateStr) << std::endl; //good
    std::cout << container->getOpen(&goodDateStr) << std::endl; //good
    std::cout << container->getClose(&goodDateStr) << std::endl; //good
    std::cout << container->getAdjusted(&goodDateStr) << std::endl; //good
    std::cout << container->getVolume(&goodDateStr) << std::endl; //good
    std::cout << container->getIncrement(&goodDateStr) << std::endl; //good
    std::cout << "-----------------------------------------\n";
    std::cout << container->getLow(11009) << std::endl; //good
    std::cout << container->getHigh(11009) << std::endl; //good
    std::cout << container->getOpen(11009) << std::endl; //good
    std::cout << container->getClose(11009) << std::endl; //good
    std::cout << container->getAdjusted(11009) << std::endl; //good
    std::cout << container->getVolume(11009) << std::endl; //good
    std::cout << container->getIncrement(11009) << std::endl; //good
    
    
    
    std::cout << "Error-------------------" << std::endl;
    if (container->errorFound())
        std::cout << container->errorString();
    
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
            std::getline(dateStream,tempStr,'/');
            date += std::string(2 - std::min(2, (int)tempStr.length()), '0') + tempStr;
            std::getline(dateStream,tempStr,'/');
            date += std::string(2 - std::min(2, (int)tempStr.length()), '0') + tempStr;
            std::getline(dateStream,tempStr,'/');
            date += tempStr + " 000000";
            
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
            container->add(&date, open, high, low, close, adjusted, volume, 'd');
        }
        isHeader = false;
    }
};