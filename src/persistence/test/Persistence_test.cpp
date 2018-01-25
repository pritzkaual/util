/*
 * Persistence_test.cpp
 *
 *  Created on: 05.05.2017
 *      Author: Alexander P.
 */

#include <omp.h>
#include <stdlib.h>

#include "persistence/xml/XMLPersistence.hpp"
#include "TestModel.hpp"

#include "EPackage.hpp"
#include "EObject.hpp"

int main () {
	try {
		// Set OpenMP number of threads
		omp_set_num_threads(1);

		// Set filename with path
		std::string filename = "_tmp/UniModel.ecore";
		std::string filename2 = "_tmp/UniModel_out.ecore";
		std::string filename3 = "_tmp/xmi.ecore";
		std::string filename4 = "_tmp/xmi_out.ecore";

		// Get MetaPackage
		std::cout << "| INFO     | " << "Get 'myEcoreMetaMetaPackage'" << std::endl;
		std::shared_ptr<ecore::EPackage> myEcoreMetaMetaPackage = testmodel::TestModel::getMetaMetaPackage();
		if ( myEcoreMetaMetaPackage == 0 )
		{
			std::cout << "| ERROR    | " << "'myEcoreMetaMetaPackage' is empty" << std::endl;
			return 0;
		}

		// Create Save-Model
		std::cout << "| INFO     | " << "Create 'myEcoreTestSaveMetaModel'" << std::endl;
		std::shared_ptr<ecore::EObject> myEcoreTestSaveMetaModel = testmodel::TestModel::createEcoreTestMetaModel();
		if ( myEcoreTestSaveMetaModel == 0 )
		{
			std::cout << "| ERROR    | " << "'myEcoreTestSaveMetaModel' is empty" << std::endl;
			return 0;
		}
		// Create Load-Model
		std::cout << "| INFO     | " << "Create 'myEcoreTestLoadMetaModel'" << std::endl;
		std::shared_ptr<ecore::EObject> myEcoreTestLoadMetaModel;


		// Crete persistence object
		persistence::xml::XMLPersistence myPersistence;
#if 0
		// Perform save()
		std::cout << "| INFO     | " << "Start save() of 'myEcoreTestSaveMetaModel'" << std::endl;

		if ( myPersistence.save( filename, myEcoreTestSaveMetaModel, myEcoreMetaMetaPackage ) ) {

			std::cout << "| INFO     | " << "Successful save() 'myEcoreTestSaveMetaModel' to '" << filename.c_str() << "'" << std::endl;
		}
		else
		{
			std::cout << "| ERROR    | " << "During save() of 'myEcoreTestSaveMetaModel'" << std::endl;
		}

		// Perform load()
		std::cout << "| INFO     | " << "Start load() of 'myEcoreTestSaveMetaModel'" << std::endl;
		myEcoreTestLoadMetaModel = myPersistence.load( filename );
		if ( myEcoreTestLoadMetaModel != nullptr )
		{
			std::cout << "| INFO     | " << "Successful load() of 'myEcoreTestLoadMetaModel' from '" << filename << "'" << std::endl;
		}
		else {
			std::cout << "| ERROR    | " << "During load() of 'myEcoreTestLoadMetaModel'" << std::endl;
		}

		// Perform save() again
		std::cout << "| INFO     | " << "Start save() of 'myEcoreTestLoadMetaModel'" << std::endl;

		if ( myPersistence.save( filename2, myEcoreTestLoadMetaModel, myEcoreMetaMetaPackage ) )
		{
			std::cout << "| INFO     | " << "Successful save() 'myEcoreTestSaveMetaModel' to '" << filename2 << "'" << std::endl;
		}
		else {
			std::cout << "| ERROR    | " << "During save() of 'myEcoreTestLoadMetaModel'" << std::endl;
		}
#endif
		// Perform load() on unknown model
		std::cout << "| INFO     | " << "Start load() of 'myEcoreTestSaveMetaModel'" << std::endl;
		myEcoreTestLoadMetaModel = myPersistence.load( filename3 );
		if ( myEcoreTestLoadMetaModel != nullptr )
		{
			std::cout << "| INFO     | " << "Successful load() of 'myEcoreTestLoadMetaModel' from '" << filename3 << "'" << std::endl;
		}
		else
		{
			std::cout << "| ERROR    | " << "During load() of 'myEcoreTestLoadMetaModel'" << std::endl;
		}

		// Perform save() again
		std::cout << "| INFO     | " << "Start save() of 'myEcoreTestLoadMetaModel'" << std::endl;

		if ( myPersistence.save( filename4, myEcoreTestLoadMetaModel, myEcoreMetaMetaPackage ) )
		{
			std::cout << "| INFO     | " << "Successful save() 'myEcoreTestSaveMetaModel' to '" << filename4 << "'" << std::endl;
		}
		else {
			std::cout << "| ERROR    | " << "During save() of 'myEcoreTestLoadMetaModel'" << std::endl;
		}
	}
	catch ( std::exception &e )
	{
		std::cout << "| ERROR    | " << e.what() << std::endl;
	}
	return 0;
}
