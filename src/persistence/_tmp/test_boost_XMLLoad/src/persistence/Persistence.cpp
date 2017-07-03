/*
 * Persistence.cpp
 *
 *  Created on: 16.05.2017
 *      Author: Alexander
 */

#include "Persistence.hpp"

using namespace std;

namespace persistence {

Persistence::Persistence () {

}

Persistence::~Persistence () {
	// TODO Auto-generated destructor stub
}

bool Persistence::load ( const std::string& filename, std::shared_ptr<ecore::EObject> model, std::set<std::string> options ) {
	isValidFile( filename );
	return true;
}

bool Persistence::save ( const std::string& filename, std::shared_ptr<ecore::EObject> model, std::set<std::string> options ) {
	if ( !isValidFile( filename ) ) {
		std::cout << "| ERROR    | " << "Given filename: '" << filename << "' is not valid!" << std::endl;
	}

	if ( options.find( persistence::Option::OPTION_SAVE_JSON ) != options.end() ) {
		std::cout << "| INFO     | " << "Save as JSON-File" << "\n";
		/*
		 std::shared_ptr<persistence::JSONSave> tmp_save = std::make_shared<persistence::JSONSave>();
		 tmp_save->save(filename, model, options); // TODO use inheritance method in JSONSave
		 */
	}
	else if ( options.find( persistence::Option::OPTION_SAVE_XML ) != options.end() ) {
		std::cout << "| INFO     | " << "Save as XML-File" << "\n";

		std::shared_ptr<persistence::XMLSave> tmp_save = std::make_shared<persistence::XMLSave>();
		tmp_save->setOptions( options );
		tmp_save->setFilename( filename );
		tmp_save->setModel( model );
		tmp_save->save(); // TODO use inheritance method in XMLSave
	}

	return true;
}

bool Persistence::isValidFile ( const std::string& filename ) {
	//boost::filesystem::path file( filename );

	return true;
}

} /* namespace persistence */
