/*
 * Load.hpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#ifndef LOAD_HPP_
#define LOAD_HPP_

#include <exception>

//#include "ExtendedMetaData.hpp"
#include "Handler.hpp"

#include "EObject.hpp"
#include "EPackage.hpp"
#include "EcorePackage.hpp"
#include "EcoreFactory.hpp"

//#include "EClass.hpp"
//#include "EEnum.hpp"
//#include "EEnumLiteral.hpp"
//#include "EDataType.hpp"
//#include "EAttribute.hpp"
//#include "EAnnotation.hpp"
#include "EStructuralFeature.hpp"
//#include "EOperation.hpp"
//#include "EParameter.hpp"
#include "EReference.hpp"
//#include "EStringToStringMapEntry.hpp"

#include <boost/any.hpp>

namespace persistence {

class Load {
public:
	Load ();
	virtual ~Load ();

	std::shared_ptr<ecore::EObject> load (const std::string &filename, std::set<std::string> options);

protected:
	std::shared_ptr<persistence::Handler> m_handler;

	virtual bool read ( const std::string &filename, std::shared_ptr<persistence::Handler> handler ) = 0;

};

} /* namespace persistence */

#endif /* LOAD_HPP_ */
