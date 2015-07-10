/*************************************************************************
 *                                                                       *
 * This file is part of Module of Neural Pathways (ENP).                 *
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



#include "DataModuleEdge.h"

#include <iostream>
#include <glog/logging.h>

#define TAG_SOURCE                      (char*)"source"
#define TAG_DESTINATION                 (char*)"destination"
#define TAG_WEIGHT                      (char*)"weight"

using namespace std;

DataPopulationModuleEdge::DataPopulationModuleEdge(DataNode *parent)
  : DataNode(parent)
{ }

void DataPopulationModuleEdge::add(DataParseElement *element)
{
  if(element->closing(TAG_EDGE))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_EDGE))
  {
    element->set(TAG_SOURCE,      _source);
    element->set(TAG_DESTINATION, _destination);
    element->set(TAG_WEIGHT,      _weight);
    VLOG(100) << "set edge values to " << _source << " -> " << _destination << " with " << _weight;
  }

}

void DataPopulationModuleEdge::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_EDGE_DEFINITION);
  root->add(NA(TAG_SOURCE,      TAG_XSD_STRING,  true));
  root->add(NA(TAG_DESTINATION, TAG_XSD_STRING,  true));
  root->add(NA(TAG_WEIGHT,      TAG_XSD_DECIMAL, true));
  spec->add(root);
}

string DataPopulationModuleEdge::source()
{
  return _source;
}

string DataPopulationModuleEdge::destination()
{
  return _destination;
}

double DataPopulationModuleEdge::weight()
{
  return _weight;
}

