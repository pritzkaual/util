/*
 * Handler.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "Handler.hpp"

#include <sstream>

namespace persistence {

Handler::Handler () {
	// TODO Auto-generated constructor stub

}

Handler::~Handler () {
	// TODO Auto-generated destructor stub
}

void Handler::handle ( std::shared_ptr<ecore::EObject> element, std::set<std::string> options ) {

}

void Handler::handle ( boost::property_tree::ptree element, std::set<std::string> options ) {
}

std::map<std::string, std::shared_ptr<ecore::EObject> > Handler::get_IdToObject_Map () {
	return m_Id_to_Object;
}

std::map<std::shared_ptr<ecore::EObject>, std::string> Handler::get_ObjectToId_Map () {
	return m_Object_to_Id;
}


std::string Handler::get_Id ( std::shared_ptr<ecore::EObject> object ) {

	std::string id = get_Hash( object );

	if ( m_Id_to_Object.find(id) == m_Id_to_Object.end() ) {
		// not found
		m_Id_to_Object.insert(std::pair<std::string, std::shared_ptr<ecore::EObject>>(id, object));
		m_Object_to_Id.insert(std::pair<std::shared_ptr<ecore::EObject>, std::string>(object, id)); // TODO brauche ich diese map wirklich
	}

	return id;
}

std::shared_ptr<ecore::EObject> Handler::get_Object ( std::string id ) {
	std::shared_ptr<ecore::EObject> tmp;

	if ( m_Id_to_Object.find(id) != m_Id_to_Object.end() ) {
		// found
		tmp = m_Id_to_Object.at(id);
	}
	return std::dynamic_pointer_cast<ecore::EObject>( tmp );
}

std::string Handler::get_Hash ( std::shared_ptr<ecore::EObject> object ) {

	std::ostringstream address;
	address <<  object.get();
	std::string name = address.str();

	return name;
}

} /* namespace persistence */
