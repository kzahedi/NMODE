/*************************************************************************
 *                                                                       *
 * This file is part of Evolution of Neural Pathways (Population).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/Population                                   *
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



#include "DataPopulation.h"

#include "glog/logging.h"

#define TAG_GENERATION (char*)"generation"

DataPopulation::DataPopulation(DataNode *parent)
  : DataNode(parent)
{
  _id         = 1;
  _generation = 1;
  _fitness    = 0.0;
}

void DataPopulation::add(DataParseElement *element)
{
  VLOG(100) << "parsing " << element->name();
  if(element->closing(TAG_POPULATION))
  {
    current = parent;
  }

  if(element->opening(TAG_POPULATION))
  {
    element->set(TAG_GENERATION, _generation);
    VLOG(100) << "set generation to " << _generation;
  }

  if(element->opening(TAG_POPULATION_MODULE))
  {
    DataPopulationModule *dpm = new DataPopulationModule(this);
    _modules.push_back(dpm);
    current = dpm;
    current->add(element);
  }
}

void DataPopulation::createXsd(XsdSpecification *spec)
{
  XsdSequence *_root = new XsdSequence(TAG_POPULATION_DEFINITION);
  _root->add(NA(TAG_GENERATION, TAG_POSITIVE_INTEGER, false));
  _root->add(NE(TAG_POPULATION_MODULE, TAG_POPULATION_MODULE_DEFINITION, 1, TAG_XSD_UNBOUNDED));
  spec->add(_root);

  DataPopulationModule::createXsd(spec);
}
