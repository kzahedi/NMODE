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


#ifndef __YARS_XSD_GENERATOR_H__
#define __YARS_XSD_GENERATOR_H__

#include <ostream>
#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include "XSDString.h"

#include "XsdSequence.h"
#include "XsdEnumeration.h"
#include "XsdElement.h"
#include "XsdChoice.h"
#include "XsdRegularExpression.h"
#include "XsdInterval.h"

XERCES_CPP_NAMESPACE_USE

/**
 * @brief This class generates the XML Schema Grammar from the XsdSpecification
 * @sa XsdSpecification
 */
class YarsXSDGenerator
/**
 * \brief This class implements the XSD-Grammar.
 */
{
  public:
    /**
     * @brief Constructor.
     */
    YarsXSDGenerator();

    /**
     * @brief Destructor.
     */
    ~YarsXSDGenerator();

    /**
     * @brief Output operator.
     *
     * @param str
     * @param g
     *
     * @return str
     */
    friend std::ostream& operator<<(std::ostream& str, YarsXSDGenerator& g)
    {
      DOMImplementation *implementation = DOMImplementationRegistry::getDOMImplementation(X("LS"));

      // Create a DOMLSSerializer which is used to serialize a DOM tree into an XML document.
      DOMLSSerializer *serializer = ((DOMImplementationLS*)implementation)->createLSSerializer();

      // Make the output more human readable by inserting line feeds.
      if (serializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
        serializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

      // The end-of-line sequence of characters to be used in the XML being written out.
      //serializer->setNewLine(XMLString::transcode("\r\n"));
      serializer->setNewLine(XMLString::transcode("\n"));

      // Write the serialized output to the destination.
      //XMLCh *string = serializer->writeToString(g.doc());

      MemBufFormatTarget memTarget;
      g.out()->setByteStream(&memTarget);
#ifndef _MSC_VER
      serializer->write(g.doc(), g.out());
#else // _MSC_VER
      std::cout << "Exporting XSD currently not supported on Windows" << std::endl;
#endif // _MSC_VER

      // Cleanup.
      serializer->release();

      str << (char*)memTarget.getRawBuffer();
      return str;
    }

    /**
     * @brief Returns the pointer to the XML Schema Grammar.
     *
     * @return
     */
    xercesc_3_1::DOMDocument* doc();

    /**
     * @brief Returns the pointer to the DOMLSOutput of the XML Schema Grammar.
     *
     * @return
     */
    DOMLSOutput* out();

  private:
    void __addSequence(XsdSequence *s);
    void __addEnumeration(XsdEnumeration *e);
    void __addChoice(XsdChoice* choice);
    void __addInterval(XsdInterval *interval);
    void __addRegularExpression(XsdRegularExpression *rexExp);
    void __createElement(DOMElement *element, XsdElement *e);
    void __createAttribute(DOMElement *element, XsdAttribute *a);
    void __createChoice(DOMElement *choice, XsdChoice *c);
    void __addRoot(XsdSequence *s);
    void __createSequence(DOMElement *sequence, XsdSequence *s);

    xercesc_3_1::DOMDocument *_doc;
    DOMElement  *_root;

    DOMImplementation *_impl;
    DOMLSOutput *_out;
};

#endif // __YARS_XSD_GENERATOR_H__
