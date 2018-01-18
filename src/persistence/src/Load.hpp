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
#include "LoadHandler.hpp"

#include "EObject.hpp"
#include "EPackage.hpp"
#include "EcoreFactory.hpp"
#include "EStructuralFeature.hpp"
#include "EReference.hpp"

#include <boost/any.hpp>

namespace persistence {

class Load {
public:
	Load ();
	virtual ~Load ();

	std::shared_ptr<ecore::EObject> load (const std::string &filename, std::set<std::string> options);

protected:
	std::shared_ptr<persistence::LoadHandler> m_handler;

	virtual bool read ( const std::string &filename, std::shared_ptr<persistence::LoadHandler> handler ) = 0;

};

} /* namespace persistence */

#endif /* LOAD_HPP_ */
