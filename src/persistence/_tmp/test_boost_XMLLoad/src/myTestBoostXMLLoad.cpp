/*
 * myTestBoostXMLLoad.cpp
 *
 *  Created on: 02.05.2017
 *      Author: Alexander
 */

#include "myTestBoostXMLLoad.hpp"

namespace testBoostXMLLoad {

myTestBoostXMLLoad::myTestBoostXMLLoad () :
				m_level( 0 ) {
	// TODO Auto-generated constructor stub

}

// TODO Auto-generated destructor stub
myTestBoostXMLLoad::~myTestBoostXMLLoad () {
}

void myTestBoostXMLLoad::load ( const std::string& filename ) {
	// Create empty property tree object
	//boost::property_tree::ptree tree;

	// Parse the XML into the property tree.
	//boost::property_tree::read_xml(filename, m_tree);
	boost::property_tree::read_xml( filename, m_tree, boost::property_tree::xml_parser::trim_whitespace );

	/*
	 // Use the throwing version of get to find the debug filename.
	 // If the path cannot be resolved, an exception is thrown.
	 m_file = tree.get<std::string>("debug.filename");

	 // Use the default-value version of get to find the debug level.
	 // Note that the default value is used to deduce the target type.
	 m_level = tree.get("debug.level", 0);

	 // Use get_child to find the node containing the modules, and iterate over
	 // its children. If the path cannot be resolved, get_child throws.
	 // A C++11 for-range loop would also work.
	 */
	print( m_tree );
}

void myTestBoostXMLLoad::print ( boost::property_tree::ptree const& pt ) {

	boost::property_tree::ptree::const_iterator end = pt.end();
	for ( boost::property_tree::ptree::const_iterator it = pt.begin(); it != end; ++it ) {
		std::cout << it->first << " " << it->second.get_value<std::string>() << std::endl;
		print( it->second );
	}
}
/*
 BOOST_FOREACH(boost::property_tree::ptree::value_type &v, m_tree)
 {
 // The data function is used to access the data stored in a node.
 std::cout << v.second.data() << std::endl;
 m_objectMap[v.first] = v.second;
 m_elements.insert(v.second.data());
 }
 */

void myTestBoostXMLLoad::save ( const std::string& filename ) {
	/*
	 // Create an empty property tree object.
	 boost::property_tree::ptree tree;

	 // Put the simple values into the tree. The integer is automatically
	 // converted to a string. Note that the "debug" node is automatically
	 // created if it doesn't exist.

	 tree.put("debug.filename", m_file);
	 tree.put("debug.level", m_level);

	 // Add all the modules. Unlike put, which overwrites existing nodes, add
	 // adds a new node at the lowest level, so the "modules" node will have
	 // multiple "module" children.

	 BOOST_FOREACH(const std::string &name, m_modules)
	 tree.add("debug.modules.module", name);
	 */

	// Set xml_writer_settings
	// Write property tree to XML file
	//boost::property_tree::write_xml(filename, m_tree);
	//boost::property_tree::write_xml(filename, m_tree, std::locale(), boost::property_tree::xml_writer_make_settings<std::string>('\t', 1));
	boost::property_tree::write_xml( filename, m_tree, std::locale(), boost::property_tree::xml_writer_make_settings<std::string>( ' ', 2 ) );
	//boost::property_tree::write_xml(filename, m_tree, std::locale(), boost::property_tree::xml_writer_make_settings<std::string>('\n', 1));
}

} /* namespace testBoostXMLLoad */
