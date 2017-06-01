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

#include "boost/property_tree/ptree.hpp"

#include "EObject.hpp"

#include "Option.hpp"

namespace persistence {

class Handler {
public:
	Handler ();
	virtual ~Handler ();

	void handle ( std::shared_ptr<ecore::EObject> element, std::set<std::string> options );
	void handle ( boost::property_tree::ptree element, std::set<std::string> options );

	std::map<std::string, std::shared_ptr<ecore::EObject>> get_IdToObject_Map ();
	std::map<std::shared_ptr<ecore::EObject>, std::string> get_ObjectToId_Map ();

	std::string get_Id ( std::shared_ptr<ecore::EObject> object );
	std::shared_ptr<ecore::EObject> get_Object ( std::string id );

private:
	std::set<std::string> m_options;

	std::map<std::string, std::shared_ptr<ecore::EObject>> m_Id_to_Object;
	std::map<std::shared_ptr<ecore::EObject>, std::string> m_Object_to_Id;


	boost::property_tree::ptree m_tree;

	std::string get_Hash ( std::shared_ptr<ecore::EObject> object );
};

} /* namespace persistence */

#endif /* HANDLER_HPP_ */
