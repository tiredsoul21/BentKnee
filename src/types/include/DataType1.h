/* 
 *  This is a type that stores a singleton data object and a bool indicating 
 *  technical maturity
 */

#ifndef DATATYPE1_H
#define DATATYPE1_H

#include <string>

class DataType1
{
public: // Public Methods
    
    /*********************** CONSTRUCTORS ******************************/

    DataType1(double datum, bool mature);

    /************************ SETTERS *******************************/
    
    // Set Data Name //
    /*--------------------------------------------------------------
     * Description - Set the data's common name
     * Input(s):
     *   string - The data's name
     * Output(s):
     *   void
     ---------------------------------------------------------------*/
    void setDataName(std::string name);
    
    /************************ GETTERS *******************************/
    
    // Get Data //
    /*--------------------------------------------------------------
     * Description - Gets the value stored in the object
     * Input(s):
     *   Void
     * Output(s):
     *   float - the indicator for this period
     ---------------------------------------------------------------*/
    double getData();

    // Get Data Name //
    /*--------------------------------------------------------------
     * Description - Get the data's common name
     * Input(s):
     *   void
     * Output(s):
     *   string - The data's name
     ---------------------------------------------------------------*/
    std::string getDataName();

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
    bool isDataSet();
    
private: // Private Members
    
    // Value for the stored indicator //
    double myData;
    
    // Data's common name
    std::string myDataName;
    
    bool dataSet = false;
    
    // Indicate flagging if data is mature //
    bool mature;
};


#endif