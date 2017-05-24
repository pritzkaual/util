/*
 * main_myTestBoostXMLLoad.cpp
 *
 *  Created on: 05.05.2017
 *      Author: Alexander P.
 */

#include "myTestBoostXMLLoad.hpp"

//#include "EClass.hpp"
//#include "EPackage.hpp"
//#include "EAnnotation.hpp"
#include "EcoreFactory.hpp"
#include "EcorePackage.hpp"
//#include "EClassifier.hpp"
//#include "impl/EcorePackageImpl.hpp"
//#include "EStructuralFeature.hpp"
//#include "EReference.hpp"
//#include "EStringToStringMapEntry.hpp"
//#include "impl/EPackageImpl.hpp"
#include "impl/EcoreFactoryImpl.hpp"

//#include "types/TypesFactory.hpp"
//#include "types/TypesPackage.hpp"

#include "persistence/Persistence.hpp"

#include <stdlib.h>

//using namespace ecore;

std::shared_ptr<ecore::EObject> createEcoreTestMetaModel () {

	std::shared_ptr<ecore::EcorePackage> package = ecore::EcorePackage::eInstance();
	std::shared_ptr<ecore::EcoreFactory> factory = ecore::EcoreFactory::eInstance();

	// Create package 'pck_UniModel' and set some default package information
	std::shared_ptr<ecore::EPackage> pck_UniModel( factory->createEPackage() );
	{
		pck_UniModel->setName( "UniModelPackage" );
		pck_UniModel->setNsPrefix( "Uni" );
		pck_UniModel->setNsURI( "http://www.examples.org/Uni" );
	}

	// get subpackage list from UniModel
	std::shared_ptr<std::vector<std::shared_ptr<ecore::EPackage>>>subpackages = pck_UniModel->getESubpackages();

	// Create new subpackage and insert into package 'pck_UniModel'
	std::shared_ptr<ecore::EPackage> pck_enum; // ptr anlegen bzw. initialisieren
	{
		pck_enum.reset( factory->createEPackage() ); // inhalt resetten bzw. ersetzten durch methoden aufruf
		std::shared_ptr<ecore::EPackageImpl> pck_enum_Impl = std::dynamic_pointer_cast<ecore::EPackageImpl>( pck_enum ); // shared_ptr casten
		{
			// set name and prefix of subpackage
			pck_enum->setName( "EnumPackage" );
			pck_enum->setNsPrefix( "enum" );
		}
		// add packages to subpackage list
		subpackages->push_back( pck_enum );
	}

	// Create new subpackage and insert into package 'pck_UniModel' (alternative variant)
	std::shared_ptr<ecore::EPackage> pck_class( factory->createEPackage() );
	{
		std::shared_ptr<ecore::EPackageImpl> pck_class_Impl = std::dynamic_pointer_cast<ecore::EPackageImpl>( pck_class ); // shared_ptr casten
		{
			// set name and prefix of subpackage
			pck_class->setName( "ClassPackage" );
			pck_class->setNsPrefix( "cls" );
		}
		// add packages to subpackage list
		subpackages->push_back( pck_class );
	}

	// Create ENUMs that are used in classes
	std::shared_ptr<ecore::EEnum> enum_Geschlecht( factory->createEEnum() );
	{
		enum_Geschlecht->setName( "EnumGeschlecht" );

		// Create const attributes (literals)
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EEnumLiteral>>>list_ELiteral = enum_Geschlecht->getELiterals();
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "MAENNLICH" );
			literal->setLiteral( "MAENNLICH" );
			literal->setValue( 0 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "WEIBLICH" );
			literal->setLiteral( "WEIBLICH" );
			literal->setValue( 1 );

			list_ELiteral->push_back( literal );
		}
	}

	std::shared_ptr<ecore::EEnum> enum_Verein( factory->createEEnum() );
	{
		enum_Verein->setName( "EnumVerein" );

		// Create const attributes (literals)
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EEnumLiteral>>>list_ELiteral = enum_Verein->getELiterals();
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "BC" );
			literal->setLiteral( "BC" );
			literal->setValue( 0 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "BD" );
			literal->setLiteral( "BD" );
			literal->setValue( 1 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "BH" );
			literal->setLiteral( "BH" );
			literal->setValue( 2 );

			list_ELiteral->push_back( literal );
		}
	}

	std::shared_ptr<ecore::EEnum> enum_Position( factory->createEEnum() );
	{
		enum_Position->setName( "EnumPosition" );

		// Create const attributes (literals)
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EEnumLiteral>>>list_ELiteral = enum_Position->getELiterals();
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "PROFESSOR" );
			literal->setLiteral( "PROFESSOR" );
			literal->setValue( 0 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "WMA" );
			literal->setLiteral( "WMA" );
			literal->setValue( 1 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "HIWI" );
			literal->setLiteral( "HIWI" );
			literal->setValue( 2 );

			list_ELiteral->push_back( literal );
		}

	}

	std::shared_ptr<ecore::EEnum> enum_StudentStatus( factory->createEEnum() );
	{
		enum_StudentStatus->setName( "EnumStudentStatus" );

		// Create const attributes (literals)
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EEnumLiteral>>>list_ELiteral = enum_StudentStatus->getELiterals();
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "BACHELOR" );
			literal->setLiteral( "BACHELOR" );
			literal->setValue( 0 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "MASTER" );
			literal->setLiteral( "MASTER" );
			literal->setValue( 1 );

			list_ELiteral->push_back( literal );
		}

	}

	std::shared_ptr<ecore::EEnum> enum_Veranstaltung( factory->createEEnum() );

	{
		enum_Veranstaltung->setName( "EnumVeranstaltung" );

		// Create const attributes (literals)
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EEnumLiteral>>>list_ELiteral = enum_Veranstaltung->getELiterals();
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "VORLESUNG" );
			literal->setLiteral( "VORLESUNG" );
			literal->setValue( 0 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "SEMINAR" );
			literal->setLiteral( "SEMINAR" );
			literal->setValue( 1 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral() );
			literal->setName( "PRAKTIKUM" );
			literal->setLiteral( "PRAKTIKUM" );
			literal->setValue( 2 );

			list_ELiteral->push_back( literal );
		}

	}

	// Init List of ENUMs
	std::shared_ptr<std::vector<std::shared_ptr<ecore::EClassifier>>>list_pck_enum = pck_enum->getEClassifiers();

	// Insert ENUMs into list
	list_pck_enum->push_back( enum_Geschlecht );
	list_pck_enum->push_back( enum_Verein );
	list_pck_enum->push_back( enum_Position );
	list_pck_enum->push_back( enum_StudentStatus );
	list_pck_enum->push_back( enum_Veranstaltung );

	// Create some classes with attributes, operations, compositions and association to each other
	std::shared_ptr<ecore::EClass> cls_UniModel( factory->createEClass() );
	{
		cls_UniModel->setName( "UniModel" );

		// Create attributes, set their names and types
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EAttribute>>>list_EAttribute = cls_UniModel->getEAttributes();
		{
		}
	}

	std::shared_ptr<ecore::EClass> cls_Universitaet( factory->createEClass() );
	{
		cls_Universitaet->setName( "Universitaet" );

		// Create attributes, set their names and types
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EAttribute>>>list_EAttribute = cls_Universitaet->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "name" );
			attrib->setEType( package->getEString() );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
	}

	std::shared_ptr<ecore::EClass> cls_Mensch( factory->createEClass() );
	{
		cls_Mensch->setName( "Mensch" );

		// Create attributes, set their names and types
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EAttribute>>>list_EAttribute = cls_Mensch->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "lastname" );
			attrib->setEType( package->getEString() );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "firstname" );
			attrib->setEType( package->getEString() );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "sex" );
			attrib->setEType( enum_Geschlecht );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
	}

	std::shared_ptr<ecore::EClass> cls_Person( factory->createEClass() );
	{
		cls_Person->setName( "Person" );
		cls_Person->setInterface( true );

		// Add SuperType
		{
			std::shared_ptr<std::vector<std::shared_ptr<ecore::EClass>>>list_ESuperTypes = cls_Person->getESuperTypes();
			list_ESuperTypes->push_back(cls_Mensch);
		}

		// Create attributes, set their names and types
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EAttribute>>>list_EAttribute = cls_Person->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "id" );
			attrib->setEType( package->getEBigInteger() );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}

		// Create operations, set their names and types
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EOperation>>>list_EOperation = cls_Person->getEOperations();
		{
			std::shared_ptr<ecore::EOperation> operation( factory->createEOperation() );

			operation->setName( "addVeranstaltung" ); // Type: void
			//operation->setEType(void)

			// Add operation to list
			list_EOperation->push_back( operation );
		}
	}

	std::shared_ptr<ecore::EClass> cls_Mitarbeiter( factory->createEClass() );
	{
		cls_Mitarbeiter->setName( "Mitarbeiter" );

		// Add SuperType
		{
			std::shared_ptr<std::vector<std::shared_ptr<ecore::EClass>>>list_ESuperTypes = cls_Mitarbeiter->getESuperTypes();
			list_ESuperTypes->push_back(cls_Person);
		}

		// Create attributes, set their names and types
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EAttribute>>>list_EAttribute = cls_Mitarbeiter->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "position" );
			attrib->setEType( enum_Position );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "gehalt" );
			attrib->setEType( package->getEFloat() );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "office" );
			attrib->setEType( package->getEString() );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
	}

	std::shared_ptr<ecore::EClass> cls_Student( factory->createEClass() );
	{
		cls_Student->setName( "Student" );

		// Add SuperType
		{
			std::shared_ptr<std::vector<std::shared_ptr<ecore::EClass>>>list_ESuperTypes = cls_Student->getESuperTypes();
			list_ESuperTypes->push_back(cls_Person);
		}

		// Create attributes, set their names and types
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EAttribute>>>list_EAttribute = cls_Student->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "status" );
			attrib->setEType( enum_StudentStatus );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}

	}

	std::shared_ptr<ecore::EClass> cls_Veranstaltung( factory->createEClass() );
	{
		cls_Veranstaltung->setName( "Veranstaltung" );

		// Create attributes, set their names and types
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EAttribute>>>list_EAttribute = cls_Veranstaltung->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "name" );
			attrib->setEType( enum_Veranstaltung );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "maxTeilnehmer" );
			attrib->setEType( package->getEInt() );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
	}

	std::shared_ptr<ecore::EClass> cls_Verein( factory->createEClass() );
	{
		cls_Verein->setName( "Verein" );

		// Create attributes, set their names and types
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EAttribute>>>list_EAttribute = cls_Veranstaltung->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "name" );
			attrib->setEType( enum_Verein );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
	}

	// Init List of ENUMs
	std::shared_ptr<std::vector<std::shared_ptr<ecore::EClassifier>>>list_pck_class = pck_class->getEClassifiers();

	// Insert ENUMs into list
	list_pck_class->push_back( cls_UniModel );
	list_pck_class->push_back( cls_Universitaet );
	list_pck_class->push_back( cls_Mensch );
	list_pck_class->push_back( cls_Person );
	list_pck_class->push_back( cls_Mitarbeiter );
	list_pck_class->push_back( cls_Student );
	list_pck_class->push_back( cls_Veranstaltung );
	list_pck_class->push_back( cls_Verein );

	// Create Compositions and Associations
	{
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EReference>>>list_association = cls_UniModel->getEReferences();
		std::shared_ptr<ecore::EReference> reference( factory->createEReference() );

		reference->setName("universitaet");
		// TODO hier muss eine Art setEreferencetype sein, damit ich der Association die zugehoerige class zuweisen kann
		//reference->set

		list_association->push_back(reference);
	}










	for ( std::shared_ptr<ecore::EPackage> subpackage : *subpackages ) {
		std::cout << subpackage->getName() << std::endl;
	}

	return std::dynamic_pointer_cast<ecore::EObject>( pck_UniModel );
}



void print () {

}

int main () {
	try {
		testBoostXMLLoad::myTestBoostXMLLoad myObject;
		//myObject.load("_tmp/debug_settings.xml");
		//myObject.save("_tmp/debug_settings_out.xml");

		auto myEcoreTestMetaModel = createEcoreTestMetaModel();

		myObject.load( "_tmp/uml.ecore" );
		myObject.save( "_tmp/uml_out.ecore" );

		std::cout << "Success\n";
	}
	catch ( std::exception &e ) {
		std::cout << "Error: " << e.what() << "\n";
	}
	return 0;
}
