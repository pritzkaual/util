/*
 * XStr.h
 *
 *  Created on: 28.06.2017
 *      Author: Alexander
 */

#ifndef WSTR_HPP_
#define WSTR_HPP_

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMLString.hpp>
#include <string>

XERCES_CPP_NAMESPACE_USE

#define W(str) WStr(str).unicodeForm()

// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of char* data to XMLCh data.
// ---------------------------------------------------------------------------
class WStr
{
public:
	WStr ( const XMLCh* const toTranscode );
	WStr ( const WStr& other );
	~WStr ();

	const std::string unicodeForm () const;

private:

	char* m_local;
};
/*
 std::ostream& operator<< ( std::ostream& target, const WStr& toDump )
 {
 target << toDump.unicodeForm();
 return target;
 }
 */
#endif /* XSTR_HPP_ */
