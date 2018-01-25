/*
 * Save.hpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#ifndef SAVE_HPP_
#define SAVE_HPP_

#include <set>
#include <iostream>
#include <string>

#include "EObject.hpp"
#include "EPackage.hpp"

#include "SaveHandler.hpp"

namespace BasePersistence {

class Save {
public:
	Save ();
	virtual ~Save ();

	bool save ( const std::string &filename, std::shared_ptr<ecore::EObject> model, std::shared_ptr<ecore::EPackage> metaMetaPackage );

protected:
	std::shared_ptr<BasePersistence::SaveHandler> m_handler;

	virtual bool write ( const std::string &filename ) = 0;

};

} /* namespace BasePersistence */

#endif /* SAVE_HPP_ */
