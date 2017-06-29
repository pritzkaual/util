/*
 * Save.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "Save.hpp"

namespace persistence {

Save::Save () {
	// TODO Auto-generated constructor stub
	m_handler = std::make_shared<persistence::Handler>();
	//m_package = ecore::EcorePackage::eInstance();
	//m_tree = nullptr;
}

Save::~Save () {
	// TODO Auto-generated destructor stub
}
bool Save::save ( const std::string &filename, std::shared_ptr<ecore::EObject> model, std::set<std::string> options ) {
	m_model = model;
	m_options = options;

	boost::property_tree::ptree wasd = boost::property_tree::ptree();
	//m_tree = traverse( model, m_tree , "ecore:EPackage");
	traverse( model, m_tree , "ecore:EPackage");

	return write( filename );
}

boost::property_tree::ptree Save::traverse ( std::shared_ptr<ecore::EObject> object, boost::property_tree::ptree &tree, const std::string prefix )  {

	std::shared_ptr<ecore::EClass> metaClass = object->eClass();
	std::shared_ptr<ecore::EClass> metaMetaClass = metaClass->eClass();

	//std::cout << metaClass->getName() << std::endl;
	//std::cout << metaMetaClass->getName() << std::endl;

	//boost::property_tree::ptree ctree;

	const int cls_id = metaClass->getClassifierID();

	switch(cls_id){
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
		attr_stream.str(""); // Reset attr_stream

		//attr_stream << prefix << ".<xmlattr>." << "nsPrefix";
		attr_stream << ".<xmlattr>." << "nsPrefix";
		//std::cout << attr_stream.str() << std::endl;
		ctree.add((std::string)attr_stream.str(), tmp_object->getNsPrefix());
		//ctree.add((std::string)attr_stream.str(), tmp_object->getNsPrefix());
		attr_stream.str(""); // Reset attr_stream

		//attr_stream << prefix << ".<xmlattr>." << "nsURI";
		attr_stream << ".<xmlattr>." << "nsURI";
		//std::cout << attr_stream.str() << std::endl;
		ctree.add((std::string)attr_stream.str(), tmp_object->getNsURI());
		//ctree.add((std::string)attr_stream.str(), tmp_object->getNsURI());
		attr_stream.str(""); // Reset attr_stream

		//std::cout << "prefix_stream: "<< prefix_stream.str()<< std::endl;
		ctree.add("wasd", "wad");
		ctree.add("wasd", "wad");
		/*
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EStructuralFeature>>>list_attrib = metaClass->getEAllStructuralFeatures();

		for ( std::shared_ptr<ecore::EStructuralFeature> eStructFeat : *list_attrib ) {

		}
		 */
/*
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EAnnotation>>>list_annotations = tmp_object->getEAnnotations();
		if(list_annotations->size()){
			boost::property_tree::ptree annotations;

			for ( std::shared_ptr<ecore::EAnnotation> eAnnotation : *list_annotations ) {
				annotations.push_back(std::make_pair("" , traverse(eAnnotation, tree, prefix + "eAnnotations")));
			}
			ctree.add_child(prefix + ".eAnnotations", annotations);
		}
*/
		/*
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EClassifier>>>list_classifiers = tmp_object->getEClassifiers();
		for ( std::shared_ptr<ecore::EClassifier> eClassifier : *list_classifiers ) {
			traverse(eClassifier, ctree, prefix + ".eClassifiers");
		}
		 */

		return tree;

		std::shared_ptr<std::vector<std::shared_ptr<ecore::EPackage>>>list_subpackages = tmp_object->getESubpackages();
		if(list_subpackages->size()){
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
	//std::shared_ptr<std::vector<std::shared_ptr<ecore::EStructuralFeature>>>list_attrib = metaClass->getEStructuralFeatures();
	std::shared_ptr<std::vector<std::shared_ptr<ecore::EStructuralFeature>>>list_attrib = metaClass->getEAllStructuralFeatures();

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
						auto list = boost::any_cast<std::shared_ptr<std::vector<std::shared_ptr<ecore::EAttribute>>>>(eStructFeat_any);

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


	std::shared_ptr<std::vector<std::shared_ptr<ecore::EOperation>>>list_operations = metaClass->getEAllOperations();

	for ( std::shared_ptr<ecore::EOperation> operation : *list_operations ) { // TODO hier wird passiert bereits beim 1. Element ein Absturz des Programms
		//for ( std::shared_ptr<ecore::EOperation> operation : *metaClass->getEOperations() ) { // TODO hier wird nur die API getClassifier() zurueckgegeben
		try {
			if(operation.get() == nullptr){
				std::cout << "Operation is nullptr" << std::endl;
			}
			if(operation == nullptr){
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
	std::shared_ptr<std::vector<std::shared_ptr<ecore::EReference>>>list_ref = metaClass->getEAllReferences();

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

} /* namespace persistence */

