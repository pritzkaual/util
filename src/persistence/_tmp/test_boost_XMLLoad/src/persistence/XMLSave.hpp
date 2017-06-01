/*
 * XMLSave.hpp
 *
 *  Created on: 16.05.2017
 *      Author: Alexander
 */

#ifndef XMLSAVE_HPP_
#define XMLSAVE_HPP_

#include "Save.hpp"
#include "boost/property_tree/xml_parser.hpp"

//#include "ExtendedMetaData.hpp"

#include <string>


namespace persistence {

class XMLSave : public Save {
public:
	XMLSave ();
	virtual ~XMLSave ();

	//bool save ( const std::string &filename, std::shared_ptr<ecore::EObject> model, std::set<std::string> options );

private:
	static const std::string wasd; // TODO Remove this.

	bool write (const std::string &filename);

};

} /* namespace persistence */

#endif /* XMLSAVE_HPP_ */
