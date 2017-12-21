/*
 * myTestXerces.cpp
 *
 *  Created on: 23.06.2017
 *      Author: Alexander
 */

#include "MyTestXerces.hpp"

namespace testXerces {

MyTestXerces::MyTestXerces () {

	m_XmlFile = 0;
	//m_DoNamespaces = false;
	m_DoNamespaces = false;
	m_DoSchema = false;
	m_SchemaFullChecking = false;
	m_DoCreate = false;

	m_outputfile = 0;
	m_XPathExpression = 0;

	// options for DOMLSSerializer's features
	m_OutputEncoding = 0;

	m_SplitCdataSections = true;
	m_DiscardDefaultContent = true;
	m_UseFilter = false;
	m_FormatPrettyPrint = true;
	m_WriteBOM = false;

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

	m_doc = nullptr;

}

MyTestXerces::~MyTestXerces () {

	if ( m_doc ) {
		m_doc->release();
	}
	XMLPlatformUtils::Terminate();

}

bool MyTestXerces::load ( const std::string& filename ) {

	//XERCES_CPP_NAMESPACE_USE
	using namespace xercesc_3_1;

	//
	//  Parse the XML file, catching any XML exceptions that might propogate
	//  out of it.
	//
	m_XmlFile = (char*) filename.c_str();

	bool errorsOccured = false;
	try {
		m_parser->parse( m_XmlFile );
	}
	catch ( const OutOfMemoryException& ) {
		std::cout << "OutOfMemoryException" << std::endl;
		errorsOccured = true;
	}
	catch ( const XMLException& e ) {
		std::cout << "An error occurred during parsing\n   Message: " << StrX( e.getMessage() ) << std::endl;
		errorsOccured = true;
	}

	catch ( const DOMException& e ) {
		const unsigned int maxChars = 2047;
		XMLCh errText[maxChars + 1];

		std::cout << "\nDOM Error during parsing: '" << m_XmlFile << "'\n" << "DOMException code is:  " << e.code << std::endl;

		if ( DOMImplementation::loadDOMExceptionMsg( e.code, errText, maxChars ) )
			std::cout << "Message is: " << StrX( errText ) << std::endl;

		errorsOccured = true;
	}

	catch ( ... ) {
		std::cout << "An error occurred during parsing\n " << std::endl;
		errorsOccured = true;
	}

	m_doc = m_parser->getDocument();

	return errorsOccured;
}

void MyTestXerces::save ( const std::string& filename ) {

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
		if ( serializerConfig->canSetParameter( XMLUni::fgDOMWRTSplitCdataSections, m_SplitCdataSections ) )
			serializerConfig->setParameter( XMLUni::fgDOMWRTSplitCdataSections, m_SplitCdataSections );

		if ( serializerConfig->canSetParameter( XMLUni::fgDOMWRTDiscardDefaultContent, m_DiscardDefaultContent ) )
			serializerConfig->setParameter( XMLUni::fgDOMWRTDiscardDefaultContent, m_DiscardDefaultContent );

		if ( serializerConfig->canSetParameter( XMLUni::fgDOMWRTFormatPrettyPrint, m_FormatPrettyPrint ) )
			serializerConfig->setParameter( XMLUni::fgDOMWRTFormatPrettyPrint, m_FormatPrettyPrint );

		if ( serializerConfig->canSetParameter( XMLUni::fgDOMWRTBOM, m_WriteBOM ) )
			serializerConfig->setParameter( XMLUni::fgDOMWRTBOM, m_WriteBOM );

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
		else{
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

		if ( m_UseFilter )
			delete myFilter;

	}
	catch ( const OutOfMemoryException& ) {
		std::cerr << "OutOfMemoryException" << std::endl;
		//retval = 5;
	}
	catch ( XMLException& e ) {
		std::cerr << "An error occurred during creation of output transcoder. Msg is:" << std::endl << StrX( e.getMessage() ) << std::endl;
		//retval = 4;
	}

}

bool MyTestXerces::getSawErrors () {
	return m_errReporter->getSawErrors();
}

void MyTestXerces::createTestDOMDocument () {

	DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation( X( "Core" ) );

	if ( impl != NULL ) {
		try {
			std::string const& ns_uri = "http://www.eclipse.org/emf/2002/Ecore";

			//DOMDocument* doc = impl->createDocument(
			m_doc = impl->createDocument(
			//(ns_uri.empty()) ? X( "NULL" ) : W( ns_uri ), // root element namespace URI.
			//0 , // root element namespace URI.
			X( "http://www.eclipse.org/emf/2002/Ecore" ) , // root element namespace URI.
			X( "ecore:EPackage" ),         // root element name
			0 );                   // document type object (DTD).




			DOMElement* rootElem = m_doc->getDocumentElement();

			// common attributes
			// xmlns:ecore="http://www.eclipse.org/emf/2002/Ecore"
			//rootElem->setAttribute( X( "xmlns:ecore" ), X( "http://www.eclipse.org/emf/2002/Ecore" ) );
			// xmlns:xmi="http://www.omg.org/XMI"
			rootElem->setAttribute( X( "xmlns:xmi" ), X( "http://www.omg.org/XMI" ) );
			// xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
			rootElem->setAttribute( X( "xmlns:xsi" ), X( "http://www.w3.org/2001/XMLSchema-instance" ) );
			// xmi:version="2.0"
			rootElem->setAttribute( X( "xmi:version" ), X( "2.0" ) );


			std::cout << m_doc->getPrefix() << std::endl;

			std::cout << m_doc->getNamespaceURI() << std::endl;
			std::cout << m_doc->lookupNamespaceURI(X("ecore")) << std::endl;
			std::cout << m_doc->lookupNamespaceURI(X("xml")) << std::endl;

			//m_doc->setPrefix( X( "xml" ) );

			DOMElement* prodElem1 = m_doc->createElement( X( "eClassifiers" ) );
			{
				rootElem->appendChild( prodElem1 );
				prodElem1->setAttribute( X( "xsi:type" ), X( "ecore:EClass" ) );
				prodElem1->setAttribute( X( "name" ), X( "EAttribute" ) );
				prodElem1->setAttribute( X( "eSuperTypes" ), X( "#//EStructuralFeature" ) );

				DOMElement* prodElem1_1 = m_doc->createElement( X( "eStructuralFeatures" ) );
				{
					prodElem1->appendChild( prodElem1_1 );
					prodElem1_1->setAttribute( X( "xsi:type" ), X( "ecore:EAttribute" ) );
					prodElem1_1->setAttribute( X( "name" ), X( "iD" ) );
					prodElem1_1->setAttribute( X( "eSuperTypes" ), X( "#//EBoolean" ) );
				}
			}

			DOMElement* prodElem2 = m_doc->createElement( X( "eClassifiers" ) );
			{
				rootElem->appendChild( prodElem2 );
				prodElem2->setAttribute( X( "xsi:type" ), X( "ecore:EClass" ) );
				prodElem2->setAttribute( X( "name" ), X( "EAttribute" ) );
				prodElem2->setAttribute( X( "eSuperTypes" ), X( "#//EStructuralFeature" ) );

				DOMElement* prodElem2_1 = m_doc->createElement( X( "eStructuralFeatures" ) );
				{
					prodElem2->appendChild( prodElem2_1 );
					prodElem2_1->setAttribute( X( "xsi:type" ), X( "ecore:EAttribute" ) );
					prodElem2_1->setAttribute( X( "name" ), X( "iD" ) );
					prodElem2_1->setAttribute( X( "eSuperTypes" ), X( "#//EBoolean" ) );
				}
			}

			/*
			 DOMText* prodDataVal = m_doc->createTextNode( X( "Xerces-C" ) );
			 prodElem->appendChild( prodDataVal );

			 DOMElement* catElem = m_doc->createElement( X( "category" ) );
			 rootElem->appendChild( catElem );

			 catElem->setAttribute( X( "idea" ), X( "great" ) );

			 DOMText* catDataVal = m_doc->createTextNode( X( "XML Parsing Tools" ) );
			 catElem->appendChild( catDataVal );

			 DOMElement* devByElem = m_doc->createElement( X( "developedBy" ) );
			 rootElem->appendChild( devByElem );

			 DOMText* devByDataVal = m_doc->createTextNode( X( "Apache Software Foundation" ) );
			 devByElem->appendChild( devByDataVal );
			 */
			//
			// Now count the number of elements in the above DOM tree.
			//
			const XMLSize_t elementCount = m_doc->getElementsByTagName( X( "*" ) )->getLength();
			std::cout << "The tree just created contains: " << elementCount << " elements." << std::endl;

			//m_doc = doc;

			//doc->release();
		}
		catch ( const OutOfMemoryException& ) {
			std::cerr << "OutOfMemoryException" << std::endl;
			//errorCode = 5;
		}
		catch ( const DOMException& e ) {
			std::cout << "DOMException code is:  " << e.code << std::endl << StrX( e.getMessage() ) << std::endl;
			//errorCode = 2;
		}
		catch ( ... ) {
			std::cout << "An error occurred creating the document" << std::endl;
			//errorCode = 3;
		}
	}  // (inpl != NULL)
	else {
		std::cout << "Requested implementation is not supported" << std::endl;
		//errorCode = 4;
	}
//return nullptr;
}

}
/* namespace */

