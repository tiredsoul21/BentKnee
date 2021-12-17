/* 
 *  This is a technicals type that stores the chaikin money flow calculation
 *  and a bool indicating technical maturity
 */

#ifndef CHAIKINMONEYFLOWTYPE_H
#define CHAIKINMONEYFLOWTYPE_H

class ChaikinMoneyFlowType
{
public: // Public Methods
    
    /*********************** CONSTRUCTORS ******************************/

    ChaikinMoneyFlowType(float cmf, bool mature);

    /*********************** DESTRUCTORS *******************************/

    ~ChaikinMoneyFlowType();

    /************************ FUNCTIONAL *******************************/
    
    // Get ChaikinMoneyFlow //
    /*--------------------------------------------------------------
     * Description - Gets the value stored in the indicator for this
     *   object
     * Input(s):
     *   Void
     * Output(s):
     *   float - the indicator for this period
     ---------------------------------------------------------------*/
    float getChaikinMoneyFlow();
    
    // Is Mature //
    /*--------------------------------------------------------------
     * Description - Returns if the calculation has reached maturation
     * Input(s):
     *   Void
     * Output(s):
     *   bool - true = is mature
     ---------------------------------------------------------------*/
    bool isMature();
    
private: // Private Members
    
    // Value for the stored indicator //
    float chaikinMoneyFlow;
    
    bool mature;
};


#endif