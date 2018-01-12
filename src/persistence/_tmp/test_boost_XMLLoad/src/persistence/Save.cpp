/*
 * Save.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "Save.hpp"

namespace persistence {

Save::Save () : m_handler(new persistence::Handler())
{

}

Save::~Save ()
{
	// TODO Auto-generated destructor stub
}

bool Save::save (const std::string &filename, std::shared_ptr<ecore::EObject> model, std::shared_ptr<ecore::EPackage> metaMetaPackage,
		std::set<std::string> options)
{
	m_handler->setMetaMetaPackage( metaMetaPackage );

	std::shared_ptr<ecore::EClass> metaClass = model->eClass();

	std::cout << "| DEBUG    | " << "metaClass: " << metaClass->getName() << std::endl;
	std::cout << "| DEBUG    | " << "metaMetaPck-NS: " << m_handler->getMetaMetaPackage()->getNsPrefix() << std::endl;
	std::cout << "| DEBUG    | " << "metaMetaPck-Uri: " << m_handler->getMetaMetaPackage()->getNsURI() << std::endl;

	m_handler->createRootNode( m_handler->getMetaMetaPackage()->getNsPrefix(), metaClass->getName(), m_handler->getMetaMetaPackage()->getNsURI() );
	m_handler->setRootObj( model );

	std::cout << "| DEBUG    | " << m_handler->extractType(model) << std::endl;

	model->save( m_handler );
	//traverse( m_model, m_handler );
	m_handler->release();

	// Call write() method in corresponding derived class
	return write( filename, m_handler );
}
#if 0
boost::property_tree::ptree Save::traverse ( std::shared_ptr<ecore::EObject> object, boost::property_tree::ptree &tree, const std::string prefix ) {

	std::shared_ptr<ecore::EClass> metaClass = object->eClass();
	std::shared_ptr<ecore::EClass> metaMetaClass = metaClass->eClass();

	//std::cout << metaClass->getName() << std::endl;
	//std::cout << metaMetaClass->getName() << std::endl;

	//boost::property_tree::ptree ctree;

	const int cls_id = metaClass->getClassifierID();

	switch(cls_id) {
		case (ecore::EcorePackage::EPACKAGE):
		{
			std::shared_ptr<ecore::EPackage> tmp_object = std::dynamic_pointer_cast<ecore::EPackage>(object);

			std::cout << "EPackage: " << tmp_object->getName() << std::endl;
			boost::property_tree::ptree &ctree = tree.add_child("ecore:EPackage", boost::property_tree::ptree());

			//std::string tag = prefix;

			//auto name = tmp_object->getName();
			//std::cout << "Object-Name: " << name << std::endl;
			//auto superpackage = tmp_object->getESuperPackage();
			/*
			 if(superpackage == nullptr){
			 std::cout << "no Superpackage" << std::endl;
			 tag += ".ecore:EPackage"; // TODO Correct version: tag = "ecore:EPackage";
			 }else{
			 std::cout << superpackage->getName() << std::endl;
			 tag += ".eSubpackages";

			 }
			 */
			std::cout << "Prefix: " << prefix.c_str() << std::endl;
			//ctree.add(prefix, ""); // add tag

			// Add Attributes
			std::stringstream attr_stream;

			//attr_stream << prefix << ".<xmlattr>." << "name";
			attr_stream << ".<xmlattr>." << "name";
			//std::cout << attr_stream.str() << std::endl;
			ctree.add((std::string)attr_stream.str(), tmp_object->getName());
			//ctree.add((std::string)attr_stream.str(), tmp_object->getName());
			attr_stream.str("");// Reset attr_stream

			//attr_stream << prefix << ".<xmlattr>." << "nsPrefix";
			attr_stream << ".<xmlattr>." << "nsPrefix";
			//std::cout << attr_stream.str() << std::endl;
			ctree.add((std::string)attr_stream.str(), tmp_object->getNsPrefix());
			//ctree.add((std::string)attr_stream.str(), tmp_object->getNsPrefix());
			attr_stream.str("");// Reset attr_stream

			//attr_stream << prefix << ".<xmlattr>." << "nsURI";
			attr_stream << ".<xmlattr>." << "nsURI";
			//std::cout << attr_stream.str() << std::endl;
			ctree.add((std::string)attr_stream.str(), tmp_object->getNsURI());
			//ctree.add((std::string)attr_stream.str(), tmp_object->getNsURI());
			attr_stream.str("");// Reset attr_stream

			//std::cout << "prefix_stream: "<< prefix_stream.str()<< std::endl;
			ctree.add("wasd", "wad");
			ctree.add("wasd", "wad");
			/*
			 std::shared_ptr<Bag<ecore::EStructuralFeature>>>list_attrib = metaClass->getEAllStructuralFeatures();

			 for ( std::shared_ptr<ecore::EStructuralFeature> eStructFeat : *list_attrib ) {

			 }
			 */
			/*
			 std::shared_ptr<Bag<ecore::EAnnotation>>>list_annotations = tmp_object->getEAnnotations();
			 if(list_annotations->size()){
			 boost::property_tree::ptree annotations;

			 for ( std::shared_ptr<ecore::EAnnotation> eAnnotation : *list_annotations ) {
			 annotations.push_back(std::make_pair("" , traverse(eAnnotation, tree, prefix + "eAnnotations")));
			 }
			 ctree.add_child(prefix + ".eAnnotations", annotations);
			 }
			 */
			/*
			 std::shared_ptr<Bag<ecore::EClassifier>>>list_classifiers = tmp_object->getEClassifiers();
			 for ( std::shared_ptr<ecore::EClassifier> eClassifier : *list_classifiers ) {
			 traverse(eClassifier, ctree, prefix + ".eClassifiers");
			 }
			 */

			return tree;

			std::shared_ptr<Bag<ecore::EPackage>>list_subpackages = tmp_object->getESubpackages();
			if(list_subpackages->size()) {
				boost::property_tree::ptree subpackages;
				boost::property_tree::ptree subpackage;

				attr_stream << ".<xmlattr>." << " name";

				/*ctree.add_child()
				 ctree.add(prefix + ".eSubpackages" + (std::string)attr_stream.str(), tmp_object->getNsURI());
				 ctree.add(prefix + ".eSubpackages" + ".eSubpackages", "Test");
				 ctree.add(prefix + ".eSubpackages" + ".eSubpackages", "Test2");
				 ctree.add(prefix + ".eSubpackages" + ".eSubpackages" + (std::string)attr_stream.str(), tmp_object->getNsURI());
				 ctree.add(prefix + ".eSubpackages" + ".eSubpackages" + ".Test2" + (std::string)attr_stream.str(), tmp_object->getNsURI());
				 */
				subpackage = tree.add_child("eSubpackages", boost::property_tree::ptree());

				for ( std::shared_ptr<ecore::EPackage> eSubpackage : *list_subpackages ) {
					//subpackages.add_child("eSubpackages", traverse(eSubpackage, tree, "eSubpackages"));
					//subpackages.push_back(std::make_pair(".eSubpackages " , traverse(eSubpackage, tree, "eSubpackages")));
					//subpackages.push_back(traverse(eSubpackage, tree, "eSubpackages"));
					//std::string wasd = ctree.get<std::string>(prefix);
					//std::cout << "Element: "<< wasd<< std::endl;
					//ctree.add_child(prefix, traverse(eSubpackage, tree, ".eSubpackages"));
					//ctree.put_child(prefix, traverse(eSubpackage, tree, "eSubpackages"));
					//ctree.add(prefix + ".eSubpackages", "test");// traverse(eSubpackage, tree, "eSubpackages"));
					//ctree.add("." + prefix, "test");// traverse(eSubpackage, tree, "eSubpackages"));
					//ctree.add(prefix + ".eSubpackages" + (std::string)attr_stream.str(), tmp_object->getNsURI());
					//ctree.add(prefix + ".eSubpackages" + ".eSubpackages", "Test");
					//ctree.add(prefix + ".wasd", "");
					traverse(eSubpackage, subpackage, "eSubpackages");

					//ctree.add_child(prefix2, subpackage);
					//ctree.push_back( std::make_pair(prefix, subpackage ) );
					//ctree.add_child( prefix2, subpackage );
					//ctree.add_child(prefix, traverse(eSubpackage, tree, "eSubpackages"));
				}
				//ctree.add_child(prefix.c_str(), subpackages);
				//ctree.add_child()
			}

		}
		break;
		case (ecore::EcorePackage::ECLASSIFIER):
		{
			std::cout << "EClassifier" << std::endl;

		}
		break;
		case (ecore::EcorePackage::ECLASS):
		{
			std::cout << "EClass" << std::endl;

		}
		break;
		case (ecore::EcorePackage::EENUM):
		{
			std::cout << "EEnum" << std::endl;

		}
		break;
		case (ecore::EcorePackage::EDATATYPE):
		{
			std::cout << "EDataType" << std::endl;

		}
		break;
		case ecore::EcorePackage::ESTRUCTURALFEATURE:
		{
			std::cout << "EStructuralFeature" << std::endl;

		}
		break;
		case ecore::EcorePackage::EREFERENCE:
		{
			std::cout << "EReference" << std::endl;

		}
		break;
		case ecore::EcorePackage::EATTRIBUTE:
		{
			std::cout << "EAttribute" << std::endl;

		}
		break;
		case ecore::EcorePackage::EOPERATION:
		{
			std::cout << "EOperation" << std::endl;

		}
		break;
		case ecore::EcorePackage::EPARAMETER:
		{
			std::cout << "EParameter" << std::endl;

		}
		break;
		case ecore::EcorePackage::EANNOTATION:
		{
			std::cout << "EAnnotation" << std::endl;

		}
		break;
		default:
		{
			std::cout << "default case" << std::endl;
		}

	}

	//return ctree;

#if 0
	//std::shared_ptr<Bag<ecore::EStructuralFeature>>>list_attrib = metaClass->getEStructuralFeatures();
	std::shared_ptr<Bag<ecore::EStructuralFeature>>>list_attrib = metaClass->getEAllStructuralFeatures();

	for ( std::shared_ptr<ecore::EStructuralFeature> eStructFeat : *list_attrib ) {
		try {

			boost::any eStructFeat_any = object->eGet(eStructFeat);
			//if(object_any.type() == typeid(std::string))
			{

				auto eStructFeat_eClass = eStructFeat->eClass();
				auto eStructFeat_EType = eStructFeat->getEType();
				auto cls_id = eStructFeat_eClass->getClassifierID();

				std::cout << "Class-ID: " << cls_id << std::endl;
				std::cout << "EStructuralFeature (eClass): " << eStructFeat_eClass->getName() << std::endl;
				std::cout << "EStructuralFeature (EType): " << eStructFeat_EType->getName() << std::endl;
				std::cout << "EStructuralFeature: " << eStructFeat->getName() << std::endl;

				//std::cout << typeid(eStructFeat_EType).name() << std::endl;
				//std::cout << std::to_string( eStructFeat_any.type() == typeid(std::string) ) << std::endl;
				//const std::type_info &ti = eStructFeat_any.type();
				//std::cout << ti.name() << std::endl;

				if(eStructFeat_any.type() == typeid(std::string))
				{
					std::cout << "std::string" << std::endl;
					auto attr = boost::any_cast<std::string>(eStructFeat_any);
					std::cout << "EStructuralFeature: " << attr.c_str() << std::endl;
				}
				/* folgendes funkt nicht
				 if (std::string p = dynamic_cast<std::string>(eStructFeat_any)) {
				 std::cout << "T1<int>" << std::endl;
				 }*/
				else if(eStructFeat_any.type() == typeid(bool))
				{
					std::cout << "bool" << std::endl;
					auto attr = boost::any_cast<bool>(eStructFeat_any);
					std::cout << "EStructuralFeature: " << attr << std::endl;
				}
				else if(eStructFeat_any.type() == typeid(int))
				{
					std::cout << "int" << std::endl;
					auto attr = boost::any_cast<int>(eStructFeat_any);
					std::cout << "EStructuralFeature: " << attr << std::endl;
				}
				else if(eStructFeat_any.type() == typeid(float))
				{
					std::cout << "float" << std::endl;
					auto attr = boost::any_cast<float>(eStructFeat_any);
					std::cout << "EStructuralFeature: " << attr << std::endl;
				}/*
				 else if(dynamic_cast<std::string >(eStructFeat_any) == nullptr)
				 {
				 std::cout << "ERROR" << std::endl;

				 }*/
				else {
					std::cout << "ecore::EObject" << std::endl;
					try
					{
						auto list = boost::any_cast<std::shared_ptr<Bag<ecore::EAttribute>>>>(eStructFeat_any);

						//auto attr = boost::any_cast<std::shared_ptr<ecore::EFactory>>(eStructFeat_any);
					}
					catch(const boost::bad_any_cast & e)
					{
						std::cout << e.what() << std::endl;
						//throw();
					}

				}
				//std::cout << "EStructuralFeature (FeatureID): " << attrib_FID << std::endl;

			}

		}
		catch ( std::exception &e ) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	std::shared_ptr<Bag<ecore::EOperation>>>list_operations = metaClass->getEAllOperations();

	for ( std::shared_ptr<ecore::EOperation> operation : *list_operations ) { // TODO hier wird passiert bereits beim 1. Element ein Absturz des Programms
		//for ( std::shared_ptr<ecore::EOperation> operation : *metaClass->getEOperations() ) { // TODO hier wird nur die API getClassifier() zurueckgegeben
		try {
			if(operation.get() == nullptr) {
				std::cout << "Operation is nullptr" << std::endl;
			}
			if(operation == nullptr) {
				std::cout << "Operation is nullptr" << std::endl;
			}
			std::cout << "Operation: " << operation->getName() << std::endl;
			auto wasd = operation->eClass();
			std::cout << "Operation (eClass): " << wasd->getName() << std::endl;
		}
		catch ( std::exception &e ) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
	/*
	 std::shared_ptr<Bag<ecore::EReference>>>list_ref = metaClass->getEAllReferences();

	 for ( std::shared_ptr<ecore::EReference> reference : *list_ref ) {
	 try {
	 std::cout << "Reference: " << reference->getName() << std::endl;
	 auto wasd = reference->eClass();
	 std::cout << "Reference (eClass): " << wasd->getName() << std::endl;
	 }
	 catch ( std::exception &e ) {
	 std::cout << "Error: " << e.what() << std::endl;
	 }
	 }

	 for ( std::shared_ptr<ecore::EStructuralFeature> reference : *object->) ) {
	 try {
	 std::cout << "Reference: " << reference->getName() << std::endl;
	 auto wasd = reference->eClass();
	 std::cout << "Reference (eClass): " << wasd->getName() << std::endl;
	 }
	 catch ( std::exception &e ) {
	 std::cout << "Error: " << e.what() << std::endl;
	 }
	 }*/

	/*
	 for ( std::shared_ptr<ecore::EReference> reference : *object->) {
	 try {
	 std::cout << "Reference: " << reference->getName() << std::endl;
	 auto wasd = reference->eClass();
	 std::cout << "Reference (eClass): " << wasd->getName() << std::endl;
	 }
	 catch ( std::exception &e ) {
	 std::cout << "Error: " << e.what() << std::endl;
	 }
	 }
	 */
#endif
	//return ctree;
	return tree;

}
#endif

#if 0
void Save::traverse ( std::shared_ptr<ecore::EObject> object, std::shared_ptr<persistence::Handler> handler ) {

	std::shared_ptr<ecore::EClass> metaClass = object->eClass();
	/*
	 std::shared_ptr<ecore::EClass> metaMetaClass = metaClass->eClass();

	 std::cout << "metaClass: " << metaClass->getName() << std::endl;
	 std::cout << "metaMetaPck-Name: " << m_metaMetaPackage->getName() << std::endl;
	 std::cout << "metaMetaPck-NS: " << m_metaMetaPackage->getNsPrefix() << std::endl;
	 std::cout << "metaMetaPck-Uri: " << m_metaMetaPackage->getNsURI() << std::endl;
	 std::cout << "metaMetaClass: " << metaMetaClass->getName() << std::endl;
	 */
	const int cls_id = metaClass->getClassifierID();

	switch ( cls_id ) {
	case (ecore::EcorePackage::EPACKAGE): {

		std::shared_ptr<ecore::EPackage> tmp_object = std::dynamic_pointer_cast<ecore::EPackage>( object );

		std::cout << "EPackage '" << tmp_object->getName() << "'" << std::endl;

		//m_handler->addToMap( tmp_object, tmp_object->getName() );
		//handler->addToMap( tmp_object );

		handler->addAttribute( "name", tmp_object->getName() );
		handler->addAttribute( "nsPrefix", tmp_object->getNsPrefix() );
		handler->addAttribute( "nsURI", tmp_object->getNsURI() );

		// traverse on ESubpackages
		std::shared_ptr<Bag<ecore::EPackage>> list_esubpackages = tmp_object->getESubpackages();

		if ( list_esubpackages->size() ) {
			for ( std::shared_ptr<ecore::EPackage> eSubpackage : *list_esubpackages ) {
				handler->createAndAddElement( "eSubpackages" );
				traverse( eSubpackage, handler );
				handler->release();
			}
		}

		// traverse on EClassifiers
		std::shared_ptr<Bag<ecore::EClassifier>> list_eclassifier = tmp_object->getEClassifiers();

		if ( list_eclassifier->size() ) {
			for ( std::shared_ptr<ecore::EClassifier> eClassifier : *list_eclassifier ) {
				handler->createAndAddElement( "eClassifiers" );
				traverse( eClassifier, handler );
				handler->release();
			}
		}

	}
		break;
	case (ecore::EcorePackage::ECLASSIFIER): {
		//std::shared_ptr<ecore::EClassifier> tmp_object = std::dynamic_pointer_cast<ecore::EClassifier>( object );

		std::cout << "EClassifier" << std::endl;

	}
		break;
	case (ecore::EcorePackage::ECLASS): {
		std::shared_ptr<ecore::EClass> tmp_object = std::dynamic_pointer_cast<ecore::EClass>( object );

		std::cout << "EClass '" << tmp_object->getName() << "'" << std::endl;

		//m_handler->addToMap( tmp_object, tmp_object->getName() );
		//handler->addToMap( tmp_object );

		//std::shared_ptr<ecore::EClass> metaClass = tmp_object->eClass();
		handler->addAttribute( "xsi:type", handler->extractType( tmp_object ) );

		std::shared_ptr<ecore::EStructuralFeature> wasd = metaClass->getEStructuralFeature( ecore::EcorePackage::ENAMEDELEMENT_NAME );
		//if ( tmp_object->eIsSet( wasd ) ) {
		handler->addAttribute( "name", tmp_object->getName() );
		//}
		handler->addAttribute( "abstract", tmp_object->isAbstract() );
		handler->addAttribute( "interface", tmp_object->isInterface() );

		std::shared_ptr<Bag<ecore::EClass> > list_eSuperTypes = tmp_object->getESuperTypes(); // TODO needs reference
		handler->addReference( "eSuperTypes", list_eSuperTypes );

		// traverse on EStructuralFeature
		std::shared_ptr<Bag<ecore::EStructuralFeature>> list_eStructFeature = tmp_object->getEStructuralFeatures();
		if ( list_eStructFeature->size() ) {
			for ( std::shared_ptr<ecore::EStructuralFeature> eStructFeature : *list_eStructFeature ) {
				handler->createAndAddElement( "eStructuralFeatures" );
				traverse( eStructFeature, handler );
				handler->release();
			}
		}
		std::shared_ptr<Bag<ecore::EAttribute>> list_eAttributes = tmp_object->getEAttributes();
		if ( list_eAttributes->size() ) {
			for ( std::shared_ptr<ecore::EAttribute> eAttributes : *list_eAttributes ) {
				//if ( !eAttributes->isTransient() && tmp_object->eIsSet(eAttributes) )
				if ( !eAttributes->isTransient() ) // TODO need impl of eIsSet()
				{
					handler->createAndAddElement( "eStructuralFeatures" );
					traverse( eAttributes, handler );
					handler->release();
				}
			}
		}
		std::shared_ptr<Bag<ecore::EReference>> list_eReferences = tmp_object->getEReferences();
		if ( list_eReferences->size() ) {
			for ( std::shared_ptr<ecore::EReference> eReferences : *list_eReferences ) {
				//if ( !eReferences->isTransient() && tmp_object->eIsSet(eReferences) )
				if ( !eReferences->isTransient() ) // TODO need impl of eIsSet()
				{
					handler->createAndAddElement( "eStructuralFeatures" );
					traverse( eReferences, handler );
					handler->release();
				}
			}
		}

	}
		break;
	case (ecore::EcorePackage::EENUM): {
		std::shared_ptr<ecore::EEnum> tmp_object = std::dynamic_pointer_cast<ecore::EEnum>( object );

		std::cout << "EEnum '" << tmp_object->getName() << "'" << std::endl;

		//m_handler->addToMap( tmp_object, tmp_object->getName() );
		//handler->addToMap( tmp_object );

		handler->addAttribute( "xsi:type", handler->extractType( tmp_object ) );
		handler->addAttribute( "name", tmp_object->getName() );
		//handler->addAttribute_xsi_type(tmp_object->getInstanceTypeName() ); // TODO remove this

		// traverse on EEnumLiteral
		std::shared_ptr<Bag<ecore::EEnumLiteral>> list_eLiteral = tmp_object->getELiterals();
		if ( list_eLiteral->size() ) {
			for ( std::shared_ptr<ecore::EEnumLiteral> eLiteral : *list_eLiteral ) {
				handler->createAndAddElement( "eLiterals" );
				traverse( eLiteral, handler );
				handler->release();
			}
		}

	}
		break;
	case (ecore::EcorePackage::EDATATYPE): {
		std::shared_ptr<ecore::EDataType> tmp_object = std::dynamic_pointer_cast<ecore::EDataType>( object );

		std::cout << "EDataType '" << tmp_object->getName() << "'" << std::endl;

		//m_handler->addToMap( tmp_object, tmp_object->getName() );
		//handler->addToMap( tmp_object );

		handler->addAttribute( "name", tmp_object->getName() );
		handler->addAttribute( "instanceClassName", tmp_object->getInstanceClassName() );
		if ( tmp_object->isSerializable() != true ) {
			handler->addAttribute( "serializable", tmp_object->isSerializable() );
		}
	}
		break;
	case ecore::EcorePackage::ESTRUCTURALFEATURE: {
		std::cout << "EStructuralFeature" << std::endl;

	}
		break;
	case ecore::EcorePackage::EREFERENCE: {
		std::shared_ptr<ecore::EReference> tmp_object = std::dynamic_pointer_cast<ecore::EReference>( object );

		std::cout << "EReference '" << tmp_object->getName() << "'" << std::endl;

		//m_handler->addToMap( tmp_object, tmp_object->getName() );
		//handler->addToMap( tmp_object );

		//std::shared_ptr<ecore::EClass> metaClass = tmp_object->eClass();
		handler->addAttribute( "xsi:type", handler->extractType( tmp_object ) );

		handler->addAttribute( "name", tmp_object->getName() );

		handler->addAttribute( "containment", tmp_object->isContainment() );
		handler->addAttribute( "container", tmp_object->isContainer() );

		if ( tmp_object->isResolveProxies() != true ) // default: isResolveProxies=true
		{
			handler->addAttribute( "resolveProxies", tmp_object->isResolveProxies() );
		}

		if ( tmp_object->isOrdered() != true ) // default: ordered=true
		{
			handler->addAttribute( "ordered", tmp_object->isOrdered() );
		}
		if ( tmp_object->isUnique() != true ) // default: unique=true
		{
			handler->addAttribute( "unique", tmp_object->isUnique() );
		}
		handler->addAttribute( "lowerBound", tmp_object->getLowerBound() );
		if ( tmp_object->getUpperBound() != 1 ) // default: upperBound=1
		{
			handler->addAttribute( "upperBound", tmp_object->getUpperBound() );
		}
		handler->addAttribute( "many", tmp_object->isMany() );
		handler->addAttribute( "required", tmp_object->isRequired() );

		if ( tmp_object->isChangeable() != true ) // default: changeable=true
		{
			handler->addAttribute( "changeable", tmp_object->isChangeable() );
		}
		handler->addAttribute( "volatile", tmp_object->isVolatile() );
		handler->addAttribute( "transient", tmp_object->isTransient() );
		handler->addAttribute( "defaultValueLiteral", tmp_object->getDefaultValueLiteral() );
		handler->addAttribute( "unsettable", tmp_object->isUnsettable() );
		handler->addAttribute( "derived", tmp_object->isDerived() );

		handler->addReference( "eType", tmp_object->getEType() );
		//handler->addAttribute( "eOpposite", tmp_object-> );// TODO needs reference

	}
		break;
	case ecore::EcorePackage::EATTRIBUTE: {
		std::shared_ptr<ecore::EAttribute> tmp_object = std::dynamic_pointer_cast<ecore::EAttribute>( object );

		std::cout << "EAttribute '" << tmp_object->getName() << "'" << std::endl;

		//m_handler->addToMap( tmp_object, tmp_object->getName() );
		//handler->addToMap( tmp_object );

		//std::shared_ptr<ecore::EClass> metaClass = tmp_object->eClass();
		handler->addAttribute( "xsi:type", handler->extractType( tmp_object ) );

		handler->addAttribute( "name", tmp_object->getName() );

		handler->addAttribute( "iD", tmp_object->isID() );

		if ( tmp_object->isOrdered() != true ) // default: ordered=true
		{
			handler->addAttribute( "ordered", tmp_object->isOrdered() );
		}
		if ( tmp_object->isUnique() != true ) // default: unique=true
		{
			handler->addAttribute( "unique", tmp_object->isUnique() );
		}
		handler->addAttribute( "lowerBound", tmp_object->getLowerBound() );
		if ( tmp_object->getUpperBound() != 1 ) // default: upperBound=1
		{
			handler->addAttribute( "upperBound", tmp_object->getUpperBound() );
		}
		handler->addAttribute( "many", tmp_object->isMany() );
		handler->addAttribute( "required", tmp_object->isRequired() );

		if ( tmp_object->isChangeable() != true )  // default: changeable=true
		{
			handler->addAttribute( "changeable", tmp_object->isChangeable() );
		}
		handler->addAttribute( "volatile", tmp_object->isVolatile() );
		handler->addAttribute( "transient", tmp_object->isTransient() );
		handler->addAttribute( "defaultValueLiteral", tmp_object->getDefaultValueLiteral() );
		handler->addAttribute( "unsettable", tmp_object->isUnsettable() );
		handler->addAttribute( "derived", tmp_object->isDerived() );

		handler->addReference( "eType", tmp_object->getEType() );

	}
		break;
	case ecore::EcorePackage::EENUMLITERAL: {
		std::shared_ptr<ecore::EEnumLiteral> tmp_object = std::dynamic_pointer_cast<ecore::EEnumLiteral>( object );

		std::cout << "EEnumLiteral '" << tmp_object->getName() << "'" << std::endl;

		//m_handler->addToMap( tmp_object, tmp_object->getName() );
		//handler->addToMap( tmp_object );

		handler->addAttribute( "name", tmp_object->getName() );
		handler->addAttribute( "value", tmp_object->getValue() );
	}
		break;
	case ecore::EcorePackage::EOPERATION: {
		std::shared_ptr<ecore::EOperation> tmp_object = std::dynamic_pointer_cast<ecore::EOperation>( object );

		std::cout << "EOperation '" << tmp_object->getName() << "'" << std::endl;

		//m_handler->addToMap( tmp_object, tmp_object->getName() );
		//handler->addToMap( tmp_object );

		handler->addAttribute( "name", tmp_object->getName() );

		if ( tmp_object->isOrdered() != true ) // default: ordered=true
		{
			handler->addAttribute( "ordered", tmp_object->isOrdered() );
		}
		if ( tmp_object->isUnique() != true ) // default: unique=true
		{
			handler->addAttribute( "unique", tmp_object->isUnique() );
		}
		handler->addAttribute( "lowerBound", tmp_object->getLowerBound() );

		if ( tmp_object->getUpperBound() != 1 ) // default: upperBound=1
		{
			handler->addAttribute( "upperBound", tmp_object->getUpperBound() );
		}
		handler->addAttribute( "many", tmp_object->isMany() );
		handler->addAttribute( "required", tmp_object->isRequired() );

		handler->addReference( "eType", tmp_object->getEType() );

		// traverse on EParameter
		std::shared_ptr<Bag<ecore::EParameter>> list_eParameter = tmp_object->getEParameters();
		if ( list_eParameter->size() ) {
			for ( std::shared_ptr<ecore::EParameter> eParameter : *list_eParameter ) {
				handler->createAndAddElement( "eParameters" );
				traverse( eParameter, handler );
				handler->release();
			}
		}
	}
		break;
	case ecore::EcorePackage::EPARAMETER: {
		std::shared_ptr<ecore::EParameter> tmp_object = std::dynamic_pointer_cast<ecore::EParameter>( object );

		std::cout << "EParameter '" << tmp_object->getName() << "'" << std::endl;

		//m_handler->addToMap( tmp_object, tmp_object->getName() );
		//handler->addToMap( tmp_object );

		handler->addAttribute( "name", tmp_object->getName() );

		if ( tmp_object->isOrdered() != true ) // default: ordered=true
		{
			handler->addAttribute( "ordered", tmp_object->isOrdered() );
		}
		if ( tmp_object->isUnique() != true ) // default: unique=true
		{
			handler->addAttribute( "unique", tmp_object->isUnique() );
		}
		handler->addAttribute( "lowerBound", tmp_object->getLowerBound() );

		if ( tmp_object->getUpperBound() != 1 ) // default: upperBound=1
		{
			handler->addAttribute( "upperBound", tmp_object->getUpperBound() );
		}
		handler->addAttribute( "many", tmp_object->isMany() );
		handler->addAttribute( "required", tmp_object->isRequired() );

		handler->addReference( "eType", tmp_object->getEType() );

		std::shared_ptr<Bag<ecore::EAnnotation>> list_eAnnotations = tmp_object->getEAnnotations();
		if ( list_eAnnotations->size() ) {
			for ( std::shared_ptr<ecore::EAnnotation> eAnnotations : *list_eAnnotations ) {
				handler->createAndAddElement( "eAnnotations" );
				traverse( eAnnotations, handler );
				handler->release();
			}
		}
	}
		break;

	case ecore::EcorePackage::EANNOTATION: {
		std::shared_ptr<ecore::EAnnotation> tmp_object = std::dynamic_pointer_cast<ecore::EAnnotation>( object );

		std::cout << "EAnnotation" << std::endl;
		handler->addAttribute( "source", tmp_object->getSource() );

		// traverse on EStringToStringMapEntry (details)
		std::shared_ptr<Bag<ecore::EStringToStringMapEntry>> list_eStringToStringMapEntry = tmp_object->getDetails();
		if ( list_eStringToStringMapEntry->size() ) {
			for ( std::shared_ptr<ecore::EStringToStringMapEntry> eStringToStringMapEntry : *list_eStringToStringMapEntry ) {
				handler->createAndAddElement( "details" );
				traverse( eStringToStringMapEntry, handler );
				handler->release();
			}
		}

	}
		break;

	case ecore::EcorePackage::ESTRINGTOSTRINGMAPENTRY: {
		std::shared_ptr<ecore::EStringToStringMapEntry> tmp_object = std::dynamic_pointer_cast<ecore::EStringToStringMapEntry>( object );

		std::cout << "EAnnotation" << std::endl;

		handler->addAttribute( "key", tmp_object->getKey() );
		handler->addAttribute( "value", tmp_object->getValue() );

	}
		break;
	default: {
		std::cout << "default case" << std::endl;
	}

	}
}
#endif
} /* namespace persistence */

