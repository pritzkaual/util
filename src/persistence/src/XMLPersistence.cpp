/*
 * XML_Persistence.cpp
 *
 *  Created on: 25.01.2018
 *      Author: Alexander
 */

#include "XMLPersistence.hpp"
#include "Load.hpp"
#include "Save.hpp"
//#include "JSONSave.hpp"
#include "XMLSave.hpp"
#include "XMLLoad.hpp"


namespace XMLPersistence {

XML_Persistence::XML_Persistence () {

}

XML_Persistence::~XML_Persistence () {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<ecore::EObject> XML_Persistence::load ( const std::string& filename )
{
	if ( isValidFile( filename ) == false ) {
		std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << "Given filename: '" << filename << "' is not valid!" << std::endl;
		return nullptr;
	}

	std::cout << "| INFO     | " << "Load from XML-File" << "\n";

	std::shared_ptr<XMLPersistence::XMLLoad> tmp_load(new XMLPersistence::XMLLoad());

	return tmp_load->load( filename ); // TODO use inheritance method in XMLLoad
}

bool XML_Persistence::save ( const std::string& filename, std::shared_ptr<ecore::EObject> model, std::shared_ptr<ecore::EPackage> metaMetaPackage )
{
	if ( isValidFile( filename ) == false ) {
		std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << "Given filename: '" << filename << "' is not valid!" << std::endl;
		return false;
	}

	std::cout << "| INFO     | " << "Save as XML-File" << "\n";

	std::shared_ptr<XMLPersistence::XMLSave> xmlSave(new XMLPersistence::XMLSave());

	return xmlSave->save( filename, model, metaMetaPackage); // TODO use inheritance method in XMLSave
}


} /* namespace XMLPersistence */


