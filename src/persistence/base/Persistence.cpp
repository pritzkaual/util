/*
 * Persistence.cpp
 *
 *  Created on: 16.05.2017
 *      Author: Alexander
 */

#include "Persistence.hpp"
#include "Load.hpp"
#include "Save.hpp"

using namespace std;

namespace persistence
{
namespace base
{

Persistence::Persistence ()
{

}

Persistence::~Persistence ()
{
	// TODO Auto-generated destructor stub
}

bool Persistence::isValidFile ( const std::string& filename )
{
	//boost::filesystem::path file( filename );
	// TODO needs implementation
	std::cout << "| WARNING  | " << __PRETTY_FUNCTION__ << " is not implemented!" << std::endl;

	return true;
}

} /* namespace base */
} /* namespace persistence */
