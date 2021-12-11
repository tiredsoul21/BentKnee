/*
 * HelloWorld.cpp
 *
 *  Created on: Oct 21, 2021
 *      Author: derrick
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

#include "HistoryContainer.h"

void parseCSV(HistoryContainer* container);

int main()
{
    std::cout << "Start-------------------" << std::endl;
    HistoryContainer* container = new HistoryContainer();
    container->setInputDateFormat("MMDDYYYY hhmmss");
    container->setDisplayDateFormat("YYYY-MM-DD");
    
    std::cout << "Parse-------------------" << std::endl;
    parseCSV(container);
    
    std::cout << "Report------------------" << std::endl;
    auto iterBad = container->getIter("02221985 000000");
    auto iterOne = container->getIter("02222000 000000");
    auto iterTwo = container->getIter(14463);
    auto iterThree = container->getBeginIter();
    
    // Testing bad sets of getIter
    container->getIter("02222050 000000"); //bad
    container->getIter(1234432); //bad
    
    // Testing of Iter && getDatenum
    std::cout << container->getDatenum(iterBad) << "\n"; //bad
    std::cout << container->getDatenum(iterOne) << "\n"; //good
    std::cout << container->getDatenum(iterTwo) << "\n";//good
    std::cout << container->getDatenum(iterThree) << "\n";//good
    std::cout << container->getDatenum("02221985 000000") << std::endl; //bad
    std::cout << container->getDatenum("02222010 000000") << std::endl; //good
    std::cout << "-----------------------------------------\n";
    std::cout << container->getDateStr(14662) << std::endl; //good
    std::cout << container->getDateStr(iterOne) << std::endl; //good
    std::cout << "-----------------------------------------\n";
    std::cout << container->getCustomDateString(14662) << std::endl; //good
    std::cout << container->getCustomDateString("02222000 000000") << std::endl; //good
    
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
    std::cout << container->getLow("02222000 000000") << std::endl; //good
    std::cout << container->getHigh("02222000 000000") << std::endl; //good
    std::cout << container->getOpen("02222000 000000") << std::endl; //good
    std::cout << container->getClose("02222000 000000") << std::endl; //good
    std::cout << container->getAdjusted("02222000 000000") << std::endl; //good
    std::cout << container->getVolume("02222000 000000") << std::endl; //good
    std::cout << container->getIncrement("02222000 000000") << std::endl; //good
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

void parseCSV(HistoryContainer* container)
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
            container->add(date, open, high, low, close, adjusted, volume, 'd');
        }
        isHeader = false;
    }
};