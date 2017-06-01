/*
 * Option.hpp
 *
 *  Created on: 30.05.2017
 *      Author: Alexander
 */

#ifndef OPTION_HPP_
#define OPTION_HPP_

#include <string>
#include <set>

#include "boost/property_tree/xml_parser.hpp"
#include "boost/lexical_cast.hpp"

namespace persistence {

class Option {

public:
	/**
	 *
	 */
	static const std::string OPTION_SAVE_JSON;
	/**
	 *
	 */
	static const std::string OPTION_SAVE_XML;
	/**
	 *
	 */
	static const std::string OPTION_USE_ID;
	/**
	 *
	 */
	static const std::string OPTION_LOAD_TRIM_WHITESPACE;
	/**
	 *
	 */

	static std::set<std::string> get_DefaultOptions();
};

} /* namespace persistence */

#endif /* OPTION_HPP_ */
