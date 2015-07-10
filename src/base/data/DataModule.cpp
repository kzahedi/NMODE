/*************************************************************************
 *                                                                       *
 * This file is part of Module of Neural Pathways (ENP).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/ENP                                   *
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



#include "DataModule.h"

#include "base/macros.h"

#include <iostream>

#define TAG_NAME (char*)"name"

using namespace std;

DataModule::DataModule(DataNode *parent)
  : DataNode(parent)
{ }

DataModule::~DataModule()
{
}

void DataModule::add(DataParseElement *element)
{

  if(element->closing(TAG_MODULE))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_MODULE))
  {
    element->set(TAG_NAME, _name);
  }

  if(element->opening(TAG_MODULE_NODE))
  {
    DataModuleNode *node = new DataModuleNode(this);
    _nodes.push_back(node);
    current = node;
    node->add(element);
  }

}

void DataModule::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_MODULE_DEFINITION);
  root->add(NA(TAG_NAME,          TAG_XSD_STRING,               true));
  root->add(NE(TAG_MODULE_NODE, TAG_MODULE_NODE_DEFINITION, 1, TAG_XSD_UNBOUNDED));
  spec->add(root);

  DataModuleNode::createXsd(spec);
}

DataModuleNodes DataModule::nodes()
{
  return _nodes;
}

string DataModule::name()
{
  return _name;
}
