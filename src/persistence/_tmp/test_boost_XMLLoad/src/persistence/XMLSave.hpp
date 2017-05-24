/*
 * XMLSave.hpp
 *
 *  Created on: 16.05.2017
 *      Author: Alexander
 */

#ifndef XMLSAVE_HPP_
#define XMLSAVE_HPP_

#include "ExtendedMetaData.hpp"
#include <map>
#include <string>

namespace persistence {

class XMLSave {
public:
	XMLSave ();
	virtual ~XMLSave ();

	void save ( const std::string& filename, ecore::EObject* model, std::map<boost::any, boost::any> options );

private:
	const std::string wasd = ExtendedMetaData::XMI_PREFIX; // TODO Remove this.

};

} /* namespace persistence */

#endif /* XMLSAVE_HPP_ */
