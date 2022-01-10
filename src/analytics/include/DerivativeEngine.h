/* 
 *  This class is the engine which generates analytic data, and maintains needed
 *  data for history.  This class in particular maintains historic data in order
 *  to simplify rolling sum calculations.
 */

#ifndef DERIVATIVEENGINE_H
#define DERIVATIVEENGINE_H

#ifndef CLASSTEMPLATE_H
#include "ClassTemplate.h"
#endif

#ifndef DATATYPE3_H
#include "DataType3.h"
#endif

#include <cmath>

class DerivativeEngine: public ClassTemplate
{
    
public: // Public Methods
    
    /*********************** CONSTRUCTORS ******************************/

    DerivativeEngine();

    /*********************** DESTRUCTORS *******************************/

    ~DerivativeEngine();
        
    /************************ FUNCTIONAL *******************************/
    
    // Next Entry //
     /*--------------------------------------------------------------
      * Description - A wrapper function the limits and simplifies data
      *   entry into the template
      * Input(s) - Overload 1:
	  *   float - data point to add to derivative chain
      * Output(s):
      *   double - the derivative calculations
      * Input(s) - Overload 2:
	  *   double - data point to add to derivative chain
      * Output(s):
      *   double - the derivative calculations
      * Input(s) - Overload 2:
	  *   int - data point to add to derivative chain
      * Output(s):
      *   double - the derivative calculations
      ---------------------------------------------------------------*/
    DataType3 nextEntry(float temp);
    DataType3 nextEntry(double temp);
    DataType3 nextEntry(int temp);
    
    // Clear Engine //
    /*--------------------------------------------------------------
     * Description - This resets the derivative engine.  This is
     *   accomplished simply by setting mature to 0
     * Input(s):
     *   void
     * Output(s):
     *   void
     ---------------------------------------------------------------*/    
    void clear();
    
    /************************ SETTERS *******************************/
    
    // Set Derivative Step Size //
    /*--------------------------------------------------------------
     * Description - This is a setter function for the derivative step
     *   size. Must be greater than 0, 1 is most common use.  Since time
     *   units are discrete, input is an int.  This only impacts the 
     *   first derivative.  This will clear stored data
     * Input(s):
     *   int - the size of the derivative calculation.
     * Output(s):
     *   void
     ---------------------------------------------------------------*/    
    void setDerivativeStep(int size);
    
    /************************ GETTERS *******************************/
    
    // Get Derivative Step Size //
    /*--------------------------------------------------------------
     * Description - This is a getter function for the derivative size.
     * Input(s):
     *   void
     * Output(s):
     *   int - the size of the derivative calculation.
     ---------------------------------------------------------------*/    
    int getDerivativeSize();
    
private: // Private Members
    
    // Integer that counts to maturity, also serves to index
    int mature = 0;
    
    // Variables populated to calculate derivatives
    double lastDatum;
    double firstDeriv1, firstDeriv2;
    double secondDeriv1, secondDeriv2;
    
    // Average settings - sets length of average calculation, this is also used
    // as a basis for maturity calculations
    int derivativeStep = 1;
    
private: // Private Methods
    
    /************************ FUNCTIONAL *******************************/
    
    // Calculate Derivatives //
    /*--------------------------------------------------------------
     * Description - A function that calculates the first, second and
     *   third order derivatives.  This considers step size.  
     * Input(s):
	 *   T - data point to add to average
     * Output(s):
     *   T - the average value calculation
     ---------------------------------------------------------------*/
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    DataType3 calculate(T datum);
    
};

#endif