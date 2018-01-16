/*
 * Handler.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "Handler.hpp"


#include <sstream> // used for get_Hash()

namespace persistence
{

Handler::Handler ()
{
	m_doc = nullptr;
	m_root_obj = nullptr;
	m_current_elem = nullptr;
	m_metaMetaPackage = nullptr;
}

Handler::~Handler ()
{

}

void Handler::deleteHandler ()
{
	if ( m_doc )
	{
		m_doc->release();
	}
}


/*void Handler::handle ( std::shared_ptr<ecore::EObject> element, std::set<std::string> options ) {
 std::cout << "| ERROR    | " << " Called " << __PRETTY_FUNCTION__ << " while is not implemented yet." << std::endl;
 }

 std::map<std::string, std::shared_ptr<ecore::EObject> > Handler::get_IdToObject_Map () {
 return m_Id_to_Object;
 }

 std::map<std::shared_ptr<ecore::EObject>, std::string> Handler::get_ObjectToId_Map () {
 return m_Object_to_Id;
 }

 std::string Handler::get_Id ( std::shared_ptr<ecore::EObject> object ) {

 std::string id;

 if ( m_Object_to_Id.find( object ) != m_Object_to_Id.end() ) {
 // found
 id = m_Object_to_Id.at( object );
 }

 return id;
 }
 */

std::shared_ptr<ecore::EObject> Handler::get_Object ( std::string id ) // TODO rename to getObject_by_ref(std::string ref)
{
	std::shared_ptr<ecore::EObject> tmp;

	if ( m_Id_to_Object.find( id ) != m_Id_to_Object.end() )
	{
		// found
		tmp = m_Id_to_Object.at( id );
		//return std::dynamic_pointer_cast<ecore::EObject>( tmp );
		return tmp;
	}
	else
	{
		std::cout << "| WARNING  | " << "Given Reference-Name: '" << id << "' is not in stored map." << std::endl;
		return nullptr;
	}
}

/*
 void Handler::addToMap ( std::shared_ptr<ecore::EObject> object ) {

 std::shared_ptr<ecore::ENamedElement> tmp_object = std::dynamic_pointer_cast<ecore::ENamedElement>( object );

 addToMap( object, tmp_object->getName() );
 }
 */
void Handler::addToMap ( std::shared_ptr<ecore::EObject> object )
{
	std::string ref = extractReference( object );

	//std::cout << "| DEBUG    | " << "Add Object-RefName to Map: " << ref << std::endl;

	if ( m_Id_to_Object.find( ref ) == m_Id_to_Object.end() )
	{
		// ref not found in map, so insert
		m_Id_to_Object.insert( std::pair<std::string, std::shared_ptr<ecore::EObject>>( ref, object ) );
		//m_Object_to_Id.insert( std::pair<std::shared_ptr<ecore::EObject>, std::string>( object, ref ) );
	}
}
/**/

DOMDocument *Handler::getDOMDocument ()
{
	return m_doc;
}

void Handler::setDOMDocument ( DOMDocument * doc )
{
	assert(doc);
	m_doc = doc;
	m_root_obj = nullptr;
	m_current_elem = m_doc->getDocumentElement(); // get root element

	m_rootPrefix = "ecore"; // TODO get prefix from document

	if ( m_current_elem->getNodeType() == DOMNode::ELEMENT_NODE )
	{
		m_element_list.push_back( m_current_elem );
	}
	else
	{
		std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << " Current DOMElement (root) is not a DOMNode::ELEMENT_NODE." << std::endl;
	}
}

std::string Handler::getPrefix ()
{
	return m_rootPrefix;
}

void Handler::setRootObj ( std::shared_ptr<ecore::EObject> object )
{
	m_root_obj = object;
	setCurrentObj(object);
}

void Handler::setCurrentObj ( std::shared_ptr<ecore::EObject> object )
{
	m_current_obj_list.push_back(object);
}

std::shared_ptr<ecore::EObject> Handler::getCurrentObj ()
{
	std::shared_ptr<ecore::EObject> tmp_obj = m_current_obj_list.back();
	assert(tmp_obj);

	return tmp_obj;
}

bool Handler::createRootNode ( const std::string& name, const std::string& ns_uri )
{
	return this->createRootNode( name, ns_uri, nullptr );
}

bool Handler::createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri )
{
	return this->createRootNode( prefix, name, ns_uri, nullptr );
}

bool Handler::createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype )
{
	m_rootPrefix = prefix;
	return this->createRootNode( prefix + ":" + name, ns_uri, nullptr );
}

bool Handler::createRootNode ( const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype )
{
	DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation( X( "Core" ) );

	if ( impl != NULL )
	{
		try
		{
			m_doc = impl->createDocument( (ns_uri.empty()) ? 0 : X( ns_uri ), // root element namespace URI.
			X( name ),         					// root element name
			doctype ); 	                		// document type object (DTD).

			m_current_elem = m_doc->getDocumentElement(); // get root element
		}
		catch ( const OutOfMemoryException& )
		{
			std::cerr << "| ERROR    | " << __PRETTY_FUNCTION__ << " OutOfMemoryException" << std::endl;
			//errorCode = 5;
			return false;
		}
		catch ( const DOMException& e )
		{
			std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << " DOMException code is:  " << e.code << std::endl << StrX( e.getMessage() ) << std::endl;
			//errorCode = 2;
			return false;
		}
		catch ( ... )
		{
			std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << " An error occurred creating the document" << std::endl;
			//errorCode = 3;
			return false;
		}
	}  // (impl != NULL)
	else
	{
		std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << " Requested implementation is not supported" << std::endl;
		//errorCode = 4;
		return false;
	}

	return true;
}

bool Handler::createAndAddElement ( const std::string& name )
{
	if ( m_doc == nullptr )
	{
		std::cout << "| ERROR    | " << " Called " << __PRETTY_FUNCTION__ << " while their is no root-Element created before." << std::endl;
		return false;
	}
	else
	{
		addChild( m_current_elem, m_doc->createElement( X( name ) ) );

		return true;
	}
}

void Handler::addChild ( DOMElement* parent_elem, DOMElement* child_elem )
{
	// Add child to parent Element, and set child as current Element.
	m_current_elem = (DOMElement *) parent_elem->appendChild( child_elem );
}

void Handler::addAttribute ( const std::string &name, bool value )
{
	addAttribute( name, (value ? (std::string) "true" : (std::string) "false") );
}

void Handler::addAttribute ( const std::string& name, const std::string& value )
{
	try
	{
		m_current_elem->setAttribute( X( name ), X( value ) );
	}
	catch ( const DOMException& e )
	{
		std::cout << "| ERROR    | " << "DOMException code is:  " << e.code << std::endl << StrX( e.getMessage() ) << std::endl;
	}
	catch ( std::exception& e )
	{
		std::cout << "| ERROR    | " << "Exception code is:  " << e.what() << std::endl;
	}
}

void Handler::addReference ( const std::string &name, std::shared_ptr<ecore::EObject> object )
{
	addAttribute( name, extractReference( object ) );
}

void addReference ( const std::string &name, std::shared_ptr<Bag<ecore::EObject> > objects )
{
	// TODO need implementation
	std::cout << "| ERROR    | " << " Called " << __PRETTY_FUNCTION__ << " while is not implemented yet." << std::endl;
}

/*
 * This API is adapted to API in Project emf4cpp.
 *
 * LINK to source: https://github.com/catedrasaes-umu/emf4cpp/tree/master/emf4cpp/ecorecpp/serializer/serializer-xerces.cpp
 * ::ecorecpp::mapping::type_traits::string_t serializer::get_type(EObject_ptr obj) const
 *
 */
std::string Handler::extractType ( std::shared_ptr<ecore::EObject> obj ) const
{
	std::stringstream ss;
	std::shared_ptr<ecore::EClass> metaClass = obj->eClass();

	if (!m_rootPrefix.empty())
	{
		ss << m_rootPrefix << ":" << metaClass->getName();
	}
	else
	{
		ss << metaClass->getName();
	}

	return ss.str();
}

/*
 * This API is adapted to API in Project emf4cpp.
 *
 * LINK to source: https://github.com/catedrasaes-umu/emf4cpp/tree/master/emf4cpp/ecorecpp/serializer/serializer-xerces.cpp
 * ::ecorecpp::mapping::type_traits::string_t serializer::get_reference(EObject_ptr from, EObject_ptr to) const
 *
 */
std::string Handler::extractReference ( std::shared_ptr<ecore::EObject> to ) const
{
	std::stringstream value;
	std::list<std::shared_ptr<ecore::EObject> > to_antecessors;
	std::shared_ptr<ecore::EObject> antecessor = to; //pre-init antecessor

	while ( antecessor )
	{
		to_antecessors.push_back( antecessor );
		antecessor = to_antecessors.back()->eContainer();
	}

	std::shared_ptr<ecore::EPackage> pkg = std::dynamic_pointer_cast<ecore::EPackage>( to_antecessors.back() );

	if ( pkg )
	{
		// This case is used for ecore-models
		//if ( (m_root_obj != pkg) || (m_root_obj == nullptr) )
		if ( m_root_obj != pkg )
		{
			value << extractType( to ) << " " << pkg->getNsURI();
		}

		value << "#/";
		//to_antecessors.pop_back();

		while ( to_antecessors.size() > 0 )
		{
			std::shared_ptr<ecore::ENamedElement> to_antecessors_back = std::dynamic_pointer_cast<ecore::ENamedElement>( to_antecessors.back() );
			if ( to_antecessors_back != nullptr )
			{
				value << "/" << to_antecessors_back->getName();
			}
			to_antecessors.pop_back();
		}
	}
	//else if ( (to_antecessors.back() == m_root_obj) || (m_root_obj == nullptr) )
	else if ( to_antecessors.back() == m_root_obj )
	{
		// This case is used for Non-Ecore-Models
		// TODO test this case

		std::cout << "| ERROR    | " << " Called " << __PRETTY_FUNCTION__ << " while else-if-case (Non-Ecore-Models) is not tested yet." << std::endl;

		value << "/";
		std::shared_ptr<ecore::EObject> prev = to_antecessors.back();
		to_antecessors.pop_back();

		while ( to_antecessors.size() )
		{
			std::shared_ptr<ecore::EStructuralFeature> esf = to_antecessors.back()->eContainingFeature();

			if ( esf->getUpperBound() == 1 )
				value << "/" << esf->getName();

			else
			{
				boost::any _any = prev->eGet( esf );

				std::shared_ptr<Bag<ecore::EObject>> ef = boost::any_cast<std::shared_ptr<Bag<ecore::EObject>>>( _any );

				// calculate the index of back at father's collection
				size_t index_of = 0;
				for ( ; index_of < ef->size() && (*ef)[index_of] != to_antecessors.back(); index_of++ );

				value << "/@" << esf->getName() << "." << index_of;
			}

			prev = to_antecessors.back();
			to_antecessors.pop_back();
		}
	}
	else
	{
		// This case is for EDataType-Classes like EString, ...
		std::shared_ptr<ecore::EDataType> dataType = std::dynamic_pointer_cast<ecore::EDataType>( to );

		if ( dataType )
		{
			std::weak_ptr<ecore::EPackage> dPck = dataType->getEPackage();

			//if ( (m_root_obj != dPck) || (m_root_obj == nullptr) )
			if(auto ePck = dPck.lock())
			{
				if ( m_root_obj != ePck) // TODO use here other way to find equality of m_root_obj and current EPackage-Obj
				{
					value << extractType( to ) << " " << ePck->getNsURI();
				}
			}

			value << "#/";
			value << "/" << dataType->getName();
		}
		else
		{
			std::cout << "| ERROR    | " << "Called " << __PRETTY_FUNCTION__ << " while else-case (EDataType-Classes) is not implemented yet." << std::endl;
		}
	}

	//std::cout << "| DEBUG    | " << value.str() << std::endl;
	return value.str();
}

void Handler::release ()
{
	if ( m_current_elem == nullptr )
	{
		std::cout << "| ERROR    | " << "You can't call " << __PRETTY_FUNCTION__ << " while current DOMElement m_current_elem is nullptr." << std::endl;
	}
	else
	{
		// set m_current_elem's parent node as new m_current_elem (decrease depth)
		m_current_elem = (DOMElement*) m_current_elem->getParentNode();
	}
}

void Handler::releaseObj ()
{
	std::shared_ptr<ecore::EObject> tmp_obj = m_current_obj_list.back();

	if ( tmp_obj == nullptr )
	{
		std::cout << "| ERROR    | " << "You can't call " << __PRETTY_FUNCTION__ << " while current Object is nullptr." << std::endl;
	}
	else
	{
		// set current (container) object as new current object (decrease depth)
		m_current_obj_list.pop_back();
	}
}
/*
 std::string Handler::create_Hash ( std::shared_ptr<ecore::EObject> object )
 {

 std::ostringstream address;
 address << object.get();
 std::string name = address.str();

 return name;
 }
 */

int Handler::getNumOfChildren ()
{
	DOMNode *child;
	unsigned int count = 0;

	for ( child = m_current_elem->getLastChild(); child != 0; child = child->getPreviousSibling() )
	{
		if ( child->getNodeType() == DOMNode::ELEMENT_NODE )
		{
			++count;
		}
	}
	if ( count != m_current_elem->getChildElementCount() )
	{
		std::cout << "| ERROR    | " << " In " << __PRETTY_FUNCTION__ << " different Number of Children." << std::endl;
	}
	return count;
}

std::string Handler::getNextNodeName ()
{
	std::string nodeName;
	DOMNode *child;

	if ( m_element_list.size() == 0 )
	{
		nodeName = "";
	}
	else
	{
		m_current_elem = (DOMElement*) m_element_list.back();

		nodeName = W( m_current_elem->getNodeName() );

		m_element_list.pop_back();

		for ( child = m_current_elem->getLastChild(); child != 0; child = child->getPreviousSibling() )
		{
			if ( child->getNodeType() == DOMNode::ELEMENT_NODE )
			{
				m_element_list.push_back( child );
			}
		}

#if true
		std::cout << "| DEBUG    | " << "Node-List: " << std::endl << "|          | ";
		for ( auto current_elem : m_element_list )
		{
			std::cout << "<" << W( current_elem->getNodeName() ) << "> ";
		}
		std::cout << std::endl;
#endif
	}
	//std::cout << "| DEBUG    | " << "NodeName: " << nodeName << std::endl;

	return nodeName;
}

std::map<std::string, std::string> Handler::getAttributeList ()
{
	std::map<std::string, std::string> attributeList;

	DOMAttr *pAttributeNode;
	std::string aName;
	std::string aValue;

	DOMNamedNodeMap *pAttributes = m_current_elem->getAttributes();
	const XMLSize_t nSize = pAttributes->getLength();

	//std::cout << "| DEBUG    | " << "\t" << "Attributes:" << std::endl;
	//std::cout << "|            " << "\t" << "-----------" << std::endl;

	for ( XMLSize_t i = 0; i < nSize; ++i )
	{
		pAttributeNode = (DOMAttr*) pAttributes->item( i );
		// get attribute name
		aName = W( pAttributeNode->getName() );

		// get attribute type
		aValue = W( pAttributeNode->getValue() );

		// Print Attribute Name and Value
		//std::cout << "| DEBUG    | " << "\t" << aName << "=" << aValue << std::endl;

		attributeList.insert( std::pair<std::string, std::string>( aName, aValue ) );
	}

	return attributeList;
}

/*
 * This API is adapted(copied) from XersecC-3.1.4-Samples in DOMCount.cpp.
 *
 * LINK to source: TODO need link to source
 *
 */
int Handler::countChildElements ( DOMNode *n, bool printOutEncounteredEles )
{
	DOMNode *child;
	int count = 0;
	if ( n )
	{
		if ( n->getNodeType() == DOMNode::ELEMENT_NODE )
		{
			if ( printOutEncounteredEles )
			{
				//char *name = XMLString::transcode( n->getNodeName() );
				std::string nodeName = W( n->getNodeName() );
				std::cout << "----------------------------------------------------------" << std::endl;
				std::cout << "Encountered Element : " << nodeName << std::endl;

				//XMLString::release( &name );

				if ( n->hasAttributes() )
				{
					// get all the attributes of the node
					DOMNamedNodeMap *pAttributes = n->getAttributes();
					const XMLSize_t nSize = pAttributes->getLength();
					std::cout << "\tAttributes" << std::endl;
					std::cout << "\t----------" << std::endl;
					for ( XMLSize_t i = 0; i < nSize; ++i )
					{
						DOMAttr *pAttributeNode = (DOMAttr*) pAttributes->item( i );
						// get attribute name
						std::string aName = W( pAttributeNode->getName() );

						std::cout << "\t" << aName << "=";
						//XMLString::release (&name);

						// get attribute type
						std::string aValue = W( pAttributeNode->getValue() );
						//name = XMLString::transcode( pAttributeNode->getValue() );
						std::cout << aValue << std::endl;
						//XMLString::release( &name );
					}
				}
			}
			++count;
		}

		for ( child = n->getFirstChild(); child != 0; child = child->getNextSibling() )
		{
			count += countChildElements( child, printOutEncounteredEles );
		}
	}
	return count;
}

void Handler::addUnresolvedReference ( const std::string &name, std::shared_ptr<ecore::EObject> object, std::shared_ptr<ecore::EStructuralFeature> esf )
{
	if(object != nullptr){
		if (esf != nullptr){
			m_unresolvedReferences.push_back( persistence::UnresolvedReference( name, object, esf ) );
		}
		else
		{
			std::cout << "| ERROR    | " <<  __PRETTY_FUNCTION__ << " esf is a nullptr" << std::endl;
		}
	}
	else
	{
		std::cout << "| ERROR    | " <<  __PRETTY_FUNCTION__ << " object is a nullptr" << std::endl;
	}
}

bool Handler::resolveReferences ()
{
	while ( !m_unresolvedReferences.empty() )
	{
		persistence::UnresolvedReference uref = m_unresolvedReferences.back();
		m_unresolvedReferences.pop_back();
		std::string name = uref.refName;
		std::shared_ptr<ecore::EObject> object = uref.eObject;
		std::shared_ptr<ecore::EStructuralFeature> esf = uref.eStructuralFeature;

		boost::any _any = object->eGet( esf );

		if ( esf->getUpperBound() == 1 )
		{
			// EStructuralFeature is a single object
			try
			{
				std::shared_ptr<ecore::EClassifier> _elem = boost::any_cast<std::shared_ptr<ecore::EClassifier> >( _any );

				std::shared_ptr<ecore::EObject> resolved_object = this->get_Object( name );

			}
			catch ( std::exception& e )
			{
				std::cout << "| ERROR    | " <<  __PRETTY_FUNCTION__ << " Exception: " << e.what() << std::endl;
			}
		}
		else
		{
			try
			{
				// EStructuralfeature is a list (Bag/Union/Subset)
				std::shared_ptr<Bag<ecore::EClassifier>> _collection = boost::any_cast<std::shared_ptr<Bag<ecore::EClassifier>> >( _any );
			}
			catch ( std::exception& e )
			{
				std::cout << "| ERROR    | " <<  __PRETTY_FUNCTION__ << " Exception: " << e.what() << std::endl;
			}
		}
	}
	return false;
}

#if 0
{
	std::cout << "| DEBUG    | " << "--- Resolving references" << std::endl;

	static MetaModelRepository_ptr _mmr = MetaModelRepository::_instance();

	while ( !m_unresolved_references.empty() )
	{
		unresolved_reference_t const& ref = m_unresolved_references.back();

		::ecorecpp::mapping::type_traits::string_t const& xpath = ref.xpath;
		::ecorecpp::mapping::type_traits::string_t const& name = ref.ref_name;
		EObject_ptr const& eobj = ref.eobject;
		EClass_ptr const& eclass = ref.eclass;

		try
		{

			DEBUG_MSG( cout, L"--- Resolving reference " << xpath << L" from " << eclass->getName() << L":" << name );

			EStructuralFeature_ptr const esf = eclass->getEStructuralFeature( name );

			DEBUG_MSG( cout, esf->getName() << " " << eclass->getName() );

			// Parse reference
			size_t size = xpath.size();
			const ::ecorecpp::mapping::type_traits::char_t * s = xpath.c_str();

			SemanticState ss;
			reference::State < SemanticState > st( ss, s, size );
			assert( reference::grammar::references::match( st ) );

			references_t& _references = ss.get_references();

			for ( size_t i = 0; i < _references.size(); i++ )
			{
				any _any;
				EObject_ptr _current = m_objects.front();
				processed_reference_t & _ref = _references[i];

				EPackage_ptr pkg = instanceOf < EPackage > (_current);
				if ( !_ref.get_uri().empty() && (!pkg || (pkg && _ref.get_uri() != pkg->getNsURI())) )
				{
					DEBUG_MSG( cout, _ref.get_uri() );
					_current = _mmr->getByNSURI( _ref.get_uri() );
				}

				path_t& _path = _ref.get_path();
				for ( size_t j = 0; j < _path.size(); j++ )
				{
					EClass_ptr cl = instanceOf < EClass > (_current);
					EPackage_ptr pkg = instanceOf < EPackage > (_current);

					::ecorecpp::mapping::type_traits::string_t const& _current_id = _path[j].get_id();

					if ( pkg )
					{
						// Is it a subpackage?
						bool is_subpackage = false;
						std::vector<EPackage_ptr> const& subpkgs = pkg->getESubpackages();

						for ( size_t k = 0; k < subpkgs.size(); k++ )
						if ( subpkgs[k]->getName() == _current_id )
						{
							_current = subpkgs[k];
							is_subpackage = true;
						}

						if ( !is_subpackage )
						{
							_current = pkg->getEClassifier( _current_id );
						}
					}
					else if ( cl )
					{
						_current = cl->getEStructuralFeature( _current_id );
					}
					else
					{
						cl = _current->eClass();
						EStructuralFeature_ptr sesf = cl->getEStructuralFeature( _current_id );

						_any = _current->eGet( sesf );
#if 0
						DEBUG_MSG(cout, _current_id << " " << cl->getName()
								<< " " << _path[j].get_index());
						DEBUG_MSG(cout, _any.type().name());
#endif
						if ( _path[j].is_collection() )
						{
							size_t _index = _path[j].get_index();

							mapping::EEListBase_ptr _collection = any::any_cast < mapping::EEListBase_ptr > (_any);

							assert( _collection->size() > _index );
							DEBUG_MSG( cout, _collection->size() );

							_current = (*_collection)[_index];
						}
						else
						_current = any::any_cast < EObject_ptr > (_any);
					}
				}

				// finally:
				_any = _current;
				eobj->eSet( esf, _any );
			}
		}
		catch ( const char* e )
		{
			ERROR_MSG( "ERROR: " << e );
		}
		catch ( const any::bad_any_cast& e )
		{
			ERROR_MSG( "ERROR: " << e.what() );
		}

		m_unresolved_references.pop_back();
	}

}
#endif

} /* namespace persistence */

