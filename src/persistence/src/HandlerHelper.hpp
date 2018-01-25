/*
 * HandlerHelper.hpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#ifndef HandlerHelper_HPP_
#define HandlerHelper_HPP_

#include <list>
#include <string>
#include <set>

#include "EClass.hpp"
#include "EDataType.hpp"
#include "ENamedElement.hpp"
#include "EObject.hpp"
#include "EPackage.hpp"
#include "EStructuralFeature.hpp"

namespace persistence
{
class HandlerHelper
{
public:
	HandlerHelper ();
	virtual ~HandlerHelper ();

	static std::string extractType ( const std::shared_ptr<ecore::EObject> obj, std::string prefix);
	static std::string extractReference ( const std::shared_ptr<ecore::EObject> toObject, const std::shared_ptr<ecore::EObject> rootObject, std::string prefix );
}
;

} /* namespace persistence */

#endif /* HandlerHelper_HPP_ */