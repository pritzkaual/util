/*
 * Handler.hpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#ifndef HANDLER_HPP_
#define HANDLER_HPP_

#include "XHandler.hpp"

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

#include "EClass.hpp"
#include "EDataType.hpp"
#include "EEnum.hpp"
#include "ENamedElement.hpp"
#include "EObject.hpp"
#include "EPackage.hpp"
#include "EStructuralFeature.hpp"


namespace persistence
{
struct UnresolvedReference
{
	inline UnresolvedReference ( std::string refName, std::shared_ptr<ecore::EObject> eObject, std::shared_ptr<ecore::EStructuralFeature> eStructuralFeature ) :
					refName( refName ),
					eObject( eObject ),
					eStructuralFeature( eStructuralFeature )
	{
	}

	std::string refName;
	std::shared_ptr<ecore::EObject> eObject;
	std::shared_ptr<ecore::EStructuralFeature> eStructuralFeature;
};
} /* namespace persistence */

namespace persistence
{
class Handler : public XHandler
{
public:
	Handler ();
	virtual ~Handler ();
	void deleteHandler (); // TODO find other way to del handler

	std::shared_ptr<ecore::EObject> getObjectByRef ( std::string ref );

	DOMDocument *getDOMDocument ();
	void setDOMDocument ( DOMDocument * doc );

	std::string getPrefix ();

	std::string extractType ( std::shared_ptr<ecore::EObject> obj ) const;

	void addToMap ( std::shared_ptr<ecore::EObject> object );

	void setCurrentObject ( std::shared_ptr<ecore::EObject> object );
  
	std::shared_ptr<ecore::EObject> getCurrentObject ( );

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
	void releaseObj ();

	int getNumOfChildNodes ();
	std::string getNextNodeName ();
	std::map<std::string, std::string> getAttributeList ();

	void addUnresolvedReference ( const std::string &name, std::shared_ptr<ecore::EObject> object, std::shared_ptr<ecore::EStructuralFeature> esf );

	void resolveReferences ();

private:

	DOMDocument *m_doc;
	DOMElement *m_currentElement;
	std::list<DOMNode *> m_currentElements;

	std::shared_ptr<ecore::EObject> m_rootObject;
	std::list<std::shared_ptr<ecore::EObject> > m_currentObjects;

	std::string m_rootPrefix;

	std::map<std::string, std::shared_ptr<ecore::EObject>> m_refToObject_map;
	std::list<persistence::UnresolvedReference> m_unresolvedReferences;

	void addChild ( DOMElement *parent_elem, DOMElement *child_elem );
	std::string extractReference ( std::shared_ptr<ecore::EObject> to ) const;
}
;

} /* namespace persistence */

#endif /* HANDLER_HPP_ */
