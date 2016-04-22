#include <nmode/YarsXSDSaxHandler.h>

#include <nmode/Data.h>
#include <nmode/ParseElement.h>
#include <nmode/ParseAttribute.h>

#include <iostream>
#include <sstream>

using namespace std;


YarsXSDSaxHandler::YarsXSDSaxHandler()
{
}


void YarsXSDSaxHandler::startElement(
    const   XMLCh* const    uri,
    const   XMLCh* const    localname,
    const   XMLCh* const    qname,
    const   Attributes&     attrs)
{
  char* message       = XMLString::transcode(localname);
  char* m_uri         = XMLString::transcode(uri);
  char* m_localname   = XMLString::transcode(localname);
  char* m_qname       = XMLString::transcode(qname);
  ParseElement *element = new ParseElement(YARS_DATA_PARSE_ELEMENT_TYPE_OPENING);
  element->setName(message);

  if(attrs.getLength() > 0)
  {
    for (XMLSize_t i = 0; i < attrs.getLength(); i++)
    {
      ParseAttribute *a = new ParseAttribute();
      string a_qname = XMLString::transcode(attrs.getQName(i));
      string a_uri   = XMLString::transcode(attrs.getURI(i));
      string a_local = XMLString::transcode(attrs.getLocalName(i));
      string a_type  = XMLString::transcode(attrs.getType(i));
      string a_value = XMLString::transcode(attrs.getValue(i));
      a->setName(a_qname);
      a->setValue(a_value);
      element->add(a);
    }
  }
  XMLString::release(&message);
  XMLString::release(&m_uri);
  XMLString::release(&m_localname);
  XMLString::release(&m_qname);
  _spec->add(element);
}

void YarsXSDSaxHandler::endElement(
    const XMLCh *const,
    const XMLCh *const localname,
    const XMLCh *const)
{
  char* message = XMLString::transcode(localname);
  ParseElement *element = new ParseElement(YARS_DATA_PARSE_ELEMENT_TYPE_CLOSING);
  element->setName(message);
  _spec->add(element);
  delete element;
  XMLString::release(&message);
}

void YarsXSDSaxHandler::startDocument()
{
  _spec = Data::instance()->specification();
}

void YarsXSDSaxHandler::endDocument()
{
  // noting
}

void YarsXSDSaxHandler::fatalError(const SAXParseException &spe)
{
  stringstream oss;
  char* message = XMLString::transcode(spe.getMessage());
  oss << "Fatal Error: " << message
    << " at line: " << spe.getLineNumber();
  XMLString::release(&message);
  _fatals.push_back(oss.str());
}

void YarsXSDSaxHandler::error(const SAXParseException &spe)
{
  stringstream oss;
  char* message = XMLString::transcode(spe.getMessage());
  oss << "Error: " << message
    << " at line: " << spe.getLineNumber();
  XMLString::release(&message);
  _errors.push_back(oss.str());
}

void YarsXSDSaxHandler::warning(const SAXParseException &spe)
{
  stringstream oss;
  char* message = XMLString::transcode(spe.getMessage());
  oss << "Warning: " << message
    << " at line: " << spe.getLineNumber();
  XMLString::release(&message);
  _warnings.push_back(oss.str());
}

std::vector<string> YarsXSDSaxHandler::errors()
{
  return _errors;
}

std::vector<string> YarsXSDSaxHandler::warnings()
{
  return _warnings;
}

std::vector<string> YarsXSDSaxHandler::fatals()
{
  return _fatals;
}

