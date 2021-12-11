/* 
 *  This class is a pure super class, one for which contains standardized
 *  class concepts that should be employed across all objects for uniformity
 */

#ifndef CLASSTEMPLATE_H
#define CLASSTEMPLATE_H

#include <string>

class ClassTemplate
{
public: // Public Methods

    /*********************** CONSTRUCTORS ******************************/

     // Default Constructor //
    ClassTemplate();

    /*********************** DESTRUCTORS *******************************/

    // Default Destructor //
    ~ClassTemplate();

    /************************ FUNCTIONAL *******************************/

    // Error Found //
    /*--------------------------------------------------------------
     * Description - Returns true if error happened since last clear.
     * Input(s):
     *   Void
     * Output(s):
     *   bool - returns true if length of string > 0
     ---------------------------------------------------------------*/
    bool errorFound();

    // Clear Error //
    /*--------------------------------------------------------------
     * Description - Clears the error string ( and errorFound() )
     * Input(s):
     *   Void
     * Output(s):
     *   Void
     ---------------------------------------------------------------*/
    void clearError();

    // Error String //
    /*--------------------------------------------------------------
     * Description - Returns last error strings written to object
     *   Manual clear necessary
     * Input(s):
     *   Void
     * Output(s):
     *   string - give error string currently held
     ---------------------------------------------------------------*/
    std::string errorString();

protected: //Protected Members

    // An error string used to communicate issues in handling.  
    // Size 0 implies no issues.
    std::string myErrorString;


};

#endif