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


#include "YarsXSDSaxHandler.h"

#include "Data.h"
#include "ParseElement.h"
#include "ParseAttribute.h"

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

