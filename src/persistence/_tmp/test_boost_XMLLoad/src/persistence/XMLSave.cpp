/*
 * XMLSave.cpp
 *
 *  Created on: 16.05.2017
 *      Author: Alexander
 */

#include "XMLSave.hpp"
//#include "ExtendedMetaData.hpp"

namespace persistence {

const std::string XMLSave::wasd = ExtendedMetaData::XMI_PREFIX; // TODO Remove this.

XMLSave::XMLSave () {
	// TODO Auto-generated constructor stub
}

XMLSave::~XMLSave () {
	// TODO Auto-generated destructor stub
}
/*
bool XMLSave::save ( const std::string& filename, std::shared_ptr<ecore::EObject> model, std::set<std::string> options ) {

	return write(filename, options);
}
*/
bool XMLSave::write (const std::string &filename ) {

	boost::property_tree::write_xml( filename, *(m_tree.get()), std::locale(), boost::property_tree::xml_writer_make_settings<std::string>( ' ', 2 ) );

	return true;
}

} /* namespace persistence */
