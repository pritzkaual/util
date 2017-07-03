/*
 * XMLLoad.cpp
 *
 *  Created on: 16.05.2017
 *      Author: Alexander
 */

#include "XMLLoad.hpp"

namespace persistence {

XMLLoad::XMLLoad () {

	m_DoNamespaces = false;
	m_DoSchema = false;
	m_SchemaFullChecking = false;
	m_DoCreate = false;


	m_ValScheme = XercesDOMParser::Val_Auto;

	// Initialize the XML4C2 system
	try {
		XMLPlatformUtils::Initialize();
	}

	catch ( const XMLException &toCatch ) {
		std::cerr << "Error during Xerces-c Initialization.\n" << "  Exception message:" << StrX( toCatch.getMessage() ) << std::endl;
		return;
	}

	//
	//  Create our parser, then attach an error handler to the parser.
	//  The parser will call back to methods of the ErrorHandler if it
	//  discovers errors during the course of parsing the XML document.
	//

	m_parser = new XercesDOMParser;
	m_parser->setValidationScheme( m_ValScheme );
	m_parser->setDoNamespaces( m_DoNamespaces );
	m_parser->setDoSchema( m_DoSchema );
	m_parser->setHandleMultipleImports( true );
	m_parser->setValidationSchemaFullChecking( m_SchemaFullChecking );
	m_parser->setCreateEntityReferenceNodes( m_DoCreate );

	m_errReporter = new DOMTreeErrorReporter();
	m_parser->setErrorHandler( m_errReporter );

}

XMLLoad::~XMLLoad () {
	/*
	if ( m_doc ) {
		m_doc->release();
	}
	XMLPlatformUtils::Terminate();
	*/
}

bool XMLLoad::getSawErrors () {
	return m_errReporter->getSawErrors();
}

} /* namespace persistence */
