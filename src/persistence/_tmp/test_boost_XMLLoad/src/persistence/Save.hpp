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

#include "boost/property_tree/ptree.hpp"
#include "boost/foreach.hpp"

#include "EObject.hpp"
#include "EClass.hpp"
#include "EAttribute.hpp"
#include "EAnnotation.hpp"
#include "EOperation.hpp"
#include "EReference.hpp"

#include "ExtendedMetaData.hpp"
#include "Handler.hpp"

namespace persistence {

class Save {
public:
	Save ();
	virtual ~Save ();

	bool save ( const std::string &filename, std::shared_ptr<ecore::EObject> model, std::set<std::string> options );

protected:
	std::shared_ptr<persistence::Handler> m_handler;

	const std::string m_filename;
	std::shared_ptr<ecore::EObject> m_model;
	std::set<std::string> m_options;
	boost::property_tree::ptree m_tree;


private:
	virtual bool write (const std::string &filename) = 0;

	boost::property_tree::ptree traverse(std::shared_ptr<ecore::EObject> object, boost::property_tree::ptree tree);


};

} /* namespace persistence */

#endif /* SAVE_HPP_ */
