/*
 * Save.hpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#ifndef SAVE_HPP_
#define SAVE_HPP_

#ifdef NDEBUG
	#define MSG_DEBUG(a) /**/
#else
	#define MSG_DEBUG(a) std::cout<<"| DEBUG    | "<<a<<std::endl
#endif
#define MSG_WARNING(a) std::cout<<"| WARNING  | "<<a<<std::endl
#define MSG_ERROR(a) std::cout<<"| ERROR    | "<<a<<std::endl
#define MSG_FLF __FILE__<<":"<<__LINE__<<" "<<__FUNCTION__<<"() "

#include <set>
#include <iostream>
#include <string>

#include "EObject.hpp"
#include "EPackage.hpp"

#include "SaveHandler.hpp"

namespace persistence
{
namespace base
{
class Save
{
public:
	Save ();
	virtual ~Save ();

	bool save ( const std::string &filename, std::shared_ptr<ecore::EObject> model, std::shared_ptr<ecore::EPackage> metaMetaPackage );

protected:
	std::shared_ptr<persistence::base::SaveHandler> m_handler;

	virtual bool write ( const std::string &filename ) = 0;
};
} /* namespace base */
} /* namespace persistence */

#endif /* SAVE_HPP_ */
