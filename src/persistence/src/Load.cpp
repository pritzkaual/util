/*
 * Load.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "Load.hpp"

#include "PluginFramework.hpp"
#include "MDE4CPPPlugin.hpp"
#include "EcoreModelPlugin.hpp"

namespace persistence
{

Load::Load () : m_handler(new persistence::Handler())
{

}

Load::~Load ()
{
	// TODO Auto-generated destructor stub
}



std::shared_ptr<ecore::EObject> Load::load (const std::string &filename, std::set<std::string> options)
{
	std::shared_ptr<ecore::EObject> retvalue = nullptr;
	std::string prefix;

	std::cout << "| INFO     | " << "Reading file '" << filename << "'"<< std::endl;

	if ( read( filename, m_handler ) == false )
	{
		std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << " Occurred during reading file." << std::endl;
		retvalue = nullptr;
	}
	else
	{
		std::cout << "| INFO     | " << "Reading file successfully." << std::endl;

		// TODO need comment here
		m_handler->getNextNodeName();

		// Use PluginFramework to create factory and package by given prefix (eg. ecore, uml,...)
		prefix = m_handler->getPrefix();

		std::shared_ptr<PluginFramework> pluginFramework = PluginFramework::eInstance();
		std::shared_ptr<MDE4CPPPlugin> plugin = pluginFramework->findPluginByName(prefix);

		if(plugin && (prefix.compare("ecore") == 0))
		{
			std::shared_ptr<EcoreModelPlugin> ecorePlugin = std::dynamic_pointer_cast<EcoreModelPlugin>(plugin);
			std::shared_ptr<ecore::EPackage> package = ecorePlugin->getPackage();
			//std::shared_ptr<ecore::EFactory> factory = ecorePlugin->getFactory(); // TODO not supported yet
			std::shared_ptr<ecore::EcoreFactory> factory =  std::dynamic_pointer_cast<ecore::EcoreFactory>(ecorePlugin->getFactory())->eInstance();

			std::shared_ptr<Bag<ecore::EClassifier>> eClassifiers = package->getEClassifiers();
			for(std::shared_ptr<ecore::EClassifier> eClassifier : *eClassifiers)
			{
				// TODO filter EDataType
				std::shared_ptr<ecore::EClass> _metaClass = eClassifier->eClass();
				if (_metaClass->getName().compare("EDataType") == 0)
				{
					m_handler->addToMap(eClassifier);
				}
			}

			// Create root object of model
			//std::shared_ptr<ecore::EPackage> pck_root = std::dynamic_pointer_cast<ecore::EPackage>(factory->create(std::dynamic_pointer_cast<ecore::EClass>(package->getEClassifier("EPackage"))) ); // TODO Not supported yet
			std::shared_ptr<ecore::EPackage> pck_root = factory->createEPackage();

			m_handler->setCurrentObject( pck_root );

			// Start loading process by calling load() on root object
			pck_root->load( m_handler );

			// Resolve unresolved references that are stored during loading
			m_handler->resolveReferences();

			// cast root object to EObject
			retvalue = std::dynamic_pointer_cast<ecore::EObject>( pck_root );
		}
		else
		{
			std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << " Given Plugin is not supported or not found by PluginFramework '" << prefix << "'" << std::endl;
		}
	}

	return retvalue;
}

} /* namespace persistence */