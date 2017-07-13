/*
 * Handler.hpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#ifndef HANDLER_HPP_
#define HANDLER_HPP_

#include <map>
#include <string>
#include <set>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#include "xerces/XStr.hpp"
#include "xerces/DOMTreeErrorReporter.hpp"
//#include "xerces/DOMPrintFilter.hpp"
//#include "xerces/DOMPrintErrorHandler.hpp"

#include <exception>
#include "boost/exception/to_string.hpp"
#include "EObject.hpp"
#include "ENamedElement.hpp"

#include "Option.hpp"

namespace persistence {

class Handler {
public:
	Handler ();
	virtual ~Handler ();

	void handle ( std::shared_ptr<ecore::EObject> element, std::set<std::string> options );
	//void handle ( boost::property_tree::ptree element, std::set<std::string> options );

	std::map<std::string, std::shared_ptr<ecore::EObject>> get_IdToObject_Map ();
	std::map<std::shared_ptr<ecore::EObject>, std::string> get_ObjectToId_Map ();

	std::string get_Id ( std::shared_ptr<ecore::EObject> object );
	std::shared_ptr<ecore::EObject> get_Object ( std::string id );

	DOMDocument *getDOMDocument ();

	std::string getPrefix ();

	void addToMap ( std::shared_ptr<ecore::EObject> object );
	void addToMap ( std::shared_ptr<ecore::EObject> object, std::string id );

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
	void addAttribute ( const std::string& name, T value ) {
		addAttribute( name, boost::to_string( value ) );
	}
	void addAttribute ( const std::string &name, bool value );
	void addAttribute ( const std::string &name, const std::string& value );
	void addAttribute_xsi_type ( const std::string& value );

	void addReference ( const std::string &name, std::shared_ptr<ecore::EObject> object );

	template<typename T>
	void addReference ( const std::string &name, std::shared_ptr<Bag<T> > objects ) {
		if ( objects->size() ) {
			for ( std::shared_ptr<T> object : *objects ) {
				addReference( name, object );
			}
		}
	}

	void release ();

private:

	DOMDocument *m_doc;

	DOMElement *m_current_elem;

	std::set<std::string> m_options;

	std::string m_rootPrefix;

	std::map<std::string, std::shared_ptr<ecore::EObject>> m_Id_to_Object;
	std::map<std::shared_ptr<ecore::EObject>, std::string> m_Object_to_Id;

	void addChild ( DOMElement *parent_elem, DOMElement *child_elem );

	std::string create_Hash ( std::shared_ptr<ecore::EObject> object );
}
;

} /* namespace persistence */

#endif /* HANDLER_HPP_ */
