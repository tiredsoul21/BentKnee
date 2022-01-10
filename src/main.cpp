/*
 * For now, this is used for testing and development of components.
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

#include "Definitions.h"
#include "PriceContainer.h"
#include "ChaikinMoneyFlow.h"
#include "SmoothingEngine.h"
#include "DerivativeEngine.h"
#include "DataType3.h"

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
    SmoothingEngine mySmoothingEngine = SmoothingEngine(Definitions::SmoothingType::Exponential);
    DerivativeEngine myDerivEngine = DerivativeEngine();
    DerivativeEngine myDerivEngine2 = DerivativeEngine();
    myDerivEngine2.setDerivativeStep(2);
    mySmoothingEngine.setHistoricalSig(.7);
    
    std::ofstream myfile;
    myfile.open ("C:/Users/derri/Desktop/QQQ.csv");
    for (auto it = cmf.begin(); it !=  cmf.end(); it++)
    {
        double smoothCmf = mySmoothingEngine.nextEntry(it->second.getData());
        DataType3 myDerivs = myDerivEngine.nextEntry(smoothCmf);
        DataType3 myDerivs2 = myDerivEngine2.nextEntry(smoothCmf);
        
        myfile << it->second.getData();
        myfile << ", " << smoothCmf << ", " ;
        if (myDerivs.isData1Set())
            myfile << myDerivs.getData1() << ", ";
        if (myDerivs.isData2Set())
            myfile << myDerivs.getData2() << ", ";
        if (myDerivs.isData3Set())
            myfile << myDerivs.getData3() << ", ";
        if (myDerivs2.isData1Set())
            myfile << myDerivs2.getData1() << ", ";
        if (myDerivs2.isData2Set())
            myfile << myDerivs2.getData2() << ", ";
        if (myDerivs2.isData3Set())
            myfile << myDerivs2.getData3();
        myfile << "\n";
    }
    myfile.close();
    
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