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


#ifndef __YARS_XSD_SAX_HANDLER_H__
#define __YARS_XSD_SAX_HANDLER_H__

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include <string>
#include <vector>

#include "ENP.h"

XERCES_CPP_NAMESPACE_USE

/**
 * @brief This is the SAX2 parser of YARS. It should not be changed. This parser
 * creates entities of type DataParseElement, which also contain
 * DataParseAttribute. 
 *
 *
 * @sa DataParseElement
 * @sa DataParseAttribute
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
    ENP *_spec;

    std::vector<std::string> _errors;
    std::vector<std::string> _warnings;
    std::vector<std::string> _fatals;
};

#endif // __YARS_XSD_SAX_HANDLER_H__
