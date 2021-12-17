/* 
 *  This class is the engine which generates the technical data, maintains needed
 *  data for history.  This class in particular maintains historic data in order
 *  to simplify rolling sum calculations.
 */

#ifndef CHAIKINMONEYFLOWENGINE_H
#define CHAIKINMONEYFLOWENGINE_H

#ifndef CLASSTEMPLATE_H
#include "ClassTemplate.h"
#endif

#ifndef CHAIKINMONEYFLOWTYPE_H
#include "ChaikinMoneyFlowType.h"
#endif

class ChaikinMoneyFlowEngine: public ClassTemplate
{
// 1. Money Flow Multiplier = [(Close  -  Low) - (High - Close)] /(High - Low) 
// 2. Money Flow Volume = Money Flow Multiplier x Volume for the Period
// 3. 20-period CMF = 20-period Sum of Money Flow Volume / 20 period Sum of Volume 
    
public: // Public Methods
    
    /*********************** CONSTRUCTORS ******************************/

    ChaikinMoneyFlowEngine();

    /*********************** DESTRUCTORS *******************************/

    ~ChaikinMoneyFlowEngine();

    /************************ FUNCTIONAL *******************************/
    
    // Next Entry //
    /*--------------------------------------------------------------
     * Description - This is the class's primary functional call to 
     *   calculate the indicator.  This will automatically track any
     *   required history data to continue calculation, only need to 
     *   feed data for the next data point.
     * Input(s):
     *   float - close price for the time period
     *   float - low price for the time period
     *   float - high price for the time period
     *   long - volume for the time period
     * Output(s):
     *   ChaikinMoneyFlowType - the indicator for this period
     ---------------------------------------------------------------*/    
    ChaikinMoneyFlowType nextEntry(float close, float low, 
                                   float high, long volume);
    
    // Set Average Size //
    /*--------------------------------------------------------------
     * Description - This is a setter function for the average size.
     *   For the Chaikin Money Flow, the standard size is 20 or 21...
     *   however, other average sizes can be used in experimentation.
     *   The max size is 50.
     * Input(s):
     *   int - the size of the average calculation.
     * Output(s):
     *   void
     ---------------------------------------------------------------*/    
    void setAverageSize(int size);
    
private: // Private Members
    
    // Record if the indicator has reach fully maturity
    bool isMature = false;
    
    // Integer that counts to maturity, also serves to index
    int mature = 0;
    
    // Storage for historic volumes.  Max of 50.  These numbers are maintained
    // In order to reduce computation time (no total sum every iteration), increases
    // memory footprint slightly however.
    double myVolumes[50];
    double myFlowVolumes[50];
    
    // Average settings - sets length of average calculation
    int averageSize = 20;
    
    // My Volume sums
    double volumeSum = 0, flowVolumeSum = 0; 
};

#endif