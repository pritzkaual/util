/*
 * XMLSave.cpp
 *
 *  Created on: 16.05.2017
 *      Author: Alexander
 */

#include "XMLSave.hpp"
//#include "ExtendedMetaData.hpp"

namespace persistence {


XMLSave::XMLSave () {
	//m_XmlFile = 0;
	//m_DoNamespaces = false;
	//m_DoSchema = false;
	//m_SchemaFullChecking = false;
	//m_DoCreate = false;

	m_outputfile = 0;
	m_XPathExpression = 0;

	// options for DOMLSSerializer's features
	m_OutputEncoding = 0;

	m_SplitCdataSections = true;
	m_DiscardDefaultContent = true;
	m_UseFilter = false;
	m_FormatPrettyPrint = true;
	m_WriteBOM = false;

	//m_ValScheme = XercesDOMParser::Val_Auto;

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
/*
	m_parser = new XercesDOMParser;
	m_parser->setValidationScheme( m_ValScheme );
	m_parser->setDoNamespaces( m_DoNamespaces );
	m_parser->setDoSchema( m_DoSchema );
	m_parser->setHandleMultipleImports( true );
	m_parser->setValidationSchemaFullChecking( m_SchemaFullChecking );
	m_parser->setCreateEntityReferenceNodes( m_DoCreate );

	m_errReporter = new DOMTreeErrorReporter();
	m_parser->setErrorHandler( m_errReporter );
*/
	m_doc = nullptr;
}

XMLSave::~XMLSave () {

	if ( m_doc ) {
		m_doc->release();
	}
	XMLPlatformUtils::Terminate();

}
/*
 bool XMLSave::save ( const std::string& filename, std::shared_ptr<ecore::EObject> model, std::set<std::string> options ) {

 return write(filename, options);
 }
 */
bool XMLSave::write ( const std::string &filename ) {

	m_outputfile = (char*) filename.c_str();

	DOMPrintFilter *myFilter = 0;

	try {
		// get a serializer, an instance of DOMLSSerializer
		XMLCh tempStr[3] = { chLatin_L, chLatin_S, chNull };
		DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation( tempStr );
		DOMLSSerializer *theSerializer = ((DOMImplementationLS*) impl)->createLSSerializer();
		DOMLSOutput *theOutputDesc = ((DOMImplementationLS*) impl)->createLSOutput();

		// set user specified output encoding
		theOutputDesc->setEncoding( m_OutputEncoding );

		// plug in user's own filter
		if ( m_UseFilter ) {
			// even we say to show attribute, but the DOMLSSerializer
			// will not show attribute nodes to the filter as
			// the specs explicitly says that DOMLSSerializer shall
			// NOT show attributes to DOMLSSerializerFilter.
			//
			// so DOMNodeFilter::SHOW_ATTRIBUTE has no effect.
			// same DOMNodeFilter::SHOW_DOCUMENT_TYPE, no effect.
			//
			myFilter = new DOMPrintFilter( DOMNodeFilter::SHOW_ELEMENT | DOMNodeFilter::SHOW_ATTRIBUTE | DOMNodeFilter::SHOW_DOCUMENT_TYPE );
			theSerializer->setFilter( myFilter );
		}

		// plug in user's own error handler
		DOMErrorHandler *myErrorHandler = new DOMPrintErrorHandler();
		DOMConfiguration* serializerConfig = theSerializer->getDomConfig();
		serializerConfig->setParameter( XMLUni::fgDOMErrorHandler, myErrorHandler );

		// set feature if the serializer supports the feature/mode
		if ( serializerConfig->canSetParameter( XMLUni::fgDOMWRTSplitCdataSections, m_SplitCdataSections ) ){
			serializerConfig->setParameter( XMLUni::fgDOMWRTSplitCdataSections, m_SplitCdataSections );
		}
		if ( serializerConfig->canSetParameter( XMLUni::fgDOMWRTDiscardDefaultContent, m_DiscardDefaultContent ) ){
			serializerConfig->setParameter( XMLUni::fgDOMWRTDiscardDefaultContent, m_DiscardDefaultContent );
		}
		if ( serializerConfig->canSetParameter( XMLUni::fgDOMWRTFormatPrettyPrint, m_FormatPrettyPrint ) ){
			serializerConfig->setParameter( XMLUni::fgDOMWRTFormatPrettyPrint, m_FormatPrettyPrint );
		}
		if ( serializerConfig->canSetParameter( XMLUni::fgDOMWRTBOM, m_WriteBOM ) ){
			serializerConfig->setParameter( XMLUni::fgDOMWRTBOM, m_WriteBOM );
		}
		//
		// Plug in a format target to receive the resultant
		// XML stream from the serializer.
		//
		// StdOutFormatTarget prints the resultant XML stream
		// to stdout once it receives any thing from the serializer.
		//
		XMLFormatTarget *myFormTarget;
		if ( m_outputfile ) {
			myFormTarget = new LocalFileFormatTarget( m_outputfile );
		}
		else {
			myFormTarget = new StdOutFormatTarget();
		}
		theOutputDesc->setByteStream( myFormTarget );
		/*
		 // get the DOM representation
		 DOMDocument *doc = parser->getDocument();
		 */
		//
		// do the serialization through DOMLSSerializer::write();
		//
		if ( m_XPathExpression != NULL ) {
			XMLCh* xpathStr = XMLString::transcode( m_XPathExpression );
			DOMElement* root = m_doc->getDocumentElement();
			try {
				DOMXPathNSResolver* resolver = m_doc->createNSResolver( root );
				DOMXPathResult* result = m_doc->evaluate( xpathStr, root, resolver, DOMXPathResult::ORDERED_NODE_SNAPSHOT_TYPE,
				NULL );

				XMLSize_t nLength = result->getSnapshotLength();
				for ( XMLSize_t i = 0; i < nLength; i++ ) {
					result->snapshotItem( i );
					theSerializer->write( result->getNodeValue(), theOutputDesc );
				}

				result->release();
				resolver->release();
			}
			catch ( const DOMXPathException& e ) {
				std::cout << "An error occurred during processing of the XPath expression. Msg is:" << std::endl << StrX( e.getMessage() ) << std::endl;
				//retval = 4;
			}
			catch ( const DOMException& e ) {
				std::cout << "An error occurred during processing of the XPath expression. Msg is:" << std::endl << StrX( e.getMessage() ) << std::endl;
				//retval = 4;
			}
			XMLString::release( &xpathStr );
		}
		else {
			theSerializer->write( m_doc, theOutputDesc );
		}
		theOutputDesc->release();
		theSerializer->release();

		//
		// Filter, formatTarget and error handler
		// are NOT owned by the serializer.
		//
		delete myFormTarget;
		delete myErrorHandler;

		if ( m_UseFilter ) {
			delete myFilter;
		}
	}
	catch ( const OutOfMemoryException& ) {
		std::cerr << "OutOfMemoryException" << std::endl;
		//retval = 5;
	}
	catch ( XMLException& e ) {
		std::cerr << "An error occurred during creation of output transcoder. Msg is:" << std::endl << StrX( e.getMessage() ) << std::endl;
		//retval = 4;
	}
	return true;
}


} /* namespace persistence */
