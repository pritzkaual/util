/*
 * Persistence.cpp
 *
 *  Created on: 16.05.2017
 *      Author: Alexander
 */

#include "Persistence.hpp"
#include "Load.hpp"
#include "Save.hpp"
//#include "JSONSave.hpp"
#include "XMLSave.hpp"
#include "XMLLoad.hpp"

#include "Option.hpp"
using namespace std;

namespace persistence {

Persistence::Persistence () {

}

Persistence::~Persistence () {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<ecore::EObject> Persistence::load ( const std::string& filename, std::set<std::string> options ) {
	std::shared_ptr<ecore::EObject> retvalue = nullptr;

	if ( isValidFile( filename ) == false ) {
		std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << "Given filename: '" << filename << "' is not valid!" << std::endl;
		retvalue = nullptr;
	}

	if ( true ) {
		std::cout << "| INFO     | " << "Load from XML-File" << "\n";

		std::shared_ptr<persistence::XMLLoad> tmp_load(new persistence::XMLLoad());

		retvalue = tmp_load->load( filename, options ); // TODO use inheritance method in XMLLoad
	}
	return retvalue;
}

bool Persistence::save ( const std::string& filename, std::shared_ptr<ecore::EObject> model, std::shared_ptr<ecore::EPackage> metaMetaPackage,
		std::set<std::string> options ) {
	bool retvalue = false;

	if ( isValidFile( filename ) == false ) {
		std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << "Given filename: '" << filename << "' is not valid!" << std::endl;
		return false;
	}

	if ( options.find( persistence::Option::OPTION_SAVE_JSON ) != options.end() ) {
		std::cout << "| INFO     | " << "Save as JSON-File" << "\n";
		/*
		 std::shared_ptr<persistence::JSONSave> jsonSave = std::make_shared<persistence::JSONSave>();
		 jsonSave->save(filename, model, options); // TODO use inheritance method in JSONSave
		 */
		std::cout << "| ERROR    | " << "Save as JSON-File is not implemented." << "\n";
		retvalue = false;

	}
	else if ( options.find( persistence::Option::OPTION_SAVE_XML ) != options.end() ) {
		std::cout << "| INFO     | " << "Save as XML-File" << "\n";

		std::shared_ptr<persistence::XMLSave> xmlSave(new persistence::XMLSave());

		retvalue = xmlSave->save( filename, model, metaMetaPackage, options ); // TODO use inheritance method in XMLSave

	}
	return retvalue;
}

bool Persistence::isValidFile ( const std::string& filename ) {
	//boost::filesystem::path file( filename );
	// TODO needs implementation
	std::cout << "| WARNING  | " << __PRETTY_FUNCTION__ << " is not implemented!" << std::endl;

	return true;
}

} /* namespace persistence */
