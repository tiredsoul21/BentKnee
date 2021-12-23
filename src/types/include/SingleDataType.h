/* 
 *  This is a type that stores a singleton data object and a bool indicating 
 *  technical maturity
 */

#ifndef SINGLEDATATYPE_H
#define SINGLEDATATYPE_H

#include <string>

class SingleDataType
{
public: // Public Methods
    
    /*********************** CONSTRUCTORS ******************************/

    SingleDataType(float datum, bool mature);

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
    float getData();

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
    
private: // Private Members
    
    // Value for the stored indicator //
    float myData;
    
    // Data's common name
    std::string myDataName;
    
    // Indicate flagging if data is mature //
    bool mature;
};


#endif