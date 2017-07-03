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

#include "myTestBoost/myTestBoostXMLLoad.hpp"
#include "myTestXerces/MyTestXerces.hpp"

#include "persistence/Persistence.hpp"

#include <stdlib.h>


int main () {
	try {
		//testBoostXMLLoad::myTestBoostXMLLoad myTestBoostObject;

		//myTestBoostObject.load( "_tmp/uml.ecore" );
		//myTestBoostObject.save( "_tmp/uml_out.ecore" );


 		testXerces::MyTestXerces myXMLObject;
/*
		if ( !myXMLObject.load( "_tmp/uml.ecore" ) && !(myXMLObject.getSawErrors()) ) {

			myXMLObject.save( "_tmp/uml_out.ecore" );
			std::cout << "Successful load() and save() of '_tmp/uml.ecore' \n";
		}
*/

		myXMLObject.createTestDOMDocument();
		//myXMLObject.save( "_tmp/test_out.ecore" );

		std::cout << "START: save() of 'myEcoreTestMetaModel' \n";

		std::shared_ptr<ecore::EObject> myEcoreTestMetaModel = testmodel::TestModel::createEcoreTestMetaModel();

		// Set Options
		std::set<std::string> options = persistence::Option::get_DefaultOptions();
		persistence::Persistence myPersistence;

		myPersistence.save( "_tmp/UniModel.ecore", myEcoreTestMetaModel, options );

		std::cout << "Successful save() of 'myEcoreTestMetaModel' \n";

	}
	catch ( std::exception &e ) {
		std::cout << "Error: " << e.what() << "\n";
	}
	return 0;
}
