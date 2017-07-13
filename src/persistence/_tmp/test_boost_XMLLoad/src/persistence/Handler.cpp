/*
 * Handler.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "Handler.hpp"

#include <sstream> // used for get_Hash()

namespace persistence {

Handler::Handler () {
	// TODO Auto-generated constructor stub
	m_doc = nullptr;
	//m_root_elem = nullptr;
	m_current_elem = nullptr;

}

Handler::~Handler () {
	if ( m_doc ) {
		m_doc->release();
	}
}

void Handler::handle ( std::shared_ptr<ecore::EObject> element, std::set<std::string> options ) {

}

std::map<std::string, std::shared_ptr<ecore::EObject> > Handler::get_IdToObject_Map () {
	return m_Id_to_Object;
}

std::map<std::shared_ptr<ecore::EObject>, std::string> Handler::get_ObjectToId_Map () {
	return m_Object_to_Id;
}

std::string Handler::get_Id ( std::shared_ptr<ecore::EObject> object ) {

	std::string id;

	if ( m_Object_to_Id.find( object ) != m_Object_to_Id.end() ) {
		// found
		id = m_Object_to_Id.at( object );
	}

	return id;
}

std::shared_ptr<ecore::EObject> Handler::get_Object ( std::string id ) {
	std::shared_ptr<ecore::EObject> tmp;

	if ( m_Id_to_Object.find( id ) != m_Id_to_Object.end() ) {
		// found
		tmp = m_Id_to_Object.at( id );
	}
	return std::dynamic_pointer_cast<ecore::EObject>( tmp );
}

void Handler::addToMap ( std::shared_ptr<ecore::EObject> object ) {

	std::shared_ptr<ecore::ENamedElement> tmp_object = std::dynamic_pointer_cast<ecore::ENamedElement>( object );

	addToMap( object, tmp_object->getName() );
}

void Handler::addToMap ( std::shared_ptr<ecore::EObject> object, std::string id ) {

	std::string _id;
	if ( m_options.find( persistence::Option::OPTION_USE_ID__HASHTAG ) != m_options.end() ) {
		_id = "#//" + id;
	}
	else if ( m_options.find( persistence::Option::OPTION_USE_ID__AT ) != m_options.end() ) {
		std::cout << "ERROR: Handler::addToMap() OPTION_USE_ID__AT is not implemented yet." << std::endl;
	}
	else {
		// default-case: Using generated Hash-Value
		_id = create_Hash( object );
	}

	if ( m_Id_to_Object.find( _id ) == m_Id_to_Object.end() ) {
		// not found
		m_Id_to_Object.insert( std::pair<std::string, std::shared_ptr<ecore::EObject>>( _id, object ) );
		m_Object_to_Id.insert( std::pair<std::shared_ptr<ecore::EObject>, std::string>( object, _id ) );
	}
}

DOMDocument *Handler::getDOMDocument () {
	return m_doc;
}

std::string Handler::getPrefix () {
	return m_rootPrefix;
}

bool Handler::createRootNode ( const std::string& name, const std::string& ns_uri ) {
	return this->createRootNode( name, ns_uri, nullptr );
}

bool Handler::createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri ) {
	return this->createRootNode( prefix, name, ns_uri, nullptr );
}

bool Handler::createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype ) {
	m_rootPrefix = prefix;
	return this->createRootNode( prefix + ":" + name, ns_uri, nullptr );
}

bool Handler::createRootNode ( const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype ) {

	DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation( X( "Core" ) );

	if ( impl != NULL ) {
		try {

			m_doc = impl->createDocument( (ns_uri.empty()) ? 0 : X( ns_uri ), // root element namespace URI.
			X( name ),         					// root element name
			doctype ); 	                		// document type object (DTD).

			m_doc->getDocumentElement();

			m_current_elem = m_doc->getDocumentElement(); // get root element

		}
		catch ( const OutOfMemoryException& ) {
			std::cerr << "OutOfMemoryException" << std::endl;
			//errorCode = 5;
			return false;
		}
		catch ( const DOMException& e ) {
			std::cout << "DOMException code is:  " << e.code << std::endl << StrX( e.getMessage() ) << std::endl;
			//errorCode = 2;
			return false;
		}
		catch ( ... ) {
			std::cout << "An error occurred creating the document" << std::endl;
			//errorCode = 3;
			return false;
		}
	}  // (impl != NULL)
	else {
		std::cout << "Requested implementation is not supported" << std::endl;
		//errorCode = 4;
		return false;
	}

	return true;
}

bool Handler::createAndAddElement ( const std::string& name ) {
	if ( m_doc == nullptr ) {
		std::cout << "ERROR: Called Handler::createElement() while their is no root-Element created before." << std::endl;
		return false;
	}
	else {
		addChild( m_current_elem, m_doc->createElement( X( name ) ) );

		return true;
	}
}

void Handler::addChild ( DOMElement* parent_elem, DOMElement* child_elem ) {
	// Add child to parent Element, and set child as current Element.
	m_current_elem = (DOMElement *) parent_elem->appendChild( child_elem );
}

void Handler::addAttribute ( const std::string &name, bool value ) {
	addAttribute( name, (value ? (std::string) "true" : (std::string) "false") );
}

void Handler::addAttribute ( const std::string& name, const std::string& value ) {
	try {
		m_current_elem->setAttribute( X( name ), X( value ) );
	}
	catch ( const DOMException& e ) {
		std::cout << "DOMException code is:  " << e.code << std::endl << StrX( e.getMessage() ) << std::endl;
	}
	catch ( std::exception& e ) {
		std::cout << "Exception code is:  " << e.what() << std::endl;
	}
}

void Handler::addAttribute_xsi_type ( const std::string& value ) {
	addAttribute( "xsi:type", value );
}


void Handler::addReference ( const std::string &name, std::shared_ptr<ecore::EObject> object ) {

	std::cout << "ERROR: Called Handler::addReference() while is not implemented yet." << std::endl;
}

void addReference ( const std::string &name, std::shared_ptr< Bag<ecore::EObject> > objects ){

	std::cout << "ERROR: Called Handler::addReference() while is not implemented yet." << std::endl;
}

void Handler::release () {
	if ( m_current_elem == nullptr ) {
		std::cout << "ERROR: You can't call Handler::release() while current DOMElement m_current_elem is nullptr." << std::endl;
	}
	else {
		// set current_elem's parent node as new current_elem (decrease depth)
		m_current_elem = (DOMElement*) m_current_elem->getParentNode();
	}
}

std::string Handler::create_Hash ( std::shared_ptr<ecore::EObject> object ) {

	std::ostringstream address;
	address << object.get();
	std::string name = address.str();

	return name;
}

} /* namespace persistence */

