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
namespace base
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
	std::stringstream ref;
	std::list<std::shared_ptr<ecore::EObject> > to_antecessors;
	std::shared_ptr<ecore::EObject> antecessor = toObject; //pre-init antecessor

	if(!toObject)
	{
		std::cout << "| ERROR    | " << __FUNCTION__ << " Given Parameter 'toObject' is nullptr." << std::endl;
		return ref.str();
	}

	while ( antecessor )
	{
		to_antecessors.push_back( antecessor );
		antecessor = to_antecessors.back()->eContainer();
	}


	// This case is used for ecore-models
	std::shared_ptr<ecore::EPackage> rootPkg = std::dynamic_pointer_cast<ecore::EPackage>( to_antecessors.back() );

	if ( rootPkg )
	{
		// Remove root Package from 'to_antecessors' because it is not used in reference name
		to_antecessors.pop_back();

		if ( rootObject != rootPkg )
		{
			ref << extractType( toObject, prefix ) << " " << rootPkg->getNsURI(); // TODO this case is not tested yet
		}

		ref << "#/";

		// Add Package name(s) and Class/Enum/EDataType name to 'value'
		while ( to_antecessors.size() > 0 )
		{
			std::shared_ptr<ecore::ENamedElement> to_antecessors_back = std::dynamic_pointer_cast<ecore::ENamedElement>( to_antecessors.back() );
			std::shared_ptr<ecore::EAnnotation> to_antecessors_back_annotation = std::dynamic_pointer_cast<ecore::EAnnotation>( to_antecessors.back() );

			if ( to_antecessors_back != nullptr )
			{
				ref << "/" << to_antecessors_back->getName();
			}
			else if ( to_antecessors_back_annotation != nullptr )
			{
				ref << "/" << "%"<< to_antecessors_back_annotation->getSource() << "%";
			}
			else
			{
				std::cout << "| ERROR    | " << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "() " << "During casting Object of type '" << to_antecessors.back()->eClass()->getName() << "' to 'ENamedElement'." << std::endl;
			}
			to_antecessors.pop_back();
		}
	}
#if 0
	//else if ( (to_antecessors.back() == m_rootObject) || (m_rootObject == nullptr) )
	else if ( to_antecessors.back() == rootObject )
	{
		// This case is used for Non-Ecore-Models
		// TODO implement and test this case

		std::cout << "| ERROR    | " << " Called " << __FUNCTION__ << " while else-if-case (Non-Ecore-Models) is not tested yet." << std::endl;

		ref << "/";
		std::shared_ptr<ecore::EObject> prev = to_antecessors.back();
		to_antecessors.pop_back();

		while ( to_antecessors.size() > 0 )
		{
			std::shared_ptr<ecore::EStructuralFeature> esf = to_antecessors.back()->eContainingFeature();

			if ( esf->getUpperBound() == 1 )
				ref << "/" << esf->getName();

			else
			{
				boost::any _any = prev->eGet( esf );

				std::shared_ptr<Bag<ecore::EObject>> ef = boost::any_cast<std::shared_ptr<Bag<ecore::EObject>>>( _any );

				// calculate the index of back at father's collection
				size_t index_of = 0;
				for ( ; index_of < ef->size() && (*ef)[index_of] != to_antecessors.back(); index_of++ );

				ref << "/@" << esf->getName() << "." << index_of;
			}

			prev = to_antecessors.back();
			to_antecessors.pop_back();
		}
	}
#endif
	else
	{
		std::shared_ptr<ecore::EClassifier> clsObj = std::dynamic_pointer_cast<ecore::EClassifier>( toObject );
		if(clsObj)
		{
			// This case is used for Class/Enum/EDataType that are not contained within a Package
			std::weak_ptr<ecore::EPackage> dPck = clsObj->getEPackage();

			//if ( (m_rootObject != dPck) || (m_rootObject == nullptr) )
			if(auto ePck = dPck.lock())
			{
				if ( rootObject != ePck) // TODO use here other way to find equality of m_rootObject and current EPackage-Obj
				{
					ref << extractType( toObject, prefix ) << " " << ePck->getNsURI(); // TODO this case is not tested yet
				}
			}
			ref << "#/";
			ref << "/" << clsObj->getName();
		}
		else
		{
			std::cout << "| WARNING  | " << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "() " << "Given Object's type '" << toObject->eClass()->getName() << "' is not 'EClassifier'." << std::endl;
		}
	}

	return ref.str();
}

} /* namespace base */
} /* namespace persistence */
