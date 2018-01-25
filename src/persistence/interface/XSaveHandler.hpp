/*
 * SaveHandler.hpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#ifndef XSaveHandler_HPP_
#define XSaveHandler_HPP_

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

namespace XPersistence {

class XSaveHandler {
public:
	//destructor
	virtual ~XSaveHandler () {}

	virtual std::string extractType ( std::shared_ptr<ecore::EObject> obj ) const = 0;
  
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
}
;

} /* namespace XPersistence */

#endif /* XSaveHandler_HPP_ */
