/*
 * SaveHandler.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "SaveHandler.hpp"


#include <sstream> // used for get_Hash()
#include <boost/algorithm/string.hpp> // used for string splitting

namespace persistence
{

SaveHandler::SaveHandler ()
{
	m_doc = nullptr;
	m_rootObject = nullptr;
	m_currentElement = nullptr;
}

SaveHandler::~SaveHandler ()
{

}

void SaveHandler::deleteHandler ()
{
	if ( m_doc )
	{
		m_doc->release();
	}
}

/**/
DOMDocument *SaveHandler::getDOMDocument ()
{
	return m_doc;
}

std::string SaveHandler::getPrefix ()
{
	return m_rootPrefix;
}


void SaveHandler::setRootObject ( std::shared_ptr<ecore::EObject> object )
{
	if (m_rootObject == nullptr)
	{
		m_rootObject = object;
	}
}

bool SaveHandler::createRootNode ( const std::string& name, const std::string& ns_uri )
{
	return this->createRootNode( name, ns_uri, nullptr );
}

bool SaveHandler::createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri )
{
	return this->createRootNode( prefix, name, ns_uri, nullptr );
}

bool SaveHandler::createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype )
{
	m_rootPrefix = prefix;
	return this->createRootNode( prefix + ":" + name, ns_uri, nullptr );
}

bool SaveHandler::createRootNode ( const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype )
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
			std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << " DOMException code is:  " << e.code << std::endl << W( e.getMessage() ) << std::endl;
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

bool SaveHandler::createAndAddElement ( const std::string& name )
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

void SaveHandler::addChild ( DOMElement* parent_elem, DOMElement* child_elem )
{
	// Add child to parent Element, and set child as current Element.
	m_currentElement = (DOMElement *) parent_elem->appendChild( child_elem );
}

void SaveHandler::addAttribute ( const std::string &name, bool value )
{
	addAttribute( name, (value ? (std::string) "true" : (std::string) "false") );
}

void SaveHandler::addAttribute ( const std::string& name, const std::string& value )
{
	try
	{
		m_currentElement->setAttribute( X( name ), X( value ) );
	}
	catch ( const DOMException& e )
	{
		std::cout << "| ERROR    | " << "DOMException code is:  " << e.code << std::endl << W( e.getMessage() ) << std::endl;
	}
	catch ( std::exception& e )
	{
		std::cout << "| ERROR    | " << "Exception code is:  " << e.what() << std::endl;
	}
}

void SaveHandler::addReference ( const std::string &name, std::shared_ptr<ecore::EObject> object )
{
	addAttribute( name, extractReference( object ) );
}

void SaveHandler::addReferences ( const std::string &name, std::shared_ptr<ecore::EObject> object )
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
		std::cout << "| ERROR    | " << "DOMException code is:  " << e.code << std::endl << W( e.getMessage() ) << std::endl;
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
std::string SaveHandler::extractType ( std::shared_ptr<ecore::EObject> obj ) const
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
std::string SaveHandler::extractReference ( std::shared_ptr<ecore::EObject> to ) const
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

void SaveHandler::release ()
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

} /* namespace persistence */

