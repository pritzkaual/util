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

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#include "xerces/XStr.hpp"
#include "xerces/WStr.hpp"
#include "xerces/DOMTreeErrorReporter.hpp"
//#include "xerces/DOMPrintFilter.hpp"
//#include "xerces/DOMPrintErrorHandler.hpp"

#include <exception>
#include "boost/exception/to_string.hpp"

#include "EcoreModelPlugin.hpp"
#include "PluginFramework.hpp"

#include "EClass.hpp"
#include "EDataType.hpp"
#include "ENamedElement.hpp"
#include "EObject.hpp"
#include "EPackage.hpp"
#include "EStructuralFeature.hpp"

#include "Option.hpp"

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

	//void handle ( std::shared_ptr<ecore::EObject> element, std::set<std::string> options );

	//std::map<std::string, std::shared_ptr<ecore::EObject>> get_IdToObject_Map ();
	//std::map<std::shared_ptr<ecore::EObject>, std::string> get_ObjectToId_Map ();

	//std::string get_Id ( std::shared_ptr<ecore::EObject> object );

	void setMetaMetaPackage( std::shared_ptr<ecore::EPackage> metaMetaPackage );
	std::shared_ptr<ecore::EPackage> getMetaMetaPackage( );

	std::shared_ptr<ecore::EObject> get_Object ( std::string id );

	DOMDocument *getDOMDocument ();
	void setDOMDocument ( DOMDocument * doc );

	std::string getPrefix ();
	std::string extractType ( std::shared_ptr<ecore::EObject> obj ) const;

	//void addToMap ( std::shared_ptr<ecore::EObject> object );
	void addToMap ( std::shared_ptr<ecore::EObject> object );

	void setRootObj ( std::shared_ptr<ecore::EObject> object );
	void setCurrentObj ( std::shared_ptr<ecore::EObject> object );
  
	//template<typename T>
	std::shared_ptr<ecore::EObject> getCurrentObj ( );

	bool createRootNode ( const std::string& name, const std::string& ns_uri );
	bool createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri );
	bool createRootNode ( const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype );
	bool createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype );

	bool createAndAddElement ( const std::string& name );

	/*
	 void addAttribute ( const std::string& name, float value );
	 void addAttribute ( const std::string& name, double value );
	 void addAttribute ( const std::string& name, long double value );

	 void addAttribute ( const std::string& name, int value );
	 void addAttribute ( const std::string& name, long int value );
	 void addAttribute ( const std::string& name, long long int value );
	 void addAttribute ( const std::string& name, unsigned int value );
	 void addAttribute ( const std::string& name, unsigned long int value );
	 void addAttribute ( const std::string& name, unsigned long long int value );
	 */
	template<typename T>
	void addAttribute ( const std::string& name, T value )
	{
		addAttribute( name, boost::to_string( value ) );
	}
	void addAttribute ( const std::string &name, bool value );
	void addAttribute ( const std::string &name, const std::string& value );
	//void addAttribute_xsi_type ( const std::string& value );

	void addReference ( const std::string &name, std::shared_ptr<ecore::EObject> object );

	template<typename T>
	void addReference ( const std::string &name, std::shared_ptr<Bag<T> > objects )
	{
		if ( objects->size() )
		{
			for ( std::shared_ptr<T> object : *objects )
			{
				addReference( name, object );
			}
		}
	}

	void release ();
	void releaseObj ();

	int countChildElements ( DOMNode *n, bool printOutEncounteredEles );

	int getNumOfChildren ();
	std::string getNextNodeName ();
	std::map<std::string, std::string> getAttributeList ();

	void addUnresolvedReference ( const std::string &name, std::shared_ptr<ecore::EObject> object, std::shared_ptr<ecore::EStructuralFeature> esf );

	bool resolveReferences ();

private:

	DOMDocument *m_doc;

	DOMElement *m_current_elem;
	std::list<DOMNode *> m_element_list;

	std::shared_ptr<ecore::EObject> m_root_obj;
	std::shared_ptr<ecore::EObject> m_current_obj;

	std::shared_ptr<ecore::EPackage> m_metaMetaPackage;

	std::set<std::string> m_options;

	std::string m_rootPrefix;

	std::map<std::string, std::shared_ptr<ecore::EObject>> m_Id_to_Object;
//	std::map<std::shared_ptr<ecore::EObject>, std::string> m_Object_to_Id;
	std::list<persistence::UnresolvedReference> m_unresolvedReferences;

	void addChild ( DOMElement *parent_elem, DOMElement *child_elem );

	std::string extractReference ( std::shared_ptr<ecore::EObject> to ) const;
	std::string create_Hash ( std::shared_ptr<ecore::EObject> object );
}
;

} /* namespace persistence */

#endif /* HANDLER_HPP_ */
