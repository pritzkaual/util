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
	m_package = ecore::EcorePackage::eInstance();
	//m_tree = nullptr;
}

Save::~Save () {
	// TODO Auto-generated destructor stub
}
bool Save::save ( const std::string &filename, std::shared_ptr<ecore::EObject> model, std::set<std::string> options ) {
	m_model = model;
	m_options = options;

	traverse( model, m_tree , "");

	return write( filename );
}

void Save::traverse ( std::shared_ptr<ecore::EObject> object, std::shared_ptr<boost::property_tree::ptree> tree, std::string prefix )  {

	std::shared_ptr<ecore::EClass> metaClass = object->eClass();
	std::shared_ptr<ecore::EClass> metaMetaClass = metaClass->eClass();

	//std::cout << metaClass->getName() << std::endl;
	//std::cout << metaMetaClass->getName() << std::endl;
	if (tree == nullptr){
		//std::shared_ptr<boost::property_tree::ptree> tree;
	}
	//boost::property_tree::ptree ctree;

	const int cls_id = metaClass->getClassifierID();

	switch(cls_id){
	case (ecore::EcorePackage::EPACKAGE):
	{
		std::cout << "EPackage" << std::endl;

		std::shared_ptr<ecore::EPackage> tmp_object = std::dynamic_pointer_cast<ecore::EPackage>(object);

		std::string tag = prefix;

		auto name = tmp_object->getName();

		auto superpackage = tmp_object->getESuperPackage();

		if(superpackage == nullptr){
			std::cout << "no Superpackage" << std::endl;
			tag += ".ecore:EPackage"; // TODO Correct version: tag = "ecore:EPackage";
		}else{
			std::cout << superpackage->getName() << std::endl;
			tag += ".eSubpackages";

		}

		tree->add(tag, ""); // add tag


		// Add Attributes
		std::stringstream attr_stream;

		attr_stream << tag << ".<xmlattr>." << "name";
		//std::cout << attr_stream.str() << std::endl;
		tree->add(attr_stream.str(), tmp_object->getName());
		attr_stream.str("");

		attr_stream << tag << ".<xmlattr>." << "nsPrefix";
		//std::cout << attr_stream.str() << std::endl;
		tree->add(attr_stream.str(), tmp_object->getNsPrefix());
		attr_stream.str("");

		attr_stream << tag << ".<xmlattr>." << "nsURI";
		//std::cout << attr_stream.str() << std::endl;
		tree->add(attr_stream.str(), tmp_object->getNsURI());
		attr_stream.str("");
		/*
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EStructuralFeature>>>list_attrib = metaClass->getEAllStructuralFeatures();

		for ( std::shared_ptr<ecore::EStructuralFeature> eStructFeat : *list_attrib ) {

		}
		*/
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EAnnotation>>>list_annotations = tmp_object->getEAnnotations();
		for ( std::shared_ptr<ecore::EAnnotation> eAnnotation : *list_annotations ) {
			traverse(eAnnotation, tree, tag);
		}
/*
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EClassifier>>>list_classifiers = tmp_object->getEClassifiers();
		for ( std::shared_ptr<ecore::EClassifier> eClassifier : *list_classifiers ) {
			traverse(eClassifier, ctree, tag);
		}
*/
		std::shared_ptr<std::vector<std::shared_ptr<ecore::EPackage>>>list_subpackages = tmp_object->getESubpackages();
		for ( std::shared_ptr<ecore::EPackage> eSubpackage : *list_subpackages ) {
			traverse(eSubpackage, tree, tag);
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
	//return tree;
}

} /* namespace persistence */

