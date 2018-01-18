/*
 * HandlerHelper.cpp
 *
 *  Created on: 29.05.2017
 *      Author: Alexander
 */

#include "HandlerHelper.hpp"

#include <sstream> // used for extractType()

namespace persistence
{

HandlerHelper::HandlerHelper ()
{ }

HandlerHelper::~HandlerHelper ()
{ }

/*
 * This API is adapted to API in Project emf4cpp.
 *
 * LINK to source: https://github.com/catedrasaes-umu/emf4cpp/tree/master/emf4cpp/ecorecpp/serializer/serializer-xerces.cpp
 * ::ecorecpp::mapping::type_traits::string_t serializer::get_type(EObject_ptr obj) const
 *
 */
std::string HandlerHelper::extractType (const std::shared_ptr<ecore::EObject> obj, std::string prefix)
{
	std::stringstream ss;
	std::shared_ptr<ecore::EClass> metaClass = obj->eClass();

	if (!prefix.empty())
	{
		ss << prefix << ":" << metaClass->getName();
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
std::string HandlerHelper::extractReference ( const std::shared_ptr<ecore::EObject> toObject, const std::shared_ptr<ecore::EObject> rootObject, std::string prefix )
{
	std::stringstream value;
	std::list<std::shared_ptr<ecore::EObject> > to_antecessors;
	std::shared_ptr<ecore::EObject> antecessor = toObject; //pre-init antecessor

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
		if ( rootObject != pkg )
		{
			value << extractType( toObject, prefix ) << " " << pkg->getNsURI(); // TODO this case is not tested yet
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
	else if ( to_antecessors.back() == rootObject )
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
		std::shared_ptr<ecore::EDataType> dataType = std::dynamic_pointer_cast<ecore::EDataType>( toObject );

		if ( dataType )
		{
			std::weak_ptr<ecore::EPackage> dPck = dataType->getEPackage();

			//if ( (m_rootObject != dPck) || (m_rootObject == nullptr) )
			if(auto ePck = dPck.lock())
			{
				if ( rootObject != ePck) // TODO use here other way to find equality of m_rootObject and current EPackage-Obj
				{
					value << extractType( toObject, prefix ) << " " << ePck->getNsURI(); // TODO this case is not tested yet
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

} /* namespace persistence */

