/* 
 *  This class is the engine which generates analytic data, and maintains needed
 *  data for history.  This class in particular maintains historic data in order
 *  to simplify rolling sum calculations.
 */

#ifndef SMOOTHINGENGINE_H
#define SMOOTHINGENGINE_H

#ifndef CLASSTEMPLATE_H
#include "ClassTemplate.h"
#endif

#ifndef DEFINITIONS_H
#include "Definitions.h"
#endif

#include <cmath>

class SmoothingEngine: public ClassTemplate
{
    
public: // Public Methods
    
    /*********************** CONSTRUCTORS ******************************/

    // Default //
    SmoothingEngine();
    
    // Sets smoothing type in initialization //
    SmoothingEngine(Definitions::SmoothingType smoothingType);

    /*********************** DESTRUCTORS *******************************/

    ~SmoothingEngine();
        
    /************************ FUNCTIONAL *******************************/
    
    // Next Entry //
     /*--------------------------------------------------------------
      * Description - A wrapper function the limits and simplifies data
      *   entry into the template
      * Input(s) - Overload 1:
	  *   float - data point to add to average
      * Output(s):
      *   float - the average value calculation
      * Input(s) - Overload 2:
	  *   double - data point to add to average
      * Output(s):
      *   double - the average value calculation
      ---------------------------------------------------------------*/
    float nextEntry(float temp);
    double nextEntry(double temp);
    
    /************************ SETTERS *******************************/
    
    // Set Average Size //
    /*--------------------------------------------------------------
     * Description - This is a setter function for the average size.
     *   Must be greater than 0, but max is MAX_SIZE.
     * Input(s):
     *   int - the size of the average calculation.
     * Output(s):
     *   void
     ---------------------------------------------------------------*/    
    void setAverageSize(int size);
    
    // Set Smoothing Type //
    /*--------------------------------------------------------------
     * Description - This function configures the smoothing
     *   type used.  This will clear out any saved information.
     * Input(s):
     *   Definitions::SmoothingType - the smoothing type
     * Output(s):
     *   void
     ---------------------------------------------------------------*/    
    void setSmoothingType(Definitions::SmoothingType type);
    
    // Set Historical Significance //
    /*--------------------------------------------------------------
     * Description - The setter function for setting the historical
     *   significance.
     * Input(s):
     *   float - the significance value (0 <= x <= 1)
     * Output(s):
     *   void
     ---------------------------------------------------------------*/    
    void setHistoricalSig(float sig);
    
    // Set Trend Significance //
    /*--------------------------------------------------------------
     * Description - The setter function for setting the trend 
     *   significance.
     * Input(s):
     *   float - the significance value (0 <= x <= 1)
     * Output(s):
     *   void
     ---------------------------------------------------------------*/    
    void setTrendSig(float sig);
    
    // Set Seasonal Significance //
    /*--------------------------------------------------------------
     * Description - Setter function for setting the seasonal 
     *   significance. 
     * Input(s):
     *   float - the significance value (0 <= x <= 1)
     * Output(s):
     *   void
     ---------------------------------------------------------------*/    
    void setSeasonalSig(float sig);

    // Set Periodicity //
    /*--------------------------------------------------------------
     * Description - Setter function for the seasonal periodicity. 
     * Input(s):
     *   int - the period for the seasonal data
     * Output(s):
     *   void
     ---------------------------------------------------------------*/    
    void setPeriod(int period);
    
    /************************ GETTERS *******************************/
    
    // Get Average Size //
    /*--------------------------------------------------------------
     * Description - This is a getter function for the average size.
     * Input(s):
     *   void
     * Output(s):
     *   int - the size of the average calculation.
     ---------------------------------------------------------------*/    
    int getAverageSize();
    
    // Get Smoothing Type //
    /*--------------------------------------------------------------
     * Description - This function shows the smoothing type used.
     * Input(s):
     *   void
     * Output(s):
     *   Definitions::SmoothingType - the smoothing type
     ---------------------------------------------------------------*/    
    Definitions::SmoothingType getSmoothingType();
    
    // Get Historical Significance //
    /*--------------------------------------------------------------
     * Description - Getter function for the historic significance. 
     * Input(s):
     *   void
     * Output(s):
     *   float - the significance value (0 <= x <= 1)
     ---------------------------------------------------------------*/    
    float getHistoricSig();
        
    // Get Trend Significance //
    /*--------------------------------------------------------------
     * Description - Getter function for the trend significance. 
     * Input(s):
     *   void
     * Output(s):
     *   float - the significance value (0 <= x <= 1)
     ---------------------------------------------------------------*/    
    float getTrendSig();
        
    // Get Seasonal Significance //
    /*--------------------------------------------------------------
     * Description - Getter function for the seasonal significance. 
     * Input(s):
     *   void
     * Output(s):
     *   float - the significance value (0 <= x <= 1)
     ---------------------------------------------------------------*/    
    float getSeasonalSig();
    
    // Get Periodicity //
    /*--------------------------------------------------------------
     * Description - Getter function for the seasonal periodicity. 
     * Input(s):
     *   void
     * Output(s):
     *   int - the period for the seasonal data
     ---------------------------------------------------------------*/    
    int getPeriod();
    
private: // Private Members
    
    // This is a max for many elements in the function, such as period & average
    const static int MAX_SIZE = 1000;
    
    // Record if the indicator has reach fully maturity
    bool isMature = false;
    
    // Integer that counts to maturity, also serves to index
    int mature = 0;
    
    // Storage for historic volumes.  Max of MAX_SIZE.  These numbers are maintained
    // In order to reduce computation time (no total sum every iteration), increases
    // memory footprint slightly however.
    double data[MAX_SIZE];
    
    // Variables to maintain memory between entries
    double dataSum = 0;
    double historicLast;
    double trendLast;
    
    // Average settings - sets length of average calculation, this is also used
    // as a basis for maturity calculations
    int averageSize = 20;
    
    // Historic significance constant. 0 weights all significance to the
    // current data point.  1 Weighs all significance to historic data.
    float historicSig = 0.8;
    
    // Trend significance constant. 0 weights all significance to the
    // recent trend (This becomes approx. exponential).  1 Weighs all significance 
    // to historic trend trend.
    float trendSig = 0.8;
    
    // Seasonal significance constant. 0 weights all significance to the
    // recent seasonality (This becomes approx double exponential).  1 Weighs all
    // significance historic seasonal data.
    float seasonalSig = 0.8;

    // Integer for seasonality, this is number of data per cycle.
    int periodicity = 20;
    
    // My selection for smoothing type
    Definitions::SmoothingType mySmoothingType = Definitions::SmoothingType::MovingAverage;
    
private: // Private Methods
    
    /************************ FUNCTIONAL *******************************/
    
    // Map Entry //
    /*--------------------------------------------------------------
     * Description - Maps the entry of data to the correct smoothing
     *   function, returns the calculated value
     * Input(s):
	 *   T - data point to add to average
     * Output(s):
     *   T - the average value calculation
     ---------------------------------------------------------------*/
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    T mapEntry(T datum);
    
    // Exponential Smoothing //
    /*--------------------------------------------------------------
     * Description - A smoothing function that weights between historic
     *   data and current data point.  This average can favor past or 
     *   more recent data  depending on weight.
     * Input(s):
	 *   T - data point to add to average
     * Output(s):
     *   T - the average value calculation
     ---------------------------------------------------------------*/
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    T exponential(T datum);
    
    // Moving Average //
    /*--------------------------------------------------------------
     * Description - A smoothing function that averages the last n
     *   data points, where each datum has equal weight in the 
     *   calculation.  This average can be easily manipulated by 
     *   dramatic fluctuations data.
     * Input(s):
	 *   T - data point to add to average
     * Output(s):
     *   T - the average value calculation
     ---------------------------------------------------------------*/
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    T movingAverage(T datum);
    
    // Double Exponential //
    /*--------------------------------------------------------------
     * Description - A smoothing function that implements two rounds of
     *   exponential smoothing.  This smoothing should be used when a
     *   trend is expected, and should also not be used under a condition
     *   of seasonality.
     * Input(s):
	 *   T - data point to add to average
     * Output(s):
     *   T - the average value calculation
     ---------------------------------------------------------------*/
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    T doubleExponential(T datum);
    
    // Holt Winters //
    /*--------------------------------------------------------------
     * Description - A smoothing function with three terms.  This
     *   method can account for a trend and seasonality or periods.
     *   for data before the first complete period, we use double
     *   exponential.
     * Input(s):
	 *   T - data point to add to average
     * Output(s):
     *   T - the average value calculation
     ---------------------------------------------------------------*/
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    T holtWinters(T datum);
    
};

#endif