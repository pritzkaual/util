/*
 * XStr.h
 *
 *  Created on: 28.06.2017
 *      Author: Alexander
 */

#ifndef XSTR_H_
#define XSTR_H_


#include <xercesc/util/XMLString.hpp>


namespace testXerces {


using namespace xercesc_3_1;



// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of char* data to XMLCh data.
// ---------------------------------------------------------------------------
class XStr
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XStr(const char* const toTranscode);

    ~XStr();


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const XMLCh* unicodeForm() const;

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fUnicodeForm
    //      This is the Unicode XMLCh format of the string.
    // -----------------------------------------------------------------------
    XMLCh*   fUnicodeForm;
};


} /* namespace testXerces */

//#define X(str) XStr(str).unicodeForm()


#endif /* XSTR_H_ */
