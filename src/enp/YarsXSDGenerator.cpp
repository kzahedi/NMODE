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


#include "YarsXSDGenerator.h"
#include "YarsXSDNames.h"

#include <cstdlib>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#if defined(XERCES_NEW_IOSTREAMS)
#  include <iostream>
#else
#  include <iostream.h>
#endif

using namespace std;

#include "XSDString.h"
#include "Data.h"

XERCES_CPP_NAMESPACE_USE

YarsXSDGenerator::YarsXSDGenerator()
{
  try
  {
    XMLPlatformUtils::Initialize();
  }
  catch(const XMLException& toCatch)
  {
    char *pMsg = XMLString::transcode(toCatch.getMessage());
    XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Initialization.\n"
      << "  Exception message:"
      << pMsg;
    XMLString::release(&pMsg);
  }

  _impl =  DOMImplementationRegistry::getDOMImplementation(NULL);
  _out  = ((DOMImplementationLS*)_impl)->createLSOutput();
  _out->setEncoding(X("UTF-8"));

  if (_impl != NULL)
  {
    try
    {
      _doc = _impl->createDocument(YARS_XSD_NS, YARS_XSD_SCHEMA, 0);

      _doc->setXmlStandalone(true);
      _root = _doc->getDocumentElement();
      _root->setAttribute(YARS_XSD_ELEMENT_FORM_DEFAULT, YARS_XSD_QUALIFIED);

      XsdSpecification *spec = Data::instance()->xsd();

      for(std::vector<XsdSequence*>::iterator s = spec->s_begin(); s != spec->s_end(); s++)
      {
        __addSequence(*s);
      }
      for(std::vector<XsdEnumeration*>::iterator e = spec->e_begin(); e != spec->e_end(); e++)
      {
        __addEnumeration(*e);
      }
      for(std::vector<XsdChoice*>::iterator c = spec->c_begin(); c != spec->c_end(); c++)
      {
        __addChoice(*c);
      }
      for(std::vector<XsdInterval*>::iterator i = spec->i_begin(); i != spec->i_end(); i++)
      {
        __addInterval(*i);
      }
      for(std::vector<XsdRegularExpression*>::iterator r = spec->r_begin(); r != spec->r_end(); r++)
      {
        __addRegularExpression(*r);
      }

      __addRoot(spec->root());

      delete spec;
    }
    catch (const OutOfMemoryException&)
    {
      XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
    }
    catch (const DOMException& e)
    {
      XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
    }
    catch (...)
    {
      XERCES_STD_QUALIFIER cerr << "An error occurred creating the document" << XERCES_STD_QUALIFIER endl;
    }
  }  // (inpl != NULL)
  else
  {
    XERCES_STD_QUALIFIER cerr << "Requested implementation is not supported" << XERCES_STD_QUALIFIER endl;
  }
}

YarsXSDGenerator::~YarsXSDGenerator()
{
  // ???
}

DOMDocument* YarsXSDGenerator::doc()
{
  return _doc;
}

void YarsXSDGenerator::__addSequence(XsdSequence *s)
{
  // DOMComment *comment     = _doc->createComment(X("comment"));
  DOMElement *parent      = _doc->createElement(YARS_XSD_COMPLEX_TYPE);
  XsdElement *xsdElement  = NULL;
  XsdChoice  *xsdChoice   = NULL;
  DOMElement *element     = NULL;
  DOMElement *choice      = NULL;

  parent->setAttribute(YARS_XSD_NAME, X(s->name().c_str()));

  if(s->n_size() > 0)
  {
    DOMElement *sequence    = _doc->createElement(YARS_XSD_SEQUENCE);
    parent->appendChild(sequence);
    for(std::vector<XsdNode*>::iterator n = s->n_begin(); n != s->n_end(); n++)
    {
      switch((*n)->nodeType())
      {
        case XSD_NODE_TYPE_ELEMENT:
          element = _doc->createElement(YARS_XSD_ELEMENT);
          xsdElement = ((XsdElement*)(*n));
          __createElement(element, xsdElement);
          sequence->appendChild(element);
          break;
        case XSD_NODE_TYPE_CHOICE:
          choice = _doc->createElement(YARS_XSD_CHOICE);
          xsdChoice = (XsdChoice*)(*n);
          __createChoice(choice, xsdChoice);
          sequence->appendChild(choice);
          break;
      }
    }
  }
  if(s->a_size() > 0)
  {
    for(std::vector<XsdAttribute*>::iterator a = s->a_begin(); a != s->a_end(); a++)
    {
      element = _doc->createElement(YARS_XSD_ATTRIBUTE);
      __createAttribute(element, *a);
      parent->appendChild(element);
    }
  }
  _root->appendChild(parent);
}

void YarsXSDGenerator::__createChoice(DOMElement *choice, XsdChoice *c)
{
  if(c->maxOccursGiven())
  {
    choice->setAttribute(YARS_XSD_MAX_OCCURS, X(c->maxOccurs().c_str()));
  }

  if(c->minOccursGiven())
  {
    choice->setAttribute(YARS_XSD_MIN_OCCURS, X(c->minOccurs().c_str()));
  }

  if(c->e_size() > 0)
  {
    for(std::vector<XsdElement*>::iterator i = c->e_begin(); i != c->e_end(); i++)
    {
      DOMElement *element = _doc->createElement(YARS_XSD_ELEMENT);
      __createElement(element, *i);
      choice->appendChild(element);
    }
  }

  if(c->s_size() > 0)
  {
    for(std::vector<XsdSequence*>::iterator s = c->s_begin(); s != c->s_end(); s++)
    {
      DOMElement *sequence = _doc->createElement(YARS_XSD_SEQUENCE);
      __createSequence(sequence, *s);
      choice->appendChild(sequence);
    }
  }

}

void YarsXSDGenerator::__createSequence(DOMElement *sequence, XsdSequence *s)
{
  if(s->e_size() > 0)
  {
    for(std::vector<XsdElement*>::iterator i = s->e_begin(); i != s->e_end(); i++)
    {
      DOMElement *element = _doc->createElement(YARS_XSD_ELEMENT);
      __createElement(element, *i);
      sequence->appendChild(element);
    }
  }
}
void YarsXSDGenerator::__createElement(DOMElement *element, XsdElement *e)
{
  if(e->maxOccursGiven())
  {
    element->setAttribute(YARS_XSD_MAX_OCCURS, X(e->maxOccurs().c_str()));
  }

  if(e->minOccursGiven())
  {
    element->setAttribute(YARS_XSD_MIN_OCCURS, X(e->minOccurs().c_str()));
  }

  element->setAttribute(YARS_XSD_NAME, X(e->name().c_str()));

  if(e->type().size() > 0)
  {
    element->setAttribute(YARS_XSD_TYPE, X(e->type().c_str()));
  }

  if(e->a_size() > 0)
  {
    DOMElement *complexType = _doc->createElement(YARS_XSD_COMPLEX_TYPE);
    for(std::vector<XsdAttribute*>::iterator a = e->a_begin(); a != e->a_end(); a++)
    {
      DOMElement *attr = _doc->createElement(YARS_XSD_ATTRIBUTE);
      __createAttribute(attr, *a);
      complexType->appendChild(attr);
    }
    element->appendChild(complexType);
  }
}

void YarsXSDGenerator::__createAttribute(DOMElement *element, XsdAttribute *a)
{
  element->setAttribute(YARS_XSD_NAME, X(a->name().c_str()));
  element->setAttribute(YARS_XSD_TYPE, X(a->type().c_str()));
  if(a->required())
  {
    element->setAttribute(YARS_XSD_USE, YARS_XSD_REQUIRED);
  }
  else
  {
    element->setAttribute(YARS_XSD_USE, YARS_XSD_OPTIONAL);
  }
}

void YarsXSDGenerator::__addEnumeration(XsdEnumeration *e)
{
  DOMElement *parent      = _doc->createElement(YARS_XSD_SIMPLE_TYPE);
  DOMElement *restriction = _doc->createElement(YARS_XSD_RESTRICTION);
  restriction->setAttribute(YARS_XSD_BASE, X(e->type().c_str()));

  parent->setAttribute(YARS_XSD_NAME, X(e->name().c_str()));
  parent->appendChild(restriction);
  for(std::vector<string>::iterator v = e->v_begin(); v != e->v_end(); v++)
  {
    DOMElement *element = _doc->createElement(YARS_XSD_ENUMERATION);
    element->setAttribute(YARS_XSD_VALUE, X(v->c_str()));
    restriction->appendChild(element);
  }
  _root->appendChild(parent);
}

void YarsXSDGenerator::__addChoice(XsdChoice *c)
{
  DOMElement *parent = _doc->createElement(YARS_XSD_COMPLEX_TYPE);
  DOMElement *choice = _doc->createElement(YARS_XSD_CHOICE);
  if(c->minOccursGiven())
  {
    choice->setAttribute(YARS_XSD_MIN_OCCURS, X(c->minOccurs().c_str()));
  }
  if(c->maxOccursGiven())
  {
    choice->setAttribute(YARS_XSD_MAX_OCCURS, X(c->maxOccurs().c_str()));
  }
  parent->setAttribute(YARS_XSD_NAME, X(c->name().c_str()));

  for(std::vector<XsdElement*>::iterator e = c->e_begin(); e != c->e_end(); e++)
  {
    DOMElement *element = _doc->createElement(YARS_XSD_ELEMENT);
    __createElement(element, *e);
    choice->appendChild(element);
  }

  for(std::vector<XsdSequence*>::iterator s = c->s_begin(); s != c->s_end(); s++)
  {
    DOMElement *sequence = _doc->createElement(YARS_XSD_SEQUENCE);
    __createSequence(sequence, *s);
    choice->appendChild(sequence);
  }

  parent->appendChild(choice);

  if(c->a_size() > 0)
  {
    for(std::vector<XsdAttribute*>::iterator a = c->a_begin(); a != c->a_end(); a++)
    {
      DOMElement *element = _doc->createElement(YARS_XSD_ATTRIBUTE);
      __createAttribute(element, *a);
      parent->appendChild(element);
    }
  }
  _root->appendChild(parent);
}

void YarsXSDGenerator::__addInterval(XsdInterval *i)
{
  DOMElement *parent      = _doc->createElement(YARS_XSD_SIMPLE_TYPE);
  DOMElement *restriction = _doc->createElement(YARS_XSD_RESTRICTION);
  restriction->setAttribute(YARS_XSD_BASE, X(i->type().c_str()));
  parent->setAttribute(YARS_XSD_NAME, X(i->name().c_str()));
  parent->appendChild(restriction);

  DOMElement *min = _doc->createElement(YARS_XSD_MIN_INCLUSIVE);
  min->setAttribute(YARS_XSD_VALUE, X(i->minimum().c_str()));
  restriction->appendChild(min);

  DOMElement *max = _doc->createElement(YARS_XSD_MAX_INCLUSIVE);
  max->setAttribute(YARS_XSD_VALUE, X(i->maximum().c_str()));
  restriction->appendChild(max);

  _root->appendChild(parent);
}

void YarsXSDGenerator::__addRegularExpression(XsdRegularExpression *r)
{
  DOMElement *parent      = _doc->createElement(YARS_XSD_SIMPLE_TYPE);
  DOMElement *restriction = _doc->createElement(YARS_XSD_RESTRICTION);
  restriction->setAttribute(YARS_XSD_BASE, X(r->type().c_str()));
  parent->setAttribute(YARS_XSD_NAME, X(r->name().c_str()));
  parent->appendChild(restriction);

  DOMElement *pattern = _doc->createElement(YARS_XSD_PATTERN);
  pattern->setAttribute(YARS_XSD_VALUE, X(r->regExp().c_str()));
  restriction->appendChild(pattern);

  _root->appendChild(parent);
}

void YarsXSDGenerator::__addRoot(XsdSequence *s)
{
  DOMElement *parent      = _doc->createElement(YARS_XSD_ELEMENT);
  DOMElement *complexType = _doc->createElement(YARS_XSD_COMPLEX_TYPE);

  parent->setAttribute(YARS_XSD_NAME, X(s->name().c_str()));
  parent->appendChild(complexType);

  if(s->e_size() > 0)
  {
    DOMElement *sequence    = _doc->createElement(YARS_XSD_SEQUENCE);
    parent->appendChild(sequence);
    for(std::vector<XsdElement*>::iterator e = s->e_begin(); e != s->e_end(); e++)
    {
      DOMElement *element = _doc->createElement(YARS_XSD_ELEMENT);
      __createElement(element, *e);
      sequence->appendChild(element);
    }
    complexType->appendChild(sequence);
  }
  if(s->a_size() > 0)
  {
    for(std::vector<XsdAttribute*>::iterator a = s->a_begin(); a != s->a_end(); a++)
    {
      DOMElement *element = _doc->createElement(YARS_XSD_ATTRIBUTE);
      __createAttribute(element, *a);
      complexType->appendChild(element);
    }

  }
  _root->appendChild(parent);
}

DOMLSOutput* YarsXSDGenerator::out()
{
  return _out;
}
