/*
 * Handler.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "Handler.hpp"


#include <sstream> // used for get_Hash()
#include <boost/algorithm/string.hpp> // used for string splitting

namespace persistence
{

Handler::Handler ()
{
	m_doc = nullptr;
	m_rootObject = nullptr;
	m_currentElement = nullptr;
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


std::shared_ptr<ecore::EObject> Handler::getObjectByRef ( std::string id ) // TODO rename to getObject_by_ref(std::string ref)
{
	std::shared_ptr<ecore::EObject> tmp;

	if ( m_refToObject_map.find( id ) != m_refToObject_map.end() )
	{
		// found
		tmp = m_refToObject_map.at( id );
		//return std::dynamic_pointer_cast<ecore::EObject>( tmp );
		return tmp;
	}
	else
	{
		std::cout << "| WARNING  | " << "Given Reference-Name: '" << id << "' is not in stored map." << std::endl;
		return nullptr;
	}
}

void Handler::addToMap ( std::shared_ptr<ecore::EObject> object )
{
	std::string ref = extractReference( object );

	if ( m_refToObject_map.find( ref ) == m_refToObject_map.end() )
	{
		// ref not found in map, so insert
		m_refToObject_map.insert( std::pair<std::string, std::shared_ptr<ecore::EObject>>( ref, object ) );
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
	m_rootObject = nullptr;
	m_currentElement = m_doc->getDocumentElement(); // get root element

	m_rootPrefix = "ecore"; // TODO get prefix from document

	if ( m_currentElement->getNodeType() == DOMNode::ELEMENT_NODE )
	{
		m_currentElements.push_back( m_currentElement );
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


void Handler::setCurrentObject ( std::shared_ptr<ecore::EObject> object )
{
	if (m_rootObject == nullptr)
	{
		m_rootObject = object;
	}
	m_currentObjects.push_back(object);
}

std::shared_ptr<ecore::EObject> Handler::getCurrentObject ()
{
	std::shared_ptr<ecore::EObject> tmp_obj = m_currentObjects.back();
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

			m_currentElement = m_doc->getDocumentElement(); // get root element
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
		addChild( m_currentElement, m_doc->createElement( X( name ) ) );

		return true;
	}
}

void Handler::addChild ( DOMElement* parent_elem, DOMElement* child_elem )
{
	// Add child to parent Element, and set child as current Element.
	m_currentElement = (DOMElement *) parent_elem->appendChild( child_elem );
}

void Handler::addAttribute ( const std::string &name, bool value )
{
	addAttribute( name, (value ? (std::string) "true" : (std::string) "false") );
}

void Handler::addAttribute ( const std::string& name, const std::string& value )
{
	try
	{
		m_currentElement->setAttribute( X( name ), X( value ) );
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

void Handler::addReferences ( const std::string &name, std::shared_ptr<ecore::EObject> object )
{
	try
	{
		std::stringstream ss;
		ss << W(m_currentElement->getAttribute(X( name )));
		ss << " " << extractReference( object );

		addAttribute( name, ss.str() );
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
		//if ( (m_rootObject != pkg) || (m_rootObject == nullptr) )
		if ( m_rootObject != pkg )
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
	//else if ( (to_antecessors.back() == m_rootObject) || (m_rootObject == nullptr) )
	else if ( to_antecessors.back() == m_rootObject )
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

			//if ( (m_rootObject != dPck) || (m_rootObject == nullptr) )
			if(auto ePck = dPck.lock())
			{
				if ( m_rootObject != ePck) // TODO use here other way to find equality of m_rootObject and current EPackage-Obj
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
	return value.str();
}

void Handler::release ()
{
	if ( m_currentElement == nullptr )
	{
		std::cout << "| ERROR    | " << "You can't call " << __PRETTY_FUNCTION__ << " while current DOMElement m_currentElement is nullptr." << std::endl;
	}
	else
	{
		// set m_currentElement's parent node as new m_currentElement (decrease depth)
		m_currentElement = (DOMElement*) m_currentElement->getParentNode();
	}
}

void Handler::releaseObj ()
{
	std::shared_ptr<ecore::EObject> tmp_obj = m_currentObjects.back();

	if ( tmp_obj == nullptr )
	{
		std::cout << "| ERROR    | " << "You can't call " << __PRETTY_FUNCTION__ << " while current Object is nullptr." << std::endl;
	}
	else
	{
		// set current (container) object as new current object (decrease depth)
		m_currentObjects.pop_back();
	}
}

int Handler::getNumOfChildNodes ()
{
	DOMNode *child;
	unsigned int count = 0;

	for ( child = m_currentElement->getLastChild(); child != 0; child = child->getPreviousSibling() )
	{
		if ( child->getNodeType() == DOMNode::ELEMENT_NODE )
		{
			++count;
		}
	}
	if ( count != m_currentElement->getChildElementCount() )
	{
		std::cout << "| ERROR    | " << " In " << __PRETTY_FUNCTION__ << " different Number of Children." << std::endl;
	}
	return count;
}

std::string Handler::getNextNodeName ()
{
	std::string nodeName;
	DOMNode *child;

	if ( m_currentElements.size() == 0 )
	{
		nodeName = "";
	}
	else
	{
		m_currentElement = (DOMElement*) m_currentElements.back();

		nodeName = W( m_currentElement->getNodeName() );

		m_currentElements.pop_back();

		for ( child = m_currentElement->getLastChild(); child != 0; child = child->getPreviousSibling() )
		{
			if ( child->getNodeType() == DOMNode::ELEMENT_NODE )
			{
				m_currentElements.push_back( child );
			}
		}

#if 0
		std::cout << "| DEBUG    | " << "Node-List: " << std::endl << "|          | ";
		for ( auto current_elem : m_currentElements )
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

	DOMNamedNodeMap *pAttributes = m_currentElement->getAttributes();
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

void Handler::resolveReferences ()
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
				std::shared_ptr<ecore::EClassifier> resolved_object = std::dynamic_pointer_cast<ecore::EClassifier>(this->getObjectByRef( name ));
				assert(resolved_object);
				object->eSet(esf, resolved_object);
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
				std::list<std::shared_ptr<ecore::EObject> >references;
				std::shared_ptr<ecore::EObject> resolved_object;
				std::list<std::string> _strs;
				std::string _tmpStr;

				boost::split(_strs, name, boost::is_any_of(" "));
				while(_strs.size() > 0)
				{
					_tmpStr = _strs.front();
					if(std::string::npos != _tmpStr.find("#//")){
						resolved_object = this->getObjectByRef(_tmpStr);
						if (resolved_object)
						{
							references.push_back(resolved_object);
						}
					}
					_strs.pop_front();
				}

				object->resolveReferences(esf->getFeatureID(), references);

			}
			catch ( std::exception& e )
			{
				std::cout << "| ERROR    | " <<  __PRETTY_FUNCTION__ << " Exception: " << e.what() << std::endl;
			}
		}
	}
}

} /* namespace persistence */

