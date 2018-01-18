/*
 * JSONSave.hpp
 *
 *  Created on: 30.05.2017
 *      Author: Alexander
 */

#ifndef JSONSAVE_HPP_
#define JSONSAVE_HPP_

#include "Save.hpp"
#include "boost/property_tree/json_parser.hpp"


namespace persistence {

class JSONSave : public Save {
public:
	virtual ~JSONSave ();
	JSONSave ();


private:
	bool write (const std::string &filename);
};

} /* namespace persistence */

#endif /* JSONSAVE_HPP_ */
