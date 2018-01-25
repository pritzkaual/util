/*
 * XMLPersistence.hpp
 *
 *  Created on: 25.01.2018
 *      Author: Alexander
 */

#ifndef XMLPERSISTENCE_HPP_
#define XMLPERSISTENCE_HPP_

#include "Persistence.hpp"

#include "EObject.hpp"
#include "EPackage.hpp"

//#include "boost/filesystem.hpp"   // includes all needed Boost.Filesystem declarations
#include <string>
#include <iostream>

namespace XMLPersistence {

class XML_Persistence : BasePersistence::Persistence  {
public:
	XML_Persistence ();
	virtual ~XML_Persistence ();

	std::shared_ptr<ecore::EObject> load ( const std::string &filename );
	bool save ( const std::string &filename, std::shared_ptr<ecore::EObject> model, std::shared_ptr<ecore::EPackage> metaMetaPackage);

private:

};

} /* namespace XMLPersistence */

#endif /* XMLPERSISTENCE_HPP_ */
