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
}

Save::~Save () {
	// TODO Auto-generated destructor stub
}
bool Save::save ( const std::string &filename, std::shared_ptr<ecore::EObject> model, std::set<std::string> options ) {
	m_model = model;
	m_options = options;

	m_tree = traverse( model, m_tree );

	return write( filename );
}

boost::property_tree::ptree Save::traverse ( std::shared_ptr<ecore::EObject> object, boost::property_tree::ptree tree ) {

	std::shared_ptr<ecore::EClass> metaClass = object->eClass();
	std::shared_ptr<ecore::EClass> metaMetaClass = metaClass->eClass();

	std::cout << metaClass->getName() << std::endl;
	std::cout << metaMetaClass->getName() << std::endl;

	std::shared_ptr<std::vector<std::shared_ptr<ecore::EAttribute>>>list_attrib = metaClass->getEAttributes();

	for ( std::shared_ptr<ecore::EAttribute> attrib : *metaClass->getEAttributes() ) {
		try {
			std::cout << "Attribute: " << attrib->getName() << std::endl;
			auto wasd = attrib->eClass();
			std::cout << "Attribute (eClass): " << wasd->getName() << std::endl;
		}
		catch ( std::exception &e ) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	for ( std::shared_ptr<ecore::EOperation> operation : *metaClass->getEOperations() ) { // TODO hier wird nur die API getClassifier() zurueckgegeben
		try {
			std::cout << "Operation: " << operation->getName() << std::endl;
			auto wasd = operation->eClass();
			std::cout << "Operation (eClass): " << wasd->getName() << std::endl;
		}
		catch ( std::exception &e ) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	for ( std::shared_ptr<ecore::EReference> reference : *metaClass->getEAllReferences() ) {
		try {
			std::cout << "Reference: " << reference->getName() << std::endl;
			auto wasd = reference->eClass();
			std::cout << "Reference (eClass): " << wasd->getName() << std::endl;
		}
		catch ( std::exception &e ) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

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


	return tree;
}

} /* namespace persistence */

