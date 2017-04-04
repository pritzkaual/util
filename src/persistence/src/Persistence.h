#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "EPackage.hpp"
#include "EFactory.hpp"

namespace persistence {

class Persistence {
public:
	Persistence();
	virtual ~Persistence();

	void serialize();
	void deserialize();




};

} /* namespace persistence */

#endif /* PERSISTENCE_H */
