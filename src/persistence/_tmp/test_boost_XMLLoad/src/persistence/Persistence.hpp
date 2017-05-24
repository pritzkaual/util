/*
 * Persistence.hpp
 *
 *  Created on: 16.05.2017
 *      Author: Alexander
 */

#ifndef PERSISTENCE_HPP_
#define PERSISTENCE_HPP_

#include "XMLLoad.hpp"
#include "XMLSave.hpp"

namespace persistence {

class Persistence {
public:
	virtual ~Persistence ();
	Persistence ();
};

} /* namespace persistence */

#endif /* PERSISTENCE_HPP_ */
