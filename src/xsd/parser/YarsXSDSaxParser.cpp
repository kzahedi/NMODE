/*************************************************************************
 *                                                                       *
 * This file is part of Yet Another Robot Simulator (YARS).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/YARS                                  *
 *                                                                       *
 * For a list of contributors see the file AUTHORS.                      *
 *                                                                       *
 * YARS is free software; you can redistribute it and/or modify it under *
 * the terms of the GNU General Public License as published by the Free  *
 * Software Foundation; either version 2 of the License, or (at your     *
 * option) any later version.                                            *
 *                                                                       *
 * YARS is distributed in the hope that it will be useful, but WITHOUT   *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
 * FITNESS FOR A PARTICULAR PURPOSE.                                     *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with YARS in the file COPYING; if not, write to the Free        *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor,               *
 * Boston, MA 02110-1301, USA                                            *
 *                                                                       *
 *************************************************************************/


#include "YarsXSDSaxParser.h"
#include "YarsXSDSaxHandler.h"

#include "xsd/generator/YarsXSDGenerator.h"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/framework/StdInInputSource.hpp>


#include <iostream>
#include <sstream>

using namespace std;
using namespace xercesc;

bool YarsXSDSaxParser::read(string filename)
{
  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    cout << "Error during initialization! :\n";
    cout << "Exception message is: \n"
      << message << "\n";
    XMLString::release(&message);
    return false;
  }

  YarsXSDGenerator *generator = new YarsXSDGenerator();

  stringstream oss;
  oss << *generator << endl;
  string xsd = oss.str();
  cout << xsd << endl;

  delete generator;

  YarsXSDSaxHandler* handler = new YarsXSDSaxHandler();
  SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();

  parser->setFeature(XMLUni::fgSAX2CoreValidation,          true);
  parser->setFeature(XMLUni::fgXercesDynamic,               false);
  parser->setFeature(XMLUni::fgXercesLoadSchema,            false);
  parser->setFeature(XMLUni::fgSAX2CoreNameSpaces,          true);
  parser->setFeature(XMLUni::fgXercesSchema,                true);
  parser->setFeature(XMLUni::fgXercesHandleMultipleImports, true);
  parser->setFeature(XMLUni::fgXercesSchemaFullChecking,    true);
  parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes,   false);

  const XMLByte*bytes=reinterpret_cast<const XMLByte*>(xsd.c_str());
  MemBufInputSource mis (bytes, xsd.size (), "/schema.xsd");

  void* id=(void*)("file:///schema.xsd");
  parser->setProperty (
      XMLUni::fgXercesSchemaExternalNoNameSpaceSchemaLocation,
      id);

  parser->loadGrammar(mis, Grammar::SchemaGrammarType, true);
  parser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse, true);

  parser->setContentHandler(handler);
  parser->setErrorHandler(handler);

  try {
    if(filename == "-")
    {
      StdInInputSource src;
      parser->parse(src);
    }
    else
    {
      parser->parse(filename.c_str());
    }
  }
  catch (const XMLException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    cout << "Exception message is: \n"
      << message << "\n";
    XMLString::release(&message);
    return false;
  }
  catch (const SAXParseException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    cout << "Exception message is: \n"
      << message << "\n";
    XMLString::release(&message);
    return false;
  }
  catch (...) {
    cout << "Unexpected Exception \n" ;
    return false;
  }
  int errorCount = parser->getErrorCount();

  _errors   = handler->errors();
  _fatals   = handler->fatals();
  _warnings = handler->warnings();

  delete parser;
  delete handler;

  if(errorCount > 0)
  {
    //cout << "Found " << errorCount << " errors while parsing." << endl;
  }

  if(_fatals.size() > 0 || (_errors.size() > 0))
  {
    return false;
  }
  return true;
}

bool YarsXSDSaxParser::parse(string xml)
{
  cout << "parse(" << xml << ")" << endl;
  try
  {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch)
  {
    char* message = XMLString::transcode(toCatch.getMessage());
    cout << "Error during initialization! :\n";
    cout << "Exception message is: \n"
      << message << "\n";
    XMLString::release(&message);
    return false;
  }

  YarsXSDGenerator *generator = new YarsXSDGenerator();

  stringstream oss;
  oss << *generator << endl;
  string xsd = oss.str();

  delete generator;

  YarsXSDSaxHandler* handler = new YarsXSDSaxHandler();
  SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();

  parser->setFeature(XMLUni::fgSAX2CoreValidation,          true);
  parser->setFeature(XMLUni::fgXercesDynamic,               false);
  parser->setFeature(XMLUni::fgSAX2CoreNameSpaces,          true);
  parser->setFeature(XMLUni::fgXercesSchema,                true);
  parser->setFeature(XMLUni::fgXercesHandleMultipleImports, true);
  parser->setFeature(XMLUni::fgXercesSchemaFullChecking,    false);
  parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes,   false);

  const XMLByte *bytes=reinterpret_cast<const XMLByte*>(xsd.c_str());
  MemBufInputSource mis(bytes, xsd.size (), "/schema.xsd");


  cout << "parse(" << xml << ")" << endl;
  const XMLByte *xml_bytes=reinterpret_cast<const XMLByte*>(xml.c_str());
  MemBufInputSource xmlbuf(xml_bytes, xml.size(), "xml.xml", false);

  parser->loadGrammar(mis, Grammar::SchemaGrammarType, true);
  parser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse, true);

  void *id=(void*)("file:///schema.xsd");
  parser->setProperty (
      XMLUni::fgXercesSchemaExternalNoNameSpaceSchemaLocation,
      id);

  parser->setContentHandler(handler);
  parser->setErrorHandler(handler);

  try {
    parser->parse(xmlbuf);
  }
  catch (const XMLException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    cout << "Exception message is: \n"
      << message << "\n";
    XMLString::release(&message);
    return false;
  }
  catch (const SAXParseException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    cout << "Exception message is: \n"
      << message << "\n";
    XMLString::release(&message);
    return false;
  }
  catch (...) {
    cout << "Unexpected Exception \n" ;
    return false;
  }
  int errorCount = parser->getErrorCount();

  _errors   = handler->errors();
  _fatals   = handler->fatals();
  _warnings = handler->warnings();

  delete parser;
  delete handler;

  if(errorCount > 0)
  {
    // TODO: throw YarsException
    //cout << "Found " << errorCount << " errors while parsing." << endl;
  }

  if(_fatals.size() > 0 || _errors.size() > 0)
  {
    return false;
  }
  return true;
}

std::vector<string>::iterator YarsXSDSaxParser::e_begin()
{
  return _errors.begin();
}

std::vector<string>::iterator YarsXSDSaxParser::e_end()
{
  return _errors.end();
}

int YarsXSDSaxParser::e_size()
{
  return (int)_errors.size();
}

std::vector<string>::iterator YarsXSDSaxParser::f_begin()
{
  return _fatals.begin();
}

std::vector<string>::iterator YarsXSDSaxParser::f_end()
{
  return _fatals.end();
}

int YarsXSDSaxParser::f_size()
{
  return (int)_fatals.size();
}

std::vector<string>::iterator YarsXSDSaxParser::w_begin()
{
  return _warnings.begin();
}

std::vector<string>::iterator YarsXSDSaxParser::w_end()
{
  return _warnings.end();
}

int YarsXSDSaxParser::w_size()
{
  return (int)_warnings.size();
}

int YarsXSDSaxParser::errors()
{
  return _fatals.size() + _errors.size();
}
