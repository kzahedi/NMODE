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


#include "XsdGraph.h"

#include <iostream>

using namespace std;

// #include "configuration/data/Data.h"
#include "xsd/specification/XsdSpecification.h"

#include "base/macros.h"

#include "XsdSequenceGraphNode.h"
#include "XsdChoiceGraphNode.h"
#include "XsdEnumerationGraphNode.h"
#include "XsdRegularExpressionGraphNode.h"
#include "XsdIntervalGraphNode.h"
#include "XsdElementGraphNode.h"


#define DO(a) if((a)->name() == destination->name()) __addChild(destination, a)

XsdGraph::XsdGraph()
{
  // _spec                      = Data::instance()->xsd();

  // FOREACHF(XsdSequence*,          s, _spec, ->s_begin(), ->s_end()) __add(*s);
  // FOREACHF(XsdChoice*,            c, _spec, ->c_begin(), ->c_end()) __add(*c);
  // FOREACHF(XsdEnumeration*,       e, _spec, ->e_begin(), ->e_end()) __add(*e);
  // FOREACHF(XsdInterval*,          i, _spec, ->i_begin(), ->i_end()) __add(*i);
  // FOREACHF(XsdRegularExpression*, r, _spec, ->r_begin(), ->r_end()) __add(*r);

  __createGraph();
}

XsdGraph::~XsdGraph()
{
  for(std::vector<XsdGraphNode*>::iterator n = _nodes.begin(); n != _nodes.end(); n++) delete *n;
}


void XsdGraph::__add(XsdSequence *seq)
{
  if(seq->name() == _spec->root()->name()) return;
  XsdSequenceGraphNode *s = new XsdSequenceGraphNode(seq);
  _nodes.push_back(s);
}

void XsdGraph::__add(XsdChoice *choice)
{
  XsdChoiceGraphNode *c = new XsdChoiceGraphNode(choice);
  _nodes.push_back(c);
}

void XsdGraph::__add(XsdEnumeration *enu)
{
  XsdEnumerationGraphNode *e = new XsdEnumerationGraphNode(enu);
  _nodes.push_back(e);
}

void XsdGraph::__add(XsdInterval *interval)
{
  XsdIntervalGraphNode *i = new XsdIntervalGraphNode(interval);
  _nodes.push_back(i);
}

void XsdGraph::__add(XsdRegularExpression *regexp)
{
  XsdRegularExpressionGraphNode *r = new XsdRegularExpressionGraphNode(regexp);
  _nodes.push_back(r);
}

std::vector<XsdGraphNodeInstance*>::iterator XsdGraph::i_begin()
{
  return _instances.begin();
}

std::vector<XsdGraphNodeInstance*>::iterator XsdGraph::i_end()
{
  return _instances.end();
}

XsdGraphNodeInstance* XsdGraph::get(string parent, string name)
{
  FORC(vector<XsdGraphNodeInstance*>, i, _instances)
  {
    if((*i)->name() == parent)
    {
      FORP(vector<XsdGraphNodeInstance*>, c, (*i))
      {
        if((*c)->name() == name)
        {
          return (*c);
        }
      }
    }
  }
  return _root;
}

void XsdGraph::__createGraph()
{
  XsdSequence          *seq  = _spec->root();
  XsdSequenceGraphNode *root = new XsdSequenceGraphNode(seq);
  _root                      = new XsdGraphNodeInstance(root->name(), root->name(), root);
  _instances.push_back(_root);

  int index = 0;
  FORF(vector<XsdAttribute*>, a, seq, ->a_begin(), ->a_end()) __add(_root, *a);
  FORF(vector<XsdElement*>,   e, seq, ->e_begin(), ->e_end()) __add(_root, *e);
  FORP(vector<XsdGraphNodeInstance*>, n, _root) (*n)->setPort(index++);
}

void XsdGraph::__add(XsdGraphNodeInstance *parent, XsdElement *element)
{
  XsdGraphNode *node             = __findNode(element->type());
  XsdGraphNodeInstance *instance = NULL;

  int index = 0;
  if(node != NULL)
  {
    instance = new XsdGraphNodeInstance(element->name(), element->type(), node);
    __add(instance, node->spec());
  }
  else
  {
    XsdElementGraphNode *node = new XsdElementGraphNode(element);
    instance = new XsdGraphNodeInstance(element->name(), element->name(), node);
    FORF(vector<XsdAttribute*>, a, element, ->a_begin(), ->a_end())
      __add(instance, *a);
    FORP(vector<XsdGraphNodeInstance*>, n, instance)
      (*n)->setPort(index++);
  }

  _instances.push_back(instance);
  parent->push_back(instance);


}

void XsdGraph::__add(XsdGraphNodeInstance *parent, XsdSequence *seq)
{
  FORF(vector<XsdAttribute*>,         a, seq, ->a_begin(), ->a_end())
    __add(parent, *a);
  FORF(vector<XsdElement*>,           e, seq, ->e_begin(), ->e_end())
    __add(parent, *e);
  FORF(vector<XsdChoice*>,            c, seq, ->c_begin(), ->c_end())
    __add(parent, *c);
  FORF(vector<XsdRegularExpression*>, r, seq, ->r_begin(), ->r_end())
    __add(parent, *r);
  FORF(vector<XsdInterval*>,          i, seq, ->i_begin(), ->i_end())
    __add(parent, *i);

  int index = 0;
  FORP(vector<XsdGraphNodeInstance*>, n, parent) (*n)->setPort(index++);
}

void XsdGraph::__add(XsdGraphNodeInstance *parent, XsdChoice *choice)
{
  FORF(vector<XsdAttribute*>, a, choice, ->a_begin(), ->a_end())
    __add(parent, *a);
  FORF(vector<XsdElement*>,   e, choice, ->e_begin(), ->e_end())
    __add(parent, *e);
  int index = 0;
  FORP(vector<XsdGraphNodeInstance*>, n, parent)
  {
    (*n)->setPort(index++);
  }

  std::vector<XsdGraphNodeInstance*> v;
  FORF(vector<XsdSequence*>,  s, choice, ->s_begin(), ->s_end())
  {
    XsdGraphNodeInstance *i = new XsdGraphNodeInstance("", "", NULL);
    __add(i, *s);
    v.push_back(i);
  }

  FORC(vector<XsdGraphNodeInstance*>, p, v)
  {
    FORP(vector<XsdGraphNodeInstance*>, i, (*p))
    {
      parent->push_back(*i);
      (*i)->setPort(index);
    }
    index++;
  }
  v.clear();
}

void XsdGraph::__add(XsdGraphNodeInstance *parent, XsdAttribute *attribute)
{
  XsdGraphNode *node             = __findNode(attribute->type());
  XsdGraphNodeInstance *instance = NULL;

  if(node != NULL)
  {
    instance = new XsdGraphNodeInstance(attribute->name(), attribute->type(), node);
    __add(instance, node->spec());

    _instances.push_back(instance);
    parent->push_back(instance);
  }
}

void XsdGraph::__add(XsdGraphNodeInstance *parent, XsdRegularExpression *regexp)
{
  XsdGraphNode *node             = __findNode(regexp->type());
  XsdGraphNodeInstance *instance = NULL;

  if(node != NULL)
  {
    instance = new XsdGraphNodeInstance(regexp->name(), regexp->type(), node);
    __add(instance, node->spec());

    _instances.push_back(instance);
    parent->push_back(instance);
  }
}

void XsdGraph::__add(XsdGraphNodeInstance *parent, XsdInterval *interval)
{
  XsdGraphNode *node             = __findNode(interval->type());
  XsdGraphNodeInstance *instance = NULL;

  if(node != NULL)
  {
    instance = new XsdGraphNodeInstance(interval->name(), interval->type(), node);
    __add(instance, node->spec());

    _instances.push_back(instance);
    parent->push_back(instance);
  }
}

void XsdGraph::__add(XsdGraphNodeInstance *parent, XsdEnumeration *enumeration)
{
  XsdGraphNode *node             = __findNode(enumeration->type());
  XsdGraphNodeInstance *instance = NULL;

  if(node != NULL)
  {
    instance = new XsdGraphNodeInstance(enumeration->name(), enumeration->type(), node);
    __add(instance, node->spec());

    _instances.push_back(instance);
    parent->push_back(instance);
  }
}

void XsdGraph::__add(XsdGraphNodeInstance *parent, XsdNode *node)
{
  switch(node->nodeType())
  {
    case XSD_NODE_TYPE_SEQUENCE:
      __add(parent, (XsdSequence*)node);
      break;
    case XSD_NODE_TYPE_CHOICE:
       __add(parent, (XsdChoice*)node);
      break;
    case XSD_NODE_TYPE_ELEMENT:
       __add(parent, (XsdElement*)node);
      break;
    case XSD_NODE_TYPE_REG_EXP:
       __add(parent, (XsdRegularExpression*)node);
      break;
    case XSD_NODE_TYPE_INTERVAL:
       __add(parent, (XsdInterval*)node);
      break;
    case XSD_NODE_TYPE_ATTRIBUTE:
       __add(parent, (XsdAttribute*)node);
      break;
    case XSD_NODE_TYPE_ENUMERATION:
       __add(parent, (XsdEnumeration*)node);
      break;
    default:
      cout << "uncaught " << node->nodeType() << endl;
      exit(-1);
  }
}


XsdGraphNode* XsdGraph::__findNode(string name)
{
  FORC(vector<XsdGraphNode*>, n, _nodes)
  {
    if((*n)->name() == name)
    {
      return (*n);
    }
  }
  return NULL;
}
