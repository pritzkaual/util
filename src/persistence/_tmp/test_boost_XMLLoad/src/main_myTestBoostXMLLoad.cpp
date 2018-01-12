/*
 * main_myTestBoostXMLLoad.cpp
 *
 *  Created on: 05.05.2017
 *      Author: Alexander P.
 */
/*
 #include <xercesc/util/PlatformUtils.hpp>
 #include <xercesc/util/XMLString.hpp>
 #include <xercesc/dom/DOM.hpp>
 #include <xercesc/util/OutOfMemoryException.hpp>
 */
#include "TestModel.hpp"

//#include "myTestBoost/myTestBoostXMLLoad.hpp"
//#include "myTestXerces/MyTestXerces.hpp"

#include "persistence/Persistence.hpp"

#include <stdlib.h>

int main () {
	try {
		// Get MetaPackage
		std::cout << "| INFO     | " << "Get 'myEcoreMetaMetaPackage'" << std::endl;
		std::shared_ptr<ecore::EPackage> myEcoreMetaMetaPackage = testmodel::TestModel::getMetaMetaPackage();
		if ( myEcoreMetaMetaPackage == 0 ) {
			std::cout << "| ERROR    | " << "'myEcoreMetaMetaPackage' is empty" << std::endl;
			return 0;
		}

		// Create Save-Model
		std::cout << "| INFO     | " << "Create 'myEcoreTestSaveMetaModel'" << std::endl;
		std::shared_ptr<ecore::EObject> myEcoreTestSaveMetaModel = testmodel::TestModel::createEcoreTestMetaModel();
		if ( myEcoreTestSaveMetaModel == 0 ) {
			std::cout << "| ERROR    | " << "'myEcoreTestSaveMetaModel' is empty" << std::endl;
			return 0;
		}

		// Set Options
		std::cout << "| INFO     | " << "Get 'options'" << std::endl;
		std::set<std::string> options = persistence::Option::get_DefaultOptions();

		// Crete persistence object
		persistence::Persistence myPersistence;

		// Set filename with path
		std::string filename = "_tmp/UniModel.ecore";
		std::string filename2 = "_tmp/UniModel2.ecore";

		// Perform save()
		std::cout << "| INFO     | " << "Start save() of 'myEcoreTestSaveMetaModel'" << std::endl;

		if ( myPersistence.save( filename, myEcoreTestSaveMetaModel, myEcoreMetaMetaPackage, options ) ) {

			std::cout << "| INFO     | " << "Successful save() 'myEcoreTestSaveMetaModel' to '" << filename.c_str() << "'" << std::endl;
		}
		else {
			std::cout << "| ERROR    | " << "During save() of 'myEcoreTestSaveMetaModel'" << std::endl;
		}

		// Create Load-Model
		std::cout << "| INFO     | " << "Create 'myEcoreTestLoadMetaModel'" << std::endl;
		std::shared_ptr<ecore::EObject> myEcoreTestLoadMetaModel;

		// Perform load()
		std::cout << "| INFO     | " << "Start load() of 'myEcoreTestSaveMetaModel'" << std::endl;
		myEcoreTestLoadMetaModel = myPersistence.load( filename, options );
		if ( myEcoreTestLoadMetaModel != nullptr ) {
			std::cout << "| INFO     | " << "Successful load() of 'myEcoreTestLoadMetaModel' from '" << filename << "'" << std::endl;
		}
		else {
			std::cout << "| ERROR    | " << "During load() of 'myEcoreTestLoadMetaModel'" << std::endl;
		}

		// Perform save() again
		std::cout << "| INFO     | " << "Start save() of 'myEcoreTestLoadMetaModel'" << std::endl;

		if ( myPersistence.save( filename2, myEcoreTestLoadMetaModel, myEcoreMetaMetaPackage, options ) ) {

			std::cout << "| INFO     | " << "Successful save() 'myEcoreTestSaveMetaModel' to '" << filename2 << "'" << std::endl;
		}
		else {
			std::cout << "| ERROR    | " << "During save() of 'myEcoreTestLoadMetaModel'" << std::endl;
		}
	}
	catch ( std::exception &e ) {
		std::cout << "| ERROR    | " << e.what() << std::endl;
	}
	return 0;
}
