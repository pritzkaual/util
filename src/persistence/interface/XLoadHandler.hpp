/*
 * LoadHandler.hpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#ifndef XLoadHandler_HPP_
#define XLoadHandler_HPP_

#include <map>
#include <list>
#include <string>
#include <set>
#include <exception>
#include "boost/exception/to_string.hpp"

#include "SubsetUnion.hpp"

namespace ecore {
	class EObject;
	//class EModelElement;
	class EStructuralFeature;
}

namespace persistence {

class XLoadHandler {
public:
	//destructor
	virtual ~XLoadHandler () {}

	virtual void addToMap ( std::shared_ptr<ecore::EObject> object ) = 0;

	virtual void setCurrentObject ( std::shared_ptr<ecore::EObject> object ) = 0;
	virtual std::shared_ptr<ecore::EObject> getCurrentObject ( ) = 0;

	virtual void release () = 0;

	virtual int getNumOfChildNodes() = 0;
	virtual std::string getNextNodeName() = 0;
	virtual std::map<std::string, std::string> getAttributeList () = 0;

	virtual void addUnresolvedReference(const std::string &name, std::shared_ptr<ecore::EObject> object, std::shared_ptr<ecore::EStructuralFeature> esf ) = 0;
}
;

} /* namespace persistence */

#endif /* XLoadHandler_HPP_ */
