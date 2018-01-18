/*
 * LoadHandler.hpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#ifndef LoadHandler_HPP_
#define LoadHandler_HPP_

#include "XLoadHandler.hpp"

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
class LoadHandler : public XLoadHandler
{
public:
	LoadHandler ();
	virtual ~LoadHandler ();
	void deleteHandler (); // TODO find other way to del LoadHandler

	std::shared_ptr<ecore::EObject> getObjectByRef ( std::string ref );

	DOMDocument *getDOMDocument ();
	void setDOMDocument ( DOMDocument * doc );

	std::string getPrefix ();

	std::string extractType ( std::shared_ptr<ecore::EObject> obj ) const;

	void addToMap ( std::shared_ptr<ecore::EObject> object );

	void setCurrentObject ( std::shared_ptr<ecore::EObject> object );
	std::shared_ptr<ecore::EObject> getCurrentObject ( );

	void release ();

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

	std::string extractReference ( std::shared_ptr<ecore::EObject> to ) const;
}
;

} /* namespace persistence */

#endif /* LoadHandler_HPP_ */
