/*
 * TestModel.cpp
 *
 *  Created on: 23.06.2017
 *      Author: Alexander
 */

#include "TestModel.hpp"

namespace testmodel {

TestModel::TestModel () {
	// TODO Auto-generated constructor stub
}

TestModel::~TestModel () {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<ecore::EPackage> TestModel::getMetaMetaPackage () {
	return ecore::EcorePackage::eInstance();

}
std::shared_ptr<ecore::EObject> TestModel::createEcoreTestMetaModel () {

	std::shared_ptr<ecore::EcorePackage> package = ecore::EcorePackage::eInstance();
	std::shared_ptr<ecore::EcoreFactory> factory = ecore::EcoreFactory::eInstance();

	// Create package 'pck_UniModel' and set some default package information
	std::shared_ptr<ecore::EPackage> pck_UniModel = factory->createEPackage() ;
	{
		pck_UniModel->setName( "UniModelPackage" );
		pck_UniModel->setNsPrefix( "Uni" );
		pck_UniModel->setNsURI( "http://www.examples.org/Uni" );
	}

	// get subpackage list from UniModel
	std::shared_ptr<Bag<ecore::EPackage>> subpackages = pck_UniModel->getESubpackages();

	// Create new subpackage 'pck_enum' and insert into package 'pck_UniModel'
	std::shared_ptr<ecore::EPackage> pck_enum( factory->createEPackage_in_ESuperPackage(pck_UniModel) );
	{

		//std::shared_ptr<ecore::EPackageImpl> pck_enum_Impl = std::dynamic_pointer_cast<ecore::EPackageImpl>( pck_enum ); // shared_ptr casten
		{
			// set name and prefix of subpackage
			pck_enum->setName( "EnumPackage" );
			pck_enum->setNsPrefix( "enum" );
		}
		// add packages to subpackage list
		subpackages->push_back( pck_enum );
		//pck_enum->setContainer(pck_UniModel); // this does not add the superpackage
	}

	// Create new subpackage and insert into package 'pck_UniModel' (alternative variant)
	std::shared_ptr<ecore::EPackage> pck_class( factory->createEPackage_in_ESuperPackage(pck_UniModel) );
	{
		//std::shared_ptr<ecore::EPackageImpl> pck_class_Impl = std::dynamic_pointer_cast<ecore::EPackageImpl>( pck_class ); // shared_ptr casten
		{
			// set name and prefix of subpackage
			pck_class->setName( "ClassPackage" );
			pck_class->setNsPrefix( "cls" );
		}
		// add packages to subpackage list
		subpackages->push_back( pck_class );

		//pck_class->setContainer(pck_UniModel);
		//std::shared_ptr<ecore::EPackage>superpackage = pck_class->getESuperPackage();
		//superpackage = pck_UniModel; // TODO hier funkt das mit dem SuperPackage nicht
	}

	// Create ENUMs that are used in classes
	std::shared_ptr<ecore::EEnum> enum_Geschlecht( factory->createEEnum_in_EPackage(pck_enum) );
	{
		enum_Geschlecht->setName( "EnumGeschlecht" );
		//enum_Geschlecht->setEPackage(pck_enum);

		// Create const attributes (literals)
		std::shared_ptr<Bag<ecore::EEnumLiteral>> list_ELiteral = enum_Geschlecht->getELiterals();
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_Geschlecht) );
			literal->setName( "MAENNLICH" );
			literal->setLiteral( "MAENNLICH" );
			literal->setValue( 0 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_Geschlecht) );
			literal->setName( "WEIBLICH" );
			literal->setLiteral( "WEIBLICH" );
			literal->setValue( 1 );

			list_ELiteral->push_back( literal );
		}
	}

	std::shared_ptr<ecore::EEnum> enum_Verein( factory->createEEnum_in_EPackage(pck_enum) );
	{
		enum_Verein->setName( "EnumVerein" );
		//enum_Verein->setEPackage(pck_enum);

		// Create const attributes (literals)
		std::shared_ptr<Bag<ecore::EEnumLiteral>> list_ELiteral = enum_Verein->getELiterals();
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_Verein) );
			literal->setName( "BC" );
			literal->setLiteral( "BC" );
			literal->setValue( 0 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_Verein) );
			literal->setName( "BD" );
			literal->setLiteral( "BD" );
			literal->setValue( 1 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_Verein) );
			literal->setName( "BH" );
			literal->setLiteral( "BH" );
			literal->setValue( 2 );

			list_ELiteral->push_back( literal );
		}
	}

	std::shared_ptr<ecore::EEnum> enum_Position( factory->createEEnum_in_EPackage(pck_enum) );
	{
		enum_Position->setName( "EnumPosition" );
		//enum_Position->setEPackage(pck_enum);

		// Create const attributes (literals)
		std::shared_ptr<Bag<ecore::EEnumLiteral>> list_ELiteral = enum_Position->getELiterals();
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_Position) );
			literal->setName( "PROFESSOR" );
			literal->setLiteral( "PROFESSOR" );
			literal->setValue( 0 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_Position) );
			literal->setName( "WMA" );
			literal->setLiteral( "WMA" );
			literal->setValue( 1 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_Position) );
			literal->setName( "HIWI" );
			literal->setLiteral( "HIWI" );
			literal->setValue( 2 );

			list_ELiteral->push_back( literal );
		}

	}

	std::shared_ptr<ecore::EEnum> enum_StudentStatus( factory->createEEnum_in_EPackage(pck_enum) );
	{
		enum_StudentStatus->setName( "EnumStudentStatus" );
		//enum_StudentStatus->setEPackage(pck_enum);

		// Create const attributes (literals)
		std::shared_ptr<Bag<ecore::EEnumLiteral>> list_ELiteral = enum_StudentStatus->getELiterals();
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_StudentStatus) );
			literal->setName( "BACHELOR" );
			literal->setLiteral( "BACHELOR" );
			literal->setValue( 0 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_StudentStatus) );
			literal->setName( "MASTER" );
			literal->setLiteral( "MASTER" );
			literal->setValue( 1 );

			list_ELiteral->push_back( literal );
		}

	}

	std::shared_ptr<ecore::EEnum> enum_Veranstaltung( factory->createEEnum_in_EPackage(pck_enum) );
	{
		enum_Veranstaltung->setName( "EnumVeranstaltung" );
		//enum_Veranstaltung->setEPackage(pck_enum);

		// Create const attributes (literals)
		std::shared_ptr<Bag<ecore::EEnumLiteral>> list_ELiteral = enum_Veranstaltung->getELiterals();
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_Veranstaltung) );
			literal->setName( "VORLESUNG" );
			literal->setLiteral( "VORLESUNG" );
			literal->setValue( 0 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_Veranstaltung) );
			literal->setName( "SEMINAR" );
			literal->setLiteral( "SEMINAR" );
			literal->setValue( 1 );

			list_ELiteral->push_back( literal );
		}
		{
			std::shared_ptr<ecore::EEnumLiteral> literal( factory->createEEnumLiteral_in_EEnum(enum_Veranstaltung) );
			literal->setName( "PRAKTIKUM" );
			literal->setLiteral( "PRAKTIKUM" );
			literal->setValue( 2 );

			list_ELiteral->push_back( literal );
		}

	}

	// Init List of ENUMs
	std::shared_ptr<Bag<ecore::EClassifier>> list_pck_enum = pck_enum->getEClassifiers();

	// Insert ENUMs into list (package EnumPackage)
	list_pck_enum->push_back( enum_Geschlecht );
	list_pck_enum->push_back( enum_Verein );
	list_pck_enum->push_back( enum_Position );
	list_pck_enum->push_back( enum_StudentStatus );
	list_pck_enum->push_back( enum_Veranstaltung );


	// Create some classes with attributes, operations, compositions and association to each other
	std::shared_ptr<ecore::EClass> cls_UniModel( factory->createEClass_in_EPackage(pck_class) );
	{
		cls_UniModel->setName( "UniModel" );
		cls_UniModel->setInterface( false );
		cls_UniModel->setAbstract( false );

		// Create attributes, set their names and types
		std::shared_ptr<Bag<ecore::EAttribute>> list_EAttribute = cls_UniModel->getEAttributes();
		{
		}
	}

	std::shared_ptr<ecore::EClass> cls_Universitaet( factory->createEClass_in_EPackage(pck_class) );
	{
		cls_Universitaet->setName( "Universitaet" );
		cls_Universitaet->setInterface( false );
		cls_Universitaet->setAbstract( false );

		// Create attributes, set their names and types
		std::shared_ptr<Bag<ecore::EAttribute>> list_EAttribute = cls_Universitaet->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "name" );
			attrib->setEType( package->getEString() );

			attrib->setID( false );
			attrib->setOrdered( true ); // default: ordered=true
			attrib->setUnique( true ); // default: unique=true
			attrib->setLowerBound( 0 );
			attrib->setUpperBound( 1 ); // default: upperBound=1
			attrib->setChangeable( true );
			attrib->setVolatile( true );
			attrib->setTransient( false );
			attrib->setDefaultValueLiteral( "" );
			attrib->setUnsettable( false );
			attrib->setDerived( false );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
	}

	std::shared_ptr<ecore::EClass> cls_Mensch( factory->createEClass_in_EPackage(pck_class) );
	{
		cls_Mensch->setName( "Mensch" );
		cls_Mensch->setInterface( false );
		cls_Mensch->setAbstract( false );

		// Create attributes, set their names and types
		std::shared_ptr<Bag<ecore::EAttribute>> list_EAttribute = cls_Mensch->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "lastname" );
			attrib->setEType( package->getEString() );

			attrib->setID( false );
			attrib->setOrdered( true ); // default: ordered=true
			attrib->setUnique( true ); // default: unique=true
			attrib->setLowerBound( 0 );
			attrib->setUpperBound( 1 ); // default: upperBound=1
			attrib->setChangeable( true );
			attrib->setVolatile( true );
			attrib->setTransient( false );
			attrib->setDefaultValueLiteral( "" );
			attrib->setUnsettable( false );
			attrib->setDerived( false );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "firstname" );
			attrib->setEType( package->getEString() );

			attrib->setID( false );
			attrib->setOrdered( true ); // default: ordered=true
			attrib->setUnique( true ); // default: unique=true
			attrib->setLowerBound( 0 );
			attrib->setUpperBound( 1 ); // default: upperBound=1
			attrib->setChangeable( true );
			attrib->setVolatile( true );
			attrib->setTransient( false );
			attrib->setDefaultValueLiteral( "" );
			attrib->setUnsettable( false );
			attrib->setDerived( false );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "sex" );
			attrib->setEType( enum_Geschlecht );

			attrib->setID( false );
			attrib->setOrdered( true ); // default: ordered=true
			attrib->setUnique( true ); // default: unique=true
			attrib->setLowerBound( 0 );
			attrib->setUpperBound( 1 ); // default: upperBound=1
			attrib->setChangeable( true );
			attrib->setVolatile( true );
			attrib->setTransient( false );
			attrib->setDefaultValueLiteral( "" );
			attrib->setUnsettable( false );
			attrib->setDerived( false );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
	}

	std::shared_ptr<ecore::EClass> cls_Person( factory->createEClass_in_EPackage(pck_class) );
	{
		cls_Person->setName( "Person" );
		cls_Person->setInterface( true );
		cls_Person->setAbstract( false );

		// Add SuperType
		{
			std::shared_ptr<Bag<ecore::EClass>> list_ESuperTypes = cls_Person->getESuperTypes();
			list_ESuperTypes->push_back( cls_Mensch );
		}

		// Create attributes, set their names and types
		std::shared_ptr<Bag<ecore::EAttribute>> list_EAttribute = cls_Person->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "id" );
			attrib->setEType( package->getEBigInteger() );

			attrib->setID( false );
			attrib->setOrdered( true ); // default: ordered=true
			attrib->setUnique( true ); // default: unique=true
			attrib->setLowerBound( 0 );
			attrib->setUpperBound( 1 ); // default: upperBound=1
			attrib->setChangeable( true );
			attrib->setVolatile( true );
			attrib->setTransient( false );
			attrib->setDefaultValueLiteral( "" );
			attrib->setUnsettable( false );
			attrib->setDerived( false );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}

		// Create operations, set their names and types
		std::shared_ptr<Bag<ecore::EOperation>> list_EOperation = cls_Person->getEOperations();
		{
			std::shared_ptr<ecore::EOperation> operation( factory->createEOperation() );

			operation->setName( "addVeranstaltung" ); // Type: void
			operation->setEType( package->getEBoolean() );

			operation->setOrdered( true ); // default: ordered=true
			operation->setUnique( true ); // default: unique=true
			operation->setLowerBound( 0 );
			operation->setUpperBound( 1 ); // default: upperBound=1

			std::shared_ptr<Bag<ecore::EAnnotation>> list_EAnnotation = operation->getEAnnotations();
			{
				std::shared_ptr<ecore::EAnnotation> annotation( factory->createEAnnotation() );

				annotation->setSource( "http://sse.tu-ilmenau.de/codegen" );

				std::shared_ptr<Bag<ecore::EStringToStringMapEntry>> list_EStringToStringMapEntry = annotation->getDetails();
				{
					std::shared_ptr<ecore::EStringToStringMapEntry> stringToStringMapEntry( factory->createEStringToStringMapEntry() );

					stringToStringMapEntry->setKey( "body" );
					stringToStringMapEntry->setValue("    if (someOperation->getEContainingClass()->isSuperTypeOf(getEContainingClass()) &amp;&amp; (someOperation->getName()==getName()))&#xD;&#xA;    {&#xD;&#xA;        std::shared_ptr&lt; Bag&lt;ecore::EParameter> > parameters = getEParameters();&#xD;&#xA;        std::shared_ptr&lt; Bag&lt;ecore::EParameter> > otherParameters = someOperation->getEParameters();&#xD;&#xA;        if (parameters->size() == otherParameters->size())&#xD;&#xA;        {&#xD;&#xA;            for (Bag&lt;EParameter> ::iterator i = parameters->begin(), j = otherParameters->begin(); i != parameters->end(); ++i,++j )&#xD;&#xA;        &#x9;{&#xD;&#xA;            &#x9;std::shared_ptr&lt;EParameter> parameter = *i;&#xD;&#xA;            &#x9;std::shared_ptr&lt;EParameter> otherParameter = *j;&#xD;&#xA;                if (!(parameter->getEType().get() == otherParameter->getEType().get()))&#xD;&#xA;          &#x9;&#x9;{&#xD;&#xA;                    return false;&#xD;&#xA;        &#x9;&#x9;}&#xD;&#xA;        &#x9;}&#xD;&#xA;&#x9;&#x9;}&#xD;&#xA;&#x9;&#x9;return true;&#xD;&#xA;&#x9;}" );

					list_EStringToStringMapEntry->push_back(stringToStringMapEntry);
				}

				list_EAnnotation->push_back( annotation );
			}
			{
				std::shared_ptr<ecore::EAnnotation> annotation( factory->createEAnnotation() );

				annotation->setSource( "http://sse.tu-ilmenau.de/HansPeter" );

				std::shared_ptr<Bag<ecore::EStringToStringMapEntry>> list_EStringToStringMapEntry = annotation->getDetails();
				{
					std::shared_ptr<ecore::EStringToStringMapEntry> stringToStringMapEntry( factory->createEStringToStringMapEntry() );

					stringToStringMapEntry->setKey( "body" );
					stringToStringMapEntry->setValue( "any source \n here is newline \t here is a tabulator" );

					list_EStringToStringMapEntry->push_back(stringToStringMapEntry);
				}

				list_EAnnotation->push_back( annotation );
			}

			// Add operation to list
			list_EOperation->push_back( operation );
		}
		{
			std::shared_ptr<ecore::EOperation> operation( factory->createEOperation() );

			operation->setName( "removeVeranstaltung" ); // Type: void
			operation->setEType( package->getEChar() );

			operation->setOrdered( true ); // default: ordered=true
			operation->setUnique( true ); // default: unique=true
			operation->setLowerBound( 0 );
			operation->setUpperBound( 1 ); // default: upperBound=1

			// Add operation to list
			list_EOperation->push_back( operation );
		}
	}

	std::shared_ptr<ecore::EClass> cls_Mitarbeiter( factory->createEClass_in_EPackage(pck_class) );
	{
		cls_Mitarbeiter->setName( "Mitarbeiter" );
		cls_Mitarbeiter->setInterface( false );
		cls_Mitarbeiter->setAbstract( false );

		// Add SuperType
		{
			std::shared_ptr<Bag<ecore::EClass>> list_ESuperTypes = cls_Mitarbeiter->getESuperTypes();
			list_ESuperTypes->push_back( cls_Person );
		}

		// Create attributes, set their names and types
		std::shared_ptr<Bag<ecore::EAttribute>> list_EAttribute = cls_Mitarbeiter->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "position" );
			attrib->setEType( enum_Position );

			attrib->setID( false );
			attrib->setOrdered( true ); // default: ordered=true
			attrib->setUnique( true ); // default: unique=true
			attrib->setLowerBound( 0 );
			attrib->setUpperBound( 1 ); // default: upperBound=1
			attrib->setChangeable( true );
			attrib->setVolatile( true );
			attrib->setTransient( false );
			attrib->setDefaultValueLiteral( "" );
			attrib->setUnsettable( false );
			attrib->setDerived( false );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "gehalt" );
			attrib->setEType( package->getEFloat() );

			attrib->setID( false );
			attrib->setOrdered( true ); // default: ordered=true
			attrib->setUnique( true ); // default: unique=true
			attrib->setLowerBound( 0 );
			attrib->setUpperBound( 1 ); // default: upperBound=1
			attrib->setChangeable( true );
			attrib->setVolatile( true );
			attrib->setTransient( false );
			attrib->setDefaultValueLiteral( "" );
			attrib->setUnsettable( false );
			attrib->setDerived( false );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "office" );
			attrib->setEType( package->getEString() );

			attrib->setID( false );
			attrib->setOrdered( true ); // default: ordered=true
			attrib->setUnique( true ); // default: unique=true
			attrib->setLowerBound( 0 );
			attrib->setUpperBound( 1 ); // default: upperBound=1
			attrib->setChangeable( true );
			attrib->setVolatile( true );
			attrib->setTransient( false );
			attrib->setDefaultValueLiteral( "" );
			attrib->setUnsettable( false );
			attrib->setDerived( false );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
	}

	std::shared_ptr<ecore::EClass> cls_Student( factory->createEClass_in_EPackage(pck_class) );
	{
		cls_Student->setName( "Student" );
		cls_Student->setInterface( false );
		cls_Student->setAbstract( false );

		// Add SuperType
		{
			std::shared_ptr<Bag<ecore::EClass>> list_ESuperTypes = cls_Student->getESuperTypes();
			list_ESuperTypes->push_back( cls_Person );
		}

		// Create attributes, set their names and types
		std::shared_ptr<Bag<ecore::EAttribute>> list_EAttribute = cls_Student->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute() );

			attrib->setName( "status" );
			attrib->setEType( enum_StudentStatus );

			attrib->setID( false );
			attrib->setOrdered( true ); // default: ordered=true
			attrib->setUnique( true ); // default: unique=true
			attrib->setLowerBound( 0 );
			attrib->setUpperBound( 1 ); // default: upperBound=1
			attrib->setChangeable( true );
			attrib->setVolatile( true );
			attrib->setTransient( false );
			attrib->setDefaultValueLiteral( "" );
			attrib->setUnsettable( false );
			attrib->setDerived( false );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}

	}

	std::shared_ptr<ecore::EClass> cls_Veranstaltung( factory->createEClass_in_EPackage(pck_class) );
	{
		cls_Veranstaltung->setName( "Veranstaltung" );
		cls_Veranstaltung->setInterface( false );
		cls_Veranstaltung->setAbstract( false );

		// Create attributes, set their names and types
		std::shared_ptr<Bag<ecore::EAttribute>> list_EAttribute = cls_Veranstaltung->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute_in_EContainingClass(cls_Veranstaltung) );

			attrib->setName( "name" );
			attrib->setEType( enum_Veranstaltung );

			attrib->setID( false );
			attrib->setOrdered( true ); // default: ordered=true
			attrib->setUnique( true ); // default: unique=true
			attrib->setLowerBound( 0 );
			attrib->setUpperBound( 1 ); // default: upperBound=1
			attrib->setChangeable( true );
			attrib->setVolatile( true );
			attrib->setTransient( false );
			attrib->setDefaultValueLiteral( "" );
			attrib->setUnsettable( false );
			attrib->setDerived( false );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute_in_EContainingClass(cls_Veranstaltung) );

			attrib->setName( "maxTeilnehmer" );
			attrib->setEType( package->getEInt() );

			attrib->setID( false );
			attrib->setOrdered( true ); // default: ordered=true
			attrib->setUnique( true ); // default: unique=true
			attrib->setLowerBound( 0 );
			attrib->setUpperBound( 1 ); // default: upperBound=1
			attrib->setChangeable( true );
			attrib->setVolatile( true );
			attrib->setTransient( false );
			attrib->setDefaultValueLiteral( "" );
			attrib->setUnsettable( false );
			attrib->setDerived( false );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
	}

	std::shared_ptr<ecore::EClass> cls_Verein( factory->createEClass_in_EPackage(pck_class) );
	{
		cls_Verein->setName( "Verein" );
		cls_Verein->setInterface( false );
		cls_Verein->setAbstract( false );

		// Create attributes, set their names and types
		std::shared_ptr<Bag<ecore::EAttribute>> list_EAttribute = cls_Veranstaltung->getEAttributes();
		{
			std::shared_ptr<ecore::EAttribute> attrib( factory->createEAttribute_in_EContainingClass(cls_Veranstaltung) );

			attrib->setName( "name" );
			attrib->setEType( enum_Verein );

			attrib->setID( false );
			attrib->setOrdered( true ); // default: ordered=true
			attrib->setUnique( true ); // default: unique=true
			attrib->setLowerBound( 0 );
			attrib->setUpperBound( 1 ); // default: upperBound=1
			attrib->setChangeable( true );
			attrib->setVolatile( true );
			attrib->setTransient( false );
			attrib->setDefaultValueLiteral( "" );
			attrib->setUnsettable( false );
			attrib->setDerived( false );

			// Add attributes to list
			list_EAttribute->push_back( attrib );
		}
	}

	// Init List of Classes
	std::shared_ptr<Bag<ecore::EClassifier>> list_pck_class = pck_class->getEClassifiers();

	// Insert Classes into list
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
		std::shared_ptr<Bag<ecore::EReference>> list_reference = cls_UniModel->getEReferences();
		{
			std::shared_ptr<ecore::EReference> reference( factory->createEReference_in_EContainingClass(cls_UniModel) );

			reference->setName( "universitaet" );
			// TODO hier muss spater eine Art setEReferenceType verwendet werden.
			reference->setEType( cls_Universitaet );
			//reference->getEReferenceType();
			reference->setContainment( true ); // set reference as composition
			reference->setResolveProxies( true ); // default: resolveProxies=true

			reference->setOrdered( true ); // default: ordered=true
			reference->setUnique( true ); // default: unique=true
			reference->setLowerBound( 0 );
			reference->setUpperBound( -1 ); // default: upperBound=1
			reference->setChangeable( true );
			reference->setVolatile( true );
			reference->setTransient( false );
			reference->setDefaultValueLiteral( "" );
			reference->setUnsettable( false );
			reference->setDerived( false );

			// Add reference to association list
			list_reference->push_back( reference );
		}
	}
	{
		std::shared_ptr<Bag<ecore::EReference>> list_reference = cls_Universitaet->getEReferences();
		{
			std::shared_ptr<ecore::EReference> reference( factory->createEReference_in_EContainingClass(cls_Universitaet) );

			reference->setName( "person" );
			// TODO hier muss spater eine Art setEReferenceType verwendet werden.
			reference->setEType( cls_Person );
			//reference->getEReferenceType();
			reference->setContainment( true );			// set reference as composition
			reference->setResolveProxies( true ); // default: resolveProxies=true

			reference->setOrdered( true ); // default: ordered=true
			reference->setUnique( true ); // default: unique=true
			reference->setLowerBound( 0 );
			reference->setUpperBound( -1 ); // default: upperBound=1
			reference->setChangeable( true );
			reference->setVolatile( true );
			reference->setTransient( false );
			reference->setDefaultValueLiteral( "" );
			reference->setUnsettable( false );
			reference->setDerived( false );

			// Add reference to association list
			list_reference->push_back( reference );
		}
		{
			std::shared_ptr<ecore::EReference> reference( factory->createEReference_in_EContainingClass(cls_Universitaet) );

			reference->setName( "veranstaltung" );
			// TODO hier muss spater eine Art setEReferenceType verwendet werden.
			reference->setEType( cls_Veranstaltung );
			//reference->getEReferenceType();
			reference->setContainment( true );			// set reference as composition
			reference->setResolveProxies( true ); // default: resolveProxies=true

			reference->setOrdered( true ); // default: ordered=true
			reference->setUnique( true ); // default: unique=true
			reference->setLowerBound( 0 );
			reference->setUpperBound( -1 ); // default: upperBound=1
			reference->setChangeable( true );
			reference->setVolatile( true );
			reference->setTransient( false );
			reference->setDefaultValueLiteral( "" );
			reference->setUnsettable( false );
			reference->setDerived( false );

			// Add reference to association list
			list_reference->push_back( reference );
		}
	}
	{
		std::shared_ptr<Bag<ecore::EReference>> list_reference = cls_Person->getEReferences();
		{
			std::shared_ptr<ecore::EReference> reference( factory->createEReference_in_EContainingClass(cls_Person) );

			reference->setName( "veranstaltung" );
			// TODO hier muss spater eine Art setEReferenceType verwendet werden.
			reference->setEType( cls_Veranstaltung );
			//reference->getEReferenceType();
			reference->setContainment( false );			// set reference as association
			reference->setResolveProxies( true ); // default: resolveProxies=true

			reference->setOrdered( true ); // default: ordered=true
			reference->setUnique( true ); // default: unique=true
			reference->setLowerBound( 0 );
			reference->setUpperBound( -1 ); // default: upperBound=1
			reference->setChangeable( true );
			reference->setVolatile( true );
			reference->setTransient( false );
			reference->setDefaultValueLiteral( "" );
			reference->setUnsettable( false );
			reference->setDerived( false );

			// Add reference to association list
			list_reference->push_back( reference );
		}
	}
	{
		std::shared_ptr<Bag<ecore::EReference>> list_reference = cls_Veranstaltung->getEReferences();
		{
			std::shared_ptr<ecore::EReference> reference( factory->createEReference_in_EContainingClass(cls_Veranstaltung) );

			reference->setName( "dozent" );
			// TODO hier muss spater eine Art setEReferenceType verwendet werden.
			reference->setEType( cls_Person );
			//reference->getEReferenceType();
			reference->setContainment( false );			// set reference as association
			reference->setResolveProxies( true ); // default: resolveProxies=true

			reference->setOrdered( true ); // default: ordered=true
			reference->setUnique( true ); // default: unique=true
			reference->setLowerBound( 0 );
			reference->setUpperBound( -1 ); // default: upperBound=1
			reference->setChangeable( true );
			reference->setVolatile( true );
			reference->setTransient( false );
			reference->setDefaultValueLiteral( "" );
			reference->setUnsettable( false );
			reference->setDerived( false );

			// Add reference to association list
			list_reference->push_back( reference );
		}
		{
			std::shared_ptr<ecore::EReference> reference( factory->createEReference_in_EContainingClass(cls_Veranstaltung) );

			reference->setName( "student" );
			// TODO hier muss spater eine Art setEReferenceType verwendet werden.
			reference->setEType( cls_Person );
			//reference->getEReferenceType();
			reference->setContainment( false );			// set reference as association
			reference->setResolveProxies( true ); // default: resolveProxies=true

			reference->setOrdered( true ); // default: ordered=true
			reference->setUnique( true ); // default: unique=true
			reference->setLowerBound( 0 );
			reference->setUpperBound( -1 ); // default: upperBound=1
			reference->setChangeable( true );
			reference->setVolatile( true );
			reference->setTransient( false );
			reference->setDefaultValueLiteral( "" );
			reference->setUnsettable( false );
			reference->setDerived( false );

			// Add reference to association list
			list_reference->push_back( reference );
		}
	}
	{
		std::shared_ptr<Bag<ecore::EReference>> list_reference = cls_Student->getEReferences();
		{
			std::shared_ptr<ecore::EReference> reference( factory->createEReference_in_EContainingClass(cls_Student) );

			reference->setName( "verein" );
			// TODO hier muss spater eine Art setEReferenceType verwendet werden.
			reference->setEType( cls_Verein );
			//reference->getEReferenceType();
			reference->setContainment( false );			// set reference as association
			reference->setResolveProxies( true ); // default: resolveProxies=true

			reference->setOrdered( true ); // default: ordered=true
			reference->setUnique( true ); // default: unique=true
			reference->setLowerBound( 0 );
			reference->setUpperBound( -1 ); // default: upperBound=1
			reference->setChangeable( true );
			reference->setVolatile( true );
			reference->setTransient( false );
			reference->setDefaultValueLiteral( "" );
			reference->setUnsettable( false );
			reference->setDerived( false );

			// Add reference to association list
			list_reference->push_back( reference );
		}
	}

	/*
	 for ( std::shared_ptr<ecore::EPackage> subpackage : *subpackages ) {
	 std::cout << "Sub-Package: " << subpackage->getName() << std::endl;
	 auto wasd = subpackage->eClass();
	 std::cout << wasd->getName() << std::endl;
	 }
	 */
	return std::dynamic_pointer_cast<ecore::EObject>( pck_UniModel );
}

} /* namespace testmodel */
