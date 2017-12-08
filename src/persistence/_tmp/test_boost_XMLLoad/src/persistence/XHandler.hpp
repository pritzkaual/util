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

#include <memory>

#include "SubsetUnion.hpp"

//#include <xercesc/dom/DOM.hpp>
//#include <xercesc/dom/DOMException.hpp>
//#include <xercesc/util/OutOfMemoryException.hpp>

//#include "xerces/XStr.hpp"
//#include "xerces/DOMTreeErrorReporter.hpp"
//#include "xerces/DOMPrintFilter.hpp"
//#include "xerces/DOMPrintErrorHandler.hpp"

#include <exception>
#include "boost/exception/to_string.hpp"

//#include "EClass.hpp"
//#include "EDataType.hpp"
//#include "ENamedElement.hpp"
namespace ecore {
	class EObject;
	class EStructuralFeature;
}

//#include "EPackage.hpp"
//#include "EStructuralFeature.hpp"




//#include "Option.hpp"

namespace persistence {

class XHandler {
public:
	//destructor
	virtual ~XHandler () {}

	//virtual void handle ( std::shared_ptr<ecore::EObject> element, std::set<std::string> options ) = 0;

	//virtual std::map<std::string, std::shared_ptr<ecore::EObject>> get_IdToObject_Map () = 0;
	//virtual std::map<std::shared_ptr<ecore::EObject>, std::string> get_ObjectToId_Map () = 0;

	//virtual std::string get_Id ( std::shared_ptr<ecore::EObject> object ) = 0;
	virtual std::shared_ptr<ecore::EObject> get_Object ( std::string id ) = 0;

	//DOMDocument *getDOMDocument () = 0;

	virtual std::string getPrefix () = 0;
	virtual std::string getType ( std::shared_ptr<ecore::EObject> obj ) const = 0;

	//virtual void addToMap ( std::shared_ptr<ecore::EObject> object ) = 0;
	virtual void addToMap ( std::shared_ptr<ecore::EObject> object ) = 0;

	virtual void setRootObj ( std::shared_ptr<ecore::EObject> object ) = 0;
	virtual void setCurrentObj ( std::shared_ptr<ecore::EObject> object ) = 0;
	virtual std::shared_ptr<ecore::EObject> getCurrentObj ( ) = 0;

	virtual bool createRootNode ( const std::string& name, const std::string& ns_uri ) = 0;
	virtual bool createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri ) = 0;
	//bool createRootNode ( const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype ) = 0;
	//bool createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype ) = 0;

	virtual bool createAndAddElement ( const std::string& name ) = 0;

	/*
	 void addAttribute ( const std::string& name, float value );
	 void addAttribute ( const std::string& name, double value );
	 void addAttribute ( const std::string& name, long double value );

	 void addAttribute ( const std::string& name, int value );
	 void addAttribute ( const std::string& name, long int value );
	 void addAttribute ( const std::string& name, long long int value );
	 void addAttribute ( const std::string& name, unsigned int value );
	 void addAttribute ( const std::string& name, unsigned long int value );
	 void addAttribute ( const std::string& name, unsigned long long int value );
	 */
	template<typename T>
	void addAttribute ( const std::string& name, T value )
	{
		addAttribute( name, boost::to_string( value ) );
	}
	virtual void addAttribute ( const std::string &name, bool value ) = 0;
	virtual void addAttribute ( const std::string &name, const std::string& value ) = 0;
	//virtual void addAttribute_xsi_type ( const std::string& value ) = 0;

	virtual void addReference ( const std::string &name, std::shared_ptr<ecore::EObject> object ) = 0;

	template<typename T>
	void addReference ( const std::string &name, std::shared_ptr<Bag<T> > objects )
	{
		if ( objects->size() ) {
			for ( std::shared_ptr<T> object : *objects ) {
				addReference( name, object );
			}
		}
	}

	virtual void release () = 0;
	virtual void releaseObj () = 0;

	virtual int getNumOfChildren() = 0;
	virtual std::string getNextNodeName() = 0;
	virtual std::map<std::string, std::string> getAttributeList () = 0;


	virtual void addUnresolvedReference(const std::string &name, std::shared_ptr<ecore::EObject> object, std::shared_ptr<ecore::EStructuralFeature> esf ) = 0;


}
;

} /* namespace persistence */

#endif /* XHANDLER_HPP_ */
