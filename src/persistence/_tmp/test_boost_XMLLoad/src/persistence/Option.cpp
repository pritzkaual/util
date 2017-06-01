/*
 * Option.cpp
 *
 *  Created on: 30.05.2017
 *      Author: Alexander
 */

#include "Option.hpp"

namespace persistence {

const std::string Option::OPTION_SAVE_JSON = "OPTION_SAVE_JSON";

const std::string Option::OPTION_SAVE_XML = "OPTION_SAVE_XML";

const std::string Option::OPTION_USE_ID = "OPTION_USE_ID";

const std::string Option::OPTION_LOAD_TRIM_WHITESPACE = boost::lexical_cast<std::string>(boost::property_tree::xml_parser::trim_whitespace);


std::set<std::string> Option::get_DefaultOptions () {
	std::set<std::string> default_options;

	default_options.insert( Option::OPTION_SAVE_XML );
	default_options.insert( Option::OPTION_USE_ID );
	default_options.insert( Option::OPTION_LOAD_TRIM_WHITESPACE );

	return default_options;
}

}/* namespace persistence */
