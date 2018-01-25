/*
 * XMLSaveHandler.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "XMLSaveHandler.hpp"

#include <sstream> // used for addReferences()
#include <boost/algorithm/string.hpp> // used for string splitting

namespace XMLPersistence
{

XMLSaveHandler::XMLSaveHandler ()
{
	m_doc = nullptr;
	m_currentElement = nullptr;
}

XMLSaveHandler::~XMLSaveHandler ()
{
	if ( m_doc )
	{
		m_doc->release();
	}
}

/**/
void XMLSaveHandler::setDOMDocument ( DOMDocument * doc )
{
	//assert(doc);
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

DOMDocument *XMLSaveHandler::getDOMDocument ()
{
	return m_doc;
}

bool XMLSaveHandler::createRootNode ( const std::string& name, const std::string& ns_uri )
{
	return this->createRootNode( name, ns_uri, nullptr );
}

bool XMLSaveHandler::createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri )
{
	return this->createRootNode( prefix, name, ns_uri, nullptr );
}

bool XMLSaveHandler::createRootNode ( const std::string& prefix, const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype )
{
	m_rootPrefix = prefix;
	return this->createRootNode( prefix + ":" + name, ns_uri, doctype );
}

bool XMLSaveHandler::createRootNode ( const std::string& name, const std::string& ns_uri, DOMDocumentType *doctype )
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

bool XMLSaveHandler::createAndAddElement ( const std::string& name )
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

void XMLSaveHandler::addChild ( DOMElement* parent_elem, DOMElement* child_elem )
{
	// Add child to parent Element, and set child as current Element.
	m_currentElement = (DOMElement *) parent_elem->appendChild( child_elem );
}

void XMLSaveHandler::addAttribute ( const std::string& name, const std::string& value )
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

void XMLSaveHandler::addReferences ( const std::string &name, std::shared_ptr<ecore::EObject> object )
{
	try
	{
		std::string ref = BasePersistence::HandlerHelper::extractReference(object, m_rootObject, m_rootPrefix);

		std::stringstream ss;
		std::string tmpStr = W(m_currentElement->getAttribute(X( name )));

		if (!tmpStr.empty())
		{
			ss << tmpStr << " ";
		}
		ss << ref;

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


void XMLSaveHandler::release ()
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

} /* namespace BasePersistence */
