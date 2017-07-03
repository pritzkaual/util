/*
 * XStr.cpp
 *
 *  Created on: 28.06.2017
 *      Author: Alexander
 */

#include "XStr.hpp"



XStr::XStr(const char* const toTranscode)
{
    // Call the private transcoding method
    fUnicodeForm = XMLString::transcode(toTranscode);
}


XStr::~XStr ()
{
    XMLString::release(&fUnicodeForm);
}


const XMLCh* XStr::unicodeForm() const
{
	return fUnicodeForm;
}

