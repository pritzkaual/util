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
			std::shared_ptr<ecore::EcoreFactory> factory = std::dynamic_pointer_cast<ecore::EcoreFactory>(ecorePlugin->getFactory())->eInstance();
			std::shared_ptr<ecore::EcorePackage> package = std::dynamic_pointer_cast<ecore::EcorePackage>(ecorePlugin->getPackage())->eInstance();
#if 0
			std::shared_ptr<ecore::EPackage> package = ecorePlugin->getPackage();

			std::shared_ptr<Bag<ecore::EClassifier>> eClassifiers = package->getEClassifiers();

			for(std::shared_ptr<ecore::EClassifier> eClassifier : *eClassifiers)
			{
				std::cout << eClassifier->getName() << std::endl;
			}
#endif
			// Add Primitive DataTypes to Handler's internal map
			m_handler->addToMap(package->getEBigDecimal());
			m_handler->addToMap(package->getEBigInteger());
			m_handler->addToMap(package->getEBoolean());
			m_handler->addToMap(package->getEBooleanObject());
			m_handler->addToMap(package->getEByte());
			m_handler->addToMap(package->getEByteArray());
			m_handler->addToMap(package->getEByteObject());
			m_handler->addToMap(package->getEChar());
			m_handler->addToMap(package->getECharacterObject());
			m_handler->addToMap(package->getEDate());
			m_handler->addToMap(package->getEDiagnosticChain());
			m_handler->addToMap(package->getEDouble());
			m_handler->addToMap(package->getEDoubleObject());
			m_handler->addToMap(package->getEEList());
			m_handler->addToMap(package->getEEnumerator());
			m_handler->addToMap(package->getEFeatureMap());
			m_handler->addToMap(package->getEFeatureMapEntry());
			m_handler->addToMap(package->getEFloat());
			m_handler->addToMap(package->getEFloatObject());
			m_handler->addToMap(package->getEInt());
			m_handler->addToMap(package->getEIntegerObject());
			m_handler->addToMap(package->getEInvocationTargetException());
			m_handler->addToMap(package->getEJavaClass());
			m_handler->addToMap(package->getEJavaObject());
			m_handler->addToMap(package->getELong());
			m_handler->addToMap(package->getELongObject());
			m_handler->addToMap(package->getEMap());
			m_handler->addToMap(package->getEResource());
			m_handler->addToMap(package->getEResourceSet());
			m_handler->addToMap(package->getEShort());
			m_handler->addToMap(package->getEShortObject());
			m_handler->addToMap(package->getEString());
			m_handler->addToMap(package->getETreeIterator());

			// Create root object of model
			std::shared_ptr<ecore::EPackage> pck_root( factory->createEPackage() );

	#if 0
			std::shared_ptr<ecore::EPackage> pck_root1( factory->createEPackage() );
			pck_root1->setName("MyPck");

			std::shared_ptr<ecore::EObject> cls( factory->create( "EClass" ) );

			std::shared_ptr<ecore::EClassifier> cls1;
			cls1 = std::dynamic_pointer_cast<ecore::EClassifier>( factory->create( "EClass" ) );

			std::shared_ptr<ecore::EClass> cls4( factory->createEClass() );
			std::shared_ptr<ecore::EClassifier> cls2( factory->createEClass() );
			std::shared_ptr<ecore::EClass> cls3 = std::dynamic_pointer_cast<ecore::EClass>( cls2 );
			cls3->setName("Hans");
			std::shared_ptr<ecore::EClass> cls4_metacls = cls4->eClass();
			cls4->setName("Peter");

			//std::shared_ptr<Bag<ecore::EStructuralFeature>> esfs = cls4_metacls->getEAllStructuralFeatures();

			std::shared_ptr<ecore::EStructuralFeature> esf_eSuperTypes = cls4_metacls->getEStructuralFeature( "eSuperTypes" );
			std::shared_ptr<ecore::EStructuralFeature> esf_ePackage = cls4_metacls->getEStructuralFeature( "ePackage" );
			std::shared_ptr<ecore::EStructuralFeature> esf2;

			/*std::string findstr = "eSuperTypes";
			 for(std::shared_ptr<ecore::EStructuralFeature> f: *esfs){
			 if(f->getName()==findstr)
			 {
			 std::cout << "found" << std::endl;
			 esf2 = f;
			 }

			 }
			 if ( esf == esf2){
			 std::cout << "is equal" << std::endl;
			 }*/
			boost::any _any = cls4->eGet( esf_eSuperTypes ); // TODO folgender code wird in resolveReference used
			std::shared_ptr<Bag<ecore::EObject>> _collection = boost::any_cast<std::shared_ptr<Bag<ecore::EObject>> >( _any );
			_collection->push_back( cls3 );

			std::shared_ptr<Bag<ecore::EClass>> cls4_supertypes = cls4->getESuperTypes();

			for ( std::shared_ptr<ecore::EClass> f : *cls4_supertypes )
			{
				std::cout << f->getName() << std::endl;
			}

			_any = cls4->eGet(esf_ePackage);

			std::shared_ptr<ecore::EObject> _current = boost::any_cast<std::shared_ptr<ecore::EObject> >( _any );

			_current = pck_root1;

			std::shared_ptr<ecore::EPackage> _current_pck = std::dynamic_pointer_cast<ecore::EPackage>(_current);
			std::cout << _current_pck->getName() << std::endl;

			//std::string _t;

	//		const std::type_info &ti = _any.type();
	//		std::cout << ti.name() << std::endl;
	//
	//		if (_any.type() == typeid(const std::string))
	//			_t = boost::any_cast<const std::string>(_any);
	//		else if (_any.type() == typeid(std::string))
	//			_t = boost::any_cast<std::string>(_any);

			//std::cout << _t << std::endl;




			//pck_cls1->load( m_handler ); // TODO remove this comment
			/*std::string _type = "ecore:EClass";

			 size_t const double_dot = _type.find(L':', 0);
			 std::string _type_ns = _type.substr(0, double_dot);
			 std::string _type_name = _type.substr(double_dot + 1);


			 std::string _type2 = "EClass";

			 size_t const double_dot2 = _type2.find(L':', 0);
			 std::string _type_ns2 = _type2.substr(0, double_dot2);
			 std::string _type_name2 = _type2.substr(double_dot2 + 1);
			 */

			/*
			 try{


			 }
			 catch (std::exception & e)
			 {
			 std::cout << e.what() << '\n';
			 }*/
	#endif

			m_handler->setRootObj( pck_root );

			// Start loading process by calling load() on root object
			pck_root->load( m_handler ); // TODO remove this comment

			// Resolve unresolved references
			m_handler->resolveReferences();

			// cast root object to EObject
			retvalue = std::dynamic_pointer_cast<ecore::EObject>( pck_root );
		}
		else
		{
			std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << " Given Plugin is not found by PluginFramework '" << prefix << "'" << std::endl;
		}
	}

	return retvalue;
}

} /* namespace persistence */
