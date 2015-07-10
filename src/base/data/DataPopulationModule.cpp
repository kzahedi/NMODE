/*************************************************************************
 *                                                                       *
 * This file is part of Evolution of Neural Pathways (PopulationModule).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/PopulationModule                                   *
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



#include "DataPopulationModule.h"

#include "glog/logging.h"

#define TAG_ID        (char*)"id"
#define TAG_OFFSPRING (char*)"offspring"
#define TAG_FITNESS   (char*)"fitness"


DataPopulationModule::DataPopulationModule(DataNode *parent)
  : DataNode(parent)
{
  _id        = 1;
  _fitness   = 0.0;
  _offspring = 0;
}

void DataPopulationModule::add(DataParseElement *element)
{
  VLOG(100) << "parsing " << element->name();
  if(element->closing(TAG_POPULATION_MODULE))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_POPULATION_MODULE))
  {
    element->set(TAG_ID,         _id);
    element->set(TAG_FITNESS,    _fitness);
    element->set(TAG_OFFSPRING,  _offspring);
    VLOG(100) << "set id to "        << _id;
    VLOG(100) << "set fitness to "   << _fitness;
    VLOG(100) << "set offspring to " << _offspring;
  }

  if(element->opening(TAG_POPULATION_MODULE_NODE))
  {
    DataPopulationModuleNode *node = new DataPopulationModuleNode(this);
    current = node;
    _nodes.push_back(node);
    current->add(element);
  }

  if(element->opening(TAG_POPULATION_MODULE_EDGE))
  {
    DataPopulationModuleEdge *edge = new DataPopulationModuleEdge(this);
    current = edge;
    _edges.push_back(edge);
    current->add(element);
  }

}

void DataPopulationModule::createXsd(XsdSpecification *spec)
{
  XsdSequence *_root = new XsdSequence(TAG_POPULATION_MODULE_DEFINITION);
  _root->add(NA(TAG_ID,        TAG_POSITIVE_INTEGER, false));
  _root->add(NA(TAG_FITNESS,   TAG_XSD_DECIMAL,      false));
  _root->add(NA(TAG_OFFSPRING, TAG_POSITIVE_INTEGER, false));
  _root->add(NE(TAG_POPULATION_MODULE_NODE, TAG_POPULATION_MODULE_NODE_DEFINITION, 0, TAG_XSD_UNBOUNDED));
  _root->add(NE(TAG_POPULATION_MODULE_EDGE, TAG_POPULATION_MODULE_EDGE_DEFINITION, 0, TAG_XSD_UNBOUNDED));
  spec->add(_root);

  DataPopulationModuleNode::createXsd(spec);
  DataPopulationModuleEdge::createXsd(spec);
}

