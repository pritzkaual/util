/*
 * Persistence.hpp
 *
 *  Created on: 16.05.2017
 *      Author: Alexander
 */

#ifndef PERSISTENCE_HPP_
#define PERSISTENCE_HPP_


#include "Load.hpp"
#include "Save.hpp"
#include "JSONSave.hpp"
#include "XMLSave.hpp"

#include "Option.hpp"

#include "EObject.hpp"
#include "EcorePackage.hpp"

//#include "boost/filesystem.hpp"   // includes all needed Boost.Filesystem declarations
#include <string>
#include <set>
#include <iostream>


namespace persistence {

class Persistence {
public:
	Persistence ();
	virtual ~Persistence ();

	bool load(const std::string &filename, std::shared_ptr<ecore::EObject> model, std::set<std::string> options);
	bool save(const std::string &filename, std::shared_ptr<ecore::EObject> model, std::set<std::string> options);

private:
	bool isValidFile(const std::string &filename);

	//boost::filesystem::path m_file;
	std::shared_ptr<ecore::EObject> m_model;
	std::shared_ptr<ecore::EObject> m_metamodel;
	std::shared_ptr<std::set<std::string>> m_options;


	std::shared_ptr<persistence::Load> m_load;
	std::shared_ptr<persistence::Save> m_save;
};

} /* namespace persistence */

#endif /* PERSISTENCE_HPP_ */
