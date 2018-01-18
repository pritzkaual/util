/*
 * SaveHandler.hpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#ifndef SaveHandler_HPP_
#define SaveHandler_HPP_

#include "XSaveHandler.hpp"
#include "HandlerHelper.hpp"

#include <map>
#include <list>
#include <string>
#include <set>
#include <exception>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#include "xerces/XStr.hpp"
#include "xerces/WStr.hpp"

#include "boost/exception/to_string.hpp"

#include "EObject.hpp"


namespace persistence
{
class SaveHandler : public XSaveHandler
{
public:
	SaveHandler ();
	virtual ~SaveHandler ();
	void deleteHandler (); // TODO find other way to del SaveHandler

	DOMDocument *getDOMDocument ();
	std::string getPrefix ();
	void setRootObject ( std::shared_ptr<ecore::EObject> object );

	std::string extractType ( std::shared_ptr<ecore::EObject> obj ) const;

	bool createRootNode ( const std::string& name, const std::string& ns_uri );
	bool createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri );
	bool createRootNode ( const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype );
	bool createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype );

	bool createAndAddElement ( const std::string& name );

	template<typename T>
	void addAttribute ( const std::string& name, T value )
	{
		addAttribute( name, boost::to_string( value ) );
	}
	void addAttribute ( const std::string &name, bool value );
	void addAttribute ( const std::string &name, const std::string& value );

	void addReference ( const std::string &name, std::shared_ptr<ecore::EObject> object );
	void addReferences ( const std::string &name, std::shared_ptr<ecore::EObject> object );

	void release ();

private:

	DOMDocument *m_doc;
	DOMElement *m_currentElement;
	std::list<DOMNode *> m_currentElements;

	std::shared_ptr<ecore::EObject> m_rootObject;

	std::string m_rootPrefix;

	void addChild ( DOMElement *parent_elem, DOMElement *child_elem );
}
;

} /* namespace persistence */

#endif /* SaveHandler_HPP_ */
