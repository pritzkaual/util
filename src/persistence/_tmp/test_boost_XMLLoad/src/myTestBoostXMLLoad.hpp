/*
 * myTestBoostXMLLoad.hpp
 *
 *  Created on: 02.05.2017
 *      Author: Alexander
 */

#ifndef MYTESTBOOSTXMLLOAD_HPP_
#define MYTESTBOOSTXMLLOAD_HPP_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <map>
#include <exception>
#include <iostream>

namespace testBoostXMLLoad {

class myTestBoostXMLLoad {
public:
	std::string m_file;               // log filename
	int m_level;                      // debug level
	std::set<std::string> m_elements;
	std::map<std::string, boost::property_tree::ptree> m_objectMap;

	boost::property_tree::ptree m_tree;

	myTestBoostXMLLoad();
	virtual ~myTestBoostXMLLoad();

	void load(const std::string &filename);
	void save(const std::string &filename);
	void print(boost::property_tree::ptree const& pt);


};

} /* namespace testBoostXMLLoad */

#endif /* MYTESTBOOSTXMLLOAD_HPP_ */
