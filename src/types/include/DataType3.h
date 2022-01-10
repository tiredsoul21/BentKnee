/* 
 *  This is a type that stores a singleton data objects and a bool indicating 
 *  technical maturity
 */

#ifndef DATATYPE3_H
#define DATATYPE3_H

#include <string>

class DataType3
{
public: // Public Methods
    
    /*********************** CONSTRUCTORS ******************************/
    DataType3();
    DataType3(double datum1, bool mature);
    DataType3(double datum1, double datum2, bool mature);
    DataType3(double datum1, double datum2, double datum3, bool mature);

    /************************ SETTERS *******************************/
    
    // Set Data Name //
    /*--------------------------------------------------------------
     * Description - Set the data's common name
     * Input(s):
     *   string - The data's name
     * Output(s):
     *   void
     ---------------------------------------------------------------*/
    void setData1Name(std::string name);
    void setData2Name(std::string name);
    void setData3Name(std::string name);
    void setDataName(std::string name1, std::string name2, std::string name3);
    
    /************************ GETTERS *******************************/
    
    // Get Data //
    /*--------------------------------------------------------------
     * Description - Gets the value stored in the object
     * Input(s):
     *   Void
     * Output(s):
     *   float - the indicator for this period
     ---------------------------------------------------------------*/
    double getData1();
    double getData2();
    double getData3();

    // Get Data Name //
    /*--------------------------------------------------------------
     * Description - Get the data's common name
     * Input(s):
     *   void
     * Output(s):
     *   string - The data's name
     ---------------------------------------------------------------*/
    std::string getData1Name();
    std::string getData2Name();
    std::string getData3Name();

    // Is Mature //
    /*--------------------------------------------------------------
     * Description - Returns if the data element has reached maturation
     * Input(s):
     *   Void
     * Output(s):
     *   bool - true = is mature
     ---------------------------------------------------------------*/
    bool isMature();
    
    // Is Data Set //
    /*--------------------------------------------------------------
     * Description - Returns if the data element has been set
     * Input(s):
     *   Void
     * Output(s):
     *   bool - true = is set
     ---------------------------------------------------------------*/   
    bool isData1Set();
    bool isData2Set();
    bool isData3Set();
    
private: // Private Members
    
    // Value for the stored indicator //
    double myData1;
    double myData2;
    double myData3;
    
    // Data's common name
    std::string myData1Name;
    std::string myData2Name;
    std::string myData3Name;
    
    bool data1Set;
    bool data2Set;
    bool data3Set;
    
    // Indicate flagging if data is mature //
    bool mature;
};


#endif