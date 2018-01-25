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

namespace persistence
{
namespace base
{
class Load
{
public:
	Load ();
	virtual ~Load ();

	std::shared_ptr<ecore::EObject> load ( const std::string &filename );

protected:
	std::shared_ptr<persistence::base::LoadHandler> m_handler;

	virtual bool read ( const std::string &filename ) = 0;
};

} /* namespace base */
} /* namespace persistence */

#endif /* LOAD_HPP_ */