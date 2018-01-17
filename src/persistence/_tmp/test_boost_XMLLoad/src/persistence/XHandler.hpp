/*
 * Handler.hpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#ifndef XHANDLER_HPP_
#define XHANDLER_HPP_

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

class XHandler {
public:
	//destructor
	virtual ~XHandler () {}

	virtual std::string extractType ( std::shared_ptr<ecore::EObject> obj ) const = 0;

	virtual void addToMap ( std::shared_ptr<ecore::EObject> object ) = 0;

	virtual void setCurrentObject ( std::shared_ptr<ecore::EObject> object ) = 0;
	virtual std::shared_ptr<ecore::EObject> getCurrentObject ( ) = 0;
  
	virtual bool createAndAddElement ( const std::string& name ) = 0;

	template<typename T>
	void addAttribute ( const std::string& name, T value )
	{
		addAttribute( name, boost::to_string( value ) );
	}
	virtual void addAttribute ( const std::string &name, bool value ) = 0;
	virtual void addAttribute ( const std::string &name, const std::string& value ) = 0;

	virtual void addReference ( const std::string &name, std::shared_ptr<ecore::EObject> object ) = 0;
	virtual void addReferences ( const std::string &name, std::shared_ptr<ecore::EObject> object ) = 0;

	template<typename T>
	void addReferences ( const std::string &name, std::shared_ptr<Bag<T> > objects )
	{
		for (std::shared_ptr<T> _object : *objects)
		{
			addReferences ( name, _object );
		}
	}

	virtual void release () = 0;
	virtual void releaseObj () = 0;

	virtual int getNumOfChildNodes() = 0;
	virtual std::string getNextNodeName() = 0;
	virtual std::map<std::string, std::string> getAttributeList () = 0;

	virtual void addUnresolvedReference(const std::string &name, std::shared_ptr<ecore::EObject> object, std::shared_ptr<ecore::EStructuralFeature> esf ) = 0;
}
;

} /* namespace persistence */

#endif /* XHANDLER_HPP_ */
