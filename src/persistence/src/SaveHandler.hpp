/*
 * SaveHandler.hpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#ifndef SaveHandler_HPP_
#define SaveHandler_HPP_

#include "XSaveHandler.hpp"
#include "HandlerHelper.hpp"

#include <map>
#include <list>
#include <string>
#include <set>
#include <exception>

#include "boost/exception/to_string.hpp"

#include "EObject.hpp"


namespace BasePersistence
{
class SaveHandler : public XPersistence::XSaveHandler
{
public:
	SaveHandler ();
	virtual ~SaveHandler ();

	std::string getPrefix ();
	void setRootObject ( std::shared_ptr<ecore::EObject> object );

	std::string extractType ( std::shared_ptr<ecore::EObject> obj ) const;

	virtual bool createRootNode ( const std::string& name, const std::string& ns_uri ) = 0;
	virtual bool createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri ) = 0;

	virtual bool createAndAddElement ( const std::string& name ) = 0;

	void addAttribute ( const std::string &name, bool value );
	virtual void addAttribute ( const std::string &name, const std::string& value ) = 0;

	void addReference ( const std::string &name, std::shared_ptr<ecore::EObject> object );
	virtual void addReferences ( const std::string &name, std::shared_ptr<ecore::EObject> object ) = 0;

	virtual void release () = 0;

protected:
	std::shared_ptr<ecore::EObject> m_rootObject;
	std::string m_rootPrefix;
}
;

} /* namespace BasePersistence */

#endif /* SaveHandler_HPP_ */
