/*
 * Load.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "Load.hpp"

namespace persistence
{

Load::Load ()
{
	m_handler = std::make_shared<persistence::Handler>();
	m_model = nullptr;
}

Load::~Load ()
{
	// TODO Auto-generated destructor stub
}

void Load::setFilename ( const std::string& filename )
{
	m_filename = filename;
}

void Load::setModel ( std::shared_ptr<ecore::EObject> model )
{
	m_model = model;
}

void Load::setMetaMetaPackage ( std::shared_ptr<ecore::EPackage> metaMetaPackage )
{
	m_metaMetaPackage = metaMetaPackage;
}

void Load::setOptions ( std::set<std::string> options )
{
	m_options = options;
}

std::shared_ptr<ecore::EObject> Load::load ( const std::string &filename, std::set<std::string> options )
/*{

 setFilename( filename );
 setModel( model ); // TODO dont need this
 setMetaMetaPackage( metaMetaPackage ); // TODO dont need this
 setOptions( options ); // TODO dont need this

 return load();
 }

 std::shared_ptr<ecore::EObject> Load::load ()*/
{
	std::shared_ptr<ecore::EObject> retvalue = nullptr;

	if ( read( filename, m_handler ) == false )
	{
		std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << " Occurred during reading file." << std::endl;
		retvalue = nullptr;
	}
	else
	{
		std::cout << "| INFO     | " << "Reading file successfully." << std::endl;

		//m_handler->countChildElements( m_handler->getDOMDocument(), true ); // TODO remove this later
		// TODO here is the load function

		//m_handler->setDOMDocument(m_handler->getDOMDocument());

		std::shared_ptr<ecore::EcoreFactory> factory = ecore::EcoreFactory::eInstance();

		m_handler->getNextNodeName(); // TODO need here

		std::shared_ptr<ecore::EPackage> pck_root( factory->createEPackage() );
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
		m_handler->setRootObj( pck_root );
		pck_root->load( m_handler ); // TODO remove this comment

		m_model = std::dynamic_pointer_cast<ecore::EObject>( pck_root );

		//

		retvalue = m_model;
	}

	return retvalue;
}

} /* namespace persistence */
