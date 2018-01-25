/*
 * Persistence.hpp
 *
 *  Created on: 16.05.2017
 *      Author: Alexander
 */

#ifndef PERSISTENCE_HPP_
#define PERSISTENCE_HPP_

#include "EObject.hpp"
#include "EPackage.hpp"

//#include "boost/filesystem.hpp"   // includes all needed Boost.Filesystem declarations
#include <string>
#include <set>
#include <iostream>

namespace BasePersistence {

class Persistence {
public:
	Persistence ();
	virtual ~Persistence ();

	virtual std::shared_ptr<ecore::EObject> load ( const std::string &filename) = 0;
	virtual bool save ( const std::string &filename, std::shared_ptr<ecore::EObject> model, std::shared_ptr<ecore::EPackage> metaMetaPackage ) = 0;

protected:
	bool isValidFile ( const std::string &filename );

};

} /* namespace BasePersistence */

#endif /* PERSISTENCE_HPP_ */
