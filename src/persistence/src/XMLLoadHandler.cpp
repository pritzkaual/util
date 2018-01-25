/*
 * XMLLoadHandler.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "XMLLoadHandler.hpp"

#include <sstream> // used for getLevel()
#include <boost/algorithm/string.hpp> // used for string splitting

namespace XMLPersistence
{

XMLLoadHandler::XMLLoadHandler ()
{
	m_doc = nullptr;
	m_currentElement = nullptr;
}

XMLLoadHandler::~XMLLoadHandler ()
{
	if ( m_doc )
	{
		m_doc->release();
	}
}

/**/

DOMDocument *XMLLoadHandler::getDOMDocument ()
{
	return m_doc;
}

void XMLLoadHandler::setDOMDocument ( DOMDocument * doc )
{
	assert(doc);
	if (doc == nullptr)
	{
		std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << " Current DOMDocument 'doc' is empty." << std::endl;
		return;
	}
	m_doc = doc;
	m_rootObject = nullptr;
	m_currentElement = m_doc->getDocumentElement(); // get root element

	if (!m_currentElement)
	{
		std::cout << "| ERROR    | " << __PRETTY_FUNCTION__ << " Current DOMElement (root) does not exist." << std::endl;
		assert(m_currentElement);
	}

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


unsigned int XMLLoadHandler::getNumOfChildNodes ()
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
	//std::cout << getLevel() << "ChildNodes: " << count << std::endl;
	return count;
}

std::string XMLLoadHandler::getNextNodeName ()
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

std::map<std::string, std::string> XMLLoadHandler::getAttributeList ()
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

} /* namespace XMLPersistence */

