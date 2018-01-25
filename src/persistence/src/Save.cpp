/*
 * Save.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "Save.hpp"

namespace persistence
{
namespace base
{

Save::Save ()
{
}

Save::~Save ()
{
	// TODO Auto-generated destructor stub
}

bool Save::save ( const std::string &filename, std::shared_ptr<ecore::EObject> model, std::shared_ptr<ecore::EPackage> metaMetaPackage )
{
	std::shared_ptr<ecore::EClass> metaClass = model->eClass();

	std::cout << "| DEBUG    | " << "metaClass: " << metaClass->getName() << std::endl;
	std::cout << "| DEBUG    | " << "metaMetaPck-NS: " << metaMetaPackage->getNsPrefix() << std::endl;
	std::cout << "| DEBUG    | " << "metaMetaPck-Uri: " << metaMetaPackage->getNsURI() << std::endl;

	m_handler->createRootNode( metaMetaPackage->getNsPrefix(), metaClass->getName(), metaMetaPackage->getNsURI() );
	m_handler->setRootObject( model );

	std::cout << "| DEBUG    | " << m_handler->extractType( model ) << std::endl;

	model->save( m_handler );
	//traverse( m_model, m_handler );
	m_handler->release();

	// Call write() method in corresponding derived class
	return write( filename );
}

} /* namespace base */
} /* namespace persistence */
