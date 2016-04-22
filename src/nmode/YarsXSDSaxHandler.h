#ifndef __NMODE_YARS_XSD_SAX_HANDLER_H__
#define __NMODE_YARS_XSD_SAX_HANDLER_H__

#include <nmode/NMODE.h>

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include <string>
#include <vector>


XERCES_CPP_NAMESPACE_USE

/**
 * @brief This is the SAX2 parser of YARS. It should not be changed. This parser
 * creates entities of type ParseElement, which also contain
 * ParseAttribute. 
 *
 *
 * @sa ParseElement
 * @sa ParseAttribute
 */
class YarsXSDSaxHandler : public DefaultHandler
{
  public:
    YarsXSDSaxHandler();

    void startElement(
        const   XMLCh* const    uri,
        const   XMLCh* const    localname,
        const   XMLCh* const    qname,
        const   Attributes&     attrs);

    void endElement(
        const XMLCh *const uri,
        const XMLCh *const localname,
        const XMLCh *const qname);

    void startDocument();
    void endDocument();

    void error(const SAXParseException& e);
    void fatalError(const SAXParseException& e);
    void warning(const SAXParseException& e);

    /**
     * @brief Returns a list of strings with error messages.
     *
     * @return list of strings
     */
    std::vector<std::string> errors();

    /**
     * @brief Returns a list of strings with warnings.
     *
     * @return list of strings
     */
    std::vector<std::string> warnings();

    /**
     * @brief Returns a list of strings with fatal messages.
     *
     * @return list of strings
     */
    std::vector<std::string> fatals();

  private:
    NMODE *_spec;

    std::vector<std::string> _errors;
    std::vector<std::string> _warnings;
    std::vector<std::string> _fatals;
};

#endif // __YARS_XSD_SAX_HANDLER_H__
