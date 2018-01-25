/*
 * LoadHandler.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "LoadHandler.hpp"

#include <sstream> // used for getLevel()
#include <boost/algorithm/string.hpp> // used for string splitting

namespace BasePersistence
{

LoadHandler::LoadHandler ()
{
	m_rootObject = nullptr;
	m_level = -1;
}

LoadHandler::~LoadHandler ()
{

}

std::shared_ptr<ecore::EObject> LoadHandler::getObjectByRef ( std::string ref )
{
	std::shared_ptr<ecore::EObject> tmp;

	if (!ref.empty())
	{
		if ( m_refToObject_map.find( ref ) != m_refToObject_map.end() )
		{
			// found
			tmp = m_refToObject_map.at( ref );
			//return std::dynamic_pointer_cast<ecore::EObject>( tmp );
		}
		else
		{
			size_t double_dot = ref.find("#//", 0);
			std::string _ref_prefix = ref.substr(0, double_dot); // TODO '_ref_prefix' is not used in this case
			std::string _ref_name = ref.substr(double_dot);

			if ( m_refToObject_map.find( _ref_name ) != m_refToObject_map.end() )
			{
				// found
				tmp = m_refToObject_map.at( _ref_name );
				//return std::dynamic_pointer_cast<ecore::EObject>( tmp );
			}
			else
			{
				std::cout << "| WARNING  | " << "Given Reference-Name: '" << ref << "' or '"<< _ref_name << "' are not in stored map." << std::endl;
				return nullptr;
			}
		}
	}
	return tmp;
}

void LoadHandler::addToMap ( std::shared_ptr<ecore::EObject> object )
{
	std::string ref = BasePersistence::HandlerHelper::extractReference(object, m_rootObject, m_rootPrefix);


	if (!ref.empty())
	{
		if ( m_refToObject_map.find( ref ) == m_refToObject_map.end() )
		{
			// ref not found in map, so insert
			m_refToObject_map.insert( std::pair<std::string, std::shared_ptr<ecore::EObject>>( ref, object ) );

			std::cout << "| DEBUG    | " << "Add to map: '" << ref << "'" << std::endl;
		}
	}
}
/**/

std::string LoadHandler::getPrefix ()
{
	return m_rootPrefix;
}

std::string LoadHandler::getLevel()
{
	std::stringstream ss;
	for (int ii = 0; ii < m_level; ii++)
	{
		ss << " ";
	}
	return ss.str();
}

void LoadHandler::setCurrentObject ( std::shared_ptr<ecore::EObject> object )
{
	if (m_rootObject == nullptr)
	{
		m_rootObject = object;
	}
	m_level++;
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
	return BasePersistence::HandlerHelper::extractType(obj, m_rootPrefix);
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
		m_level--;
	}
}


void LoadHandler::addUnresolvedReference ( const std::string &name, std::shared_ptr<ecore::EObject> object, std::shared_ptr<ecore::EStructuralFeature> esf )
{
	if(object != nullptr){
		if (esf != nullptr){
			m_unresolvedReferences.push_back( BasePersistence::UnresolvedReference( name, object, esf ) );
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
		BasePersistence::UnresolvedReference uref = m_unresolvedReferences.back();
		m_unresolvedReferences.pop_back();

		std::string name = uref.refName;
		std::shared_ptr<ecore::EObject> object = uref.eObject;
		std::shared_ptr<ecore::EStructuralFeature> esf = uref.eStructuralFeature;

		std::list<std::shared_ptr<ecore::EObject> >references;
		std::shared_ptr<ecore::EObject> resolved_object;

		try
		{
			if ( esf->getUpperBound() == 1 )
			{
				// EStructuralFeature is a single object

				resolved_object = this->getObjectByRef( name );
				//assert(resolved_object);
				if(resolved_object)
				{
					references.push_back(resolved_object);

					// Call resolveReferences() of corresponding 'object'
					object->resolveReferences(esf->getFeatureID(), references);
					//object->eSet(esf, resolved_object); // use eSet() instead resolveReferences()
				}
			}
			else
			{
				// EStructuralFeature is a list of objects

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

} /* namespace BasePersistence */

