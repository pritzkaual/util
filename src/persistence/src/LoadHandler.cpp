/*
 * LoadHandler.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "LoadHandler.hpp"


#include <sstream> // used for get_Hash()
#include <boost/algorithm/string.hpp> // used for string splitting

namespace persistence
{

LoadHandler::LoadHandler ()
{
	m_doc = nullptr;
	m_rootObject = nullptr;
	m_currentElement = nullptr;
}

LoadHandler::~LoadHandler ()
{

}

void LoadHandler::deleteHandler ()
{
	if ( m_doc )
	{
		m_doc->release();
	}
}


std::shared_ptr<ecore::EObject> LoadHandler::getObjectByRef ( std::string ref ) // TODO rename to getObject_by_ref(std::string ref)
{
	std::shared_ptr<ecore::EObject> tmp;

	if ( m_refToObject_map.find( ref ) != m_refToObject_map.end() )
	{
		// found
		tmp = m_refToObject_map.at( ref );
		//return std::dynamic_pointer_cast<ecore::EObject>( tmp );
		return tmp;
	}
	else
	{
		std::cout << "| WARNING  | " << "Given Reference-Name: '" << ref << "' is not in stored map." << std::endl;
		return nullptr;
	}
}

void LoadHandler::addToMap ( std::shared_ptr<ecore::EObject> object )
{
	std::string ref = persistence::HandlerHelper::extractReference(object, m_rootObject, m_rootPrefix);

	if ( m_refToObject_map.find( ref ) == m_refToObject_map.end() )
	{
		// ref not found in map, so insert
		m_refToObject_map.insert( std::pair<std::string, std::shared_ptr<ecore::EObject>>( ref, object ) );
	}
}
/**/

DOMDocument *LoadHandler::getDOMDocument ()
{
	return m_doc;
}

void LoadHandler::setDOMDocument ( DOMDocument * doc )
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

std::string LoadHandler::getPrefix ()
{
	return m_rootPrefix;
}


void LoadHandler::setCurrentObject ( std::shared_ptr<ecore::EObject> object )
{
	if (m_rootObject == nullptr)
	{
		m_rootObject = object;
	}
	m_currentObjects.push_back(object);
}

std::shared_ptr<ecore::EObject> LoadHandler::getCurrentObject ()
{
	std::shared_ptr<ecore::EObject> tmp_obj = m_currentObjects.back();
	assert(tmp_obj);

	return tmp_obj;
}

/*
 * This API is adapted to API in Project emf4cpp.
 *
 * LINK to source: https://github.com/catedrasaes-umu/emf4cpp/tree/master/emf4cpp/ecorecpp/serializer/serializer-xerces.cpp
 * ::ecorecpp::mapping::type_traits::string_t serializer::get_type(EObject_ptr obj) const
 *
 */
std::string LoadHandler::extractType ( std::shared_ptr<ecore::EObject> obj ) const
{
	return persistence::HandlerHelper::extractType(obj, m_rootPrefix);
}

void LoadHandler::release ()
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

int LoadHandler::getNumOfChildNodes ()
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

std::string LoadHandler::getNextNodeName ()
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

std::map<std::string, std::string> LoadHandler::getAttributeList ()
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

void LoadHandler::addUnresolvedReference ( const std::string &name, std::shared_ptr<ecore::EObject> object, std::shared_ptr<ecore::EStructuralFeature> esf )
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

void LoadHandler::resolveReferences ()
{
	while ( !m_unresolvedReferences.empty() )
	{
		persistence::UnresolvedReference uref = m_unresolvedReferences.back();
		m_unresolvedReferences.pop_back();

		std::string name = uref.refName;
		std::shared_ptr<ecore::EObject> object = uref.eObject;
		std::shared_ptr<ecore::EStructuralFeature> esf = uref.eStructuralFeature;
		try
		{
			if ( esf->getUpperBound() == 1 )
			{
				// EStructuralFeature is a single object
				std::shared_ptr<ecore::EClassifier> resolved_object = std::dynamic_pointer_cast<ecore::EClassifier>(this->getObjectByRef( name ));
				assert(resolved_object);
				if(resolved_object)
				{
					object->eSet(esf, resolved_object);
				}
			}
			else
			{
				// EStructuralFeature is a single object
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
				// Call resolveReferences() of corresponding 'object'
				object->resolveReferences(esf->getFeatureID(), references);
			}
		}
		catch ( std::exception& e )
		{
			std::cout << "| ERROR    | " <<  __PRETTY_FUNCTION__ << " Exception: " << e.what() << std::endl;
		}
	}
}

} /* namespace persistence */

