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
//#include "JSONSave.hpp"
#include "XMLSave.hpp"
#include "XMLLoad.hpp"

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

	std::shared_ptr<ecore::EObject> load ( const std::string &filename, std::set<std::string> options );
	bool save ( const std::string &filename, std::shared_ptr<ecore::EObject> model, std::shared_ptr<ecore::EPackage> metaMetaPackage,
			std::set<std::string> options );

private:
	bool isValidFile ( const std::string &filename );

};

} /* namespace persistence */

#endif /* PERSISTENCE_HPP_ */
