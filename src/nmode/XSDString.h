#ifndef __NMODE_XSD_STRING_H__
#define __NMODE_XSD_STRING_H__

#include <xercesc/util/XMLString.hpp>

XERCES_CPP_NAMESPACE_USE

// code taken from xerces/c/samples/CreateDOMDocument.cpp

class XSDString
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XSDString(const char* const toTranscode);
    ~XSDString();


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const XMLCh* unicodeForm() const;

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fUnicodeForm
    //      This is the Unicode XMLCh format of the string.
    // -----------------------------------------------------------------------
    XMLCh*   fUnicodeForm;
};

#define X(str) XSDString(str).unicodeForm()



#endif // __XSD_STRING_H__
