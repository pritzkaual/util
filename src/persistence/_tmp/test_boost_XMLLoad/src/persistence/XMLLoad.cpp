/*
 * XMLLoad.cpp
 *
 *  Created on: 16.05.2017
 *      Author: Alexander
 */

#include "XMLLoad.hpp"

namespace persistence
{

XMLLoad::XMLLoad ()
{

	m_DoNamespaces = false;
	m_DoSchema = false;
	m_SchemaFullChecking = false;
	m_DoCreate = false;

	m_ValScheme = XercesDOMParser::Val_Auto;

	// Initialize the XML4C2 system
	try
	{
		XMLPlatformUtils::Initialize();
	}

	catch ( const XMLException &toCatch )
	{
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

XMLLoad::~XMLLoad ()
{

	XMLPlatformUtils::Terminate();
}

bool XMLLoad::read ( const std::string &filename, std::shared_ptr<persistence::Handler> handler )
{
	//XERCES_CPP_NAMESPACE_USE
	using namespace xercesc_3_1;

	//
	//  Parse the XML file, catching any XML exceptions that might propogate
	//  out of it.
	//
	char* xmlFile = (char*) filename.c_str();

	bool errorsOccured = false;
	try
	{
		m_parser->parse( xmlFile );
	}
	catch ( const OutOfMemoryException& )
	{
		std::cout << "OutOfMemoryException" << std::endl;
		errorsOccured = true;
	}
	catch ( const XMLException& e )
	{
		std::cout << "An error occurred during parsing\n   Message: " << StrX( e.getMessage() ) << std::endl;
		errorsOccured = true;
	}

	catch ( const DOMException& e )
	{
		const unsigned int maxChars = 2047;
		XMLCh errText[maxChars + 1];

		std::cout << "\nDOM Error during parsing: '" << xmlFile << "'\n" << "DOMException code is:  " << e.code << std::endl;

		if ( DOMImplementation::loadDOMExceptionMsg( e.code, errText, maxChars ) )
			std::cout << "Message is: " << StrX( errText ) << std::endl;

		errorsOccured = true;
	}

	catch ( ... )
	{
		std::cout << "An error occurred during parsing\n " << std::endl;
		errorsOccured = true;
	}

	//m_doc = m_parser->getDocument();
	handler->setDOMDocument( m_parser->getDocument() );

	return ((errorsOccured == false) && (m_errReporter->getSawErrors() == false));
}

void XMLLoad::perform ( std::shared_ptr<persistence::Handler> handler )
{

}
} /* namespace persistence */
