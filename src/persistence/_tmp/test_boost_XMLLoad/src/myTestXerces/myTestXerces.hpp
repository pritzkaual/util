/*
 * myTestXerces.hpp
 *
 *  Created on: 23.06.2017
 *      Author: Alexander
 */

#ifndef MYTESTXERCES_HPP_
#define MYTESTXERCES_HPP_

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/dom/DOMException.hpp>

#include <xercesc/dom/DOM.hpp>


#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include "DOMTreeErrorReporter.hpp"
#include "DOMPrintFilter.hpp"
#include "DOMPrintErrorHandler.hpp"


#include "XStr.h"



#include <string.h>
#include <stdlib.h>

//#include <iostream>




namespace testXerces {

#define X(str) testXerces::XStr(str).unicodeForm()


class myTestXerces {
private:
	// ---------------------------------------------------------------------------
	//  Local data
	//
	//  gXmlFile
	//      The path to the file to parser. Set via command line.
	//
	//  gDoNamespaces
	//      Indicates whether namespace processing should be done.
	//
	//  gDoSchema
	//      Indicates whether schema processing should be done.
	//
	//  gSchemaFullChecking
	//      Indicates whether full schema constraint checking should be done.
	//
	//  gDoCreate
	//      Indicates whether entity reference nodes needs to be created or not
	//      Defaults to false
	//
	//  gOutputEncoding
	//      The encoding we are to output in. If not set on the command line,
	//      then it is defaults to the encoding of the input XML file.
	//
	//  gSplitCdataSections
	//      Indicates whether split-cdata-sections is to be enabled or not.
	//
	//  gDiscardDefaultContent
	//      Indicates whether default content is discarded or not.
	//
	//  gUseFilter
	//      Indicates if user wants to plug in the DOMPrintFilter.
	//
	//  gValScheme
	//      Indicates what validation scheme to use. It defaults to 'auto', but
	//      can be set via the -v= command.
	//
	// ---------------------------------------------------------------------------
	char* m_XmlFile;
	bool m_DoNamespaces;
	bool m_DoSchema;
	bool m_SchemaFullChecking;
	bool m_DoCreate;

	char* m_outputfile;
	char* m_XPathExpression;

	// options for DOMLSSerializer's features
	XMLCh* m_OutputEncoding;

	bool m_SplitCdataSections;
	bool m_DiscardDefaultContent;
	bool m_UseFilter;
	bool m_FormatPrettyPrint;
	bool m_WriteBOM;

	XercesDOMParser::ValSchemes m_ValScheme;

	//
	// Parser and Error	handler
	//
	XercesDOMParser *m_parser;
	DOMTreeErrorReporter *m_errReporter;

	// get the DOM representation
	DOMDocument *m_doc;

public:

	myTestXerces ();
	~myTestXerces ();

	bool load ( const std::string &filename );
	void save ( const std::string &filename );

	void createTestDOMDocument();

	//void print(boost::property_tree::ptree const& pt);

	bool getSawErrors ();
};

} /* namespace xerces */

#endif /* MYTESTXERCES_HPP_ */
