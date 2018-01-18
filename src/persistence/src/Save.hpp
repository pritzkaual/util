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

namespace persistence {

class Save {
public:
	Save ();
	virtual ~Save ();

	bool save ( const std::string &filename, std::shared_ptr<ecore::EObject> model, std::shared_ptr<ecore::EPackage> metaMetaPackage, std::set<std::string> options );

protected:
	std::shared_ptr<persistence::SaveHandler> m_handler;

private:
	virtual bool write ( const std::string &filename, std::shared_ptr<persistence::SaveHandler> handler ) = 0;

};

} /* namespace persistence */

#endif /* SAVE_HPP_ */
