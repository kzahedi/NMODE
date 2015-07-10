/*************************************************************************
 *                                                                       *
 * This file is part of Configuration of Neural Pathways (ENP).          *
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



#include "DataConfiguration.h"

#include "base/macros.h"

#include <iostream>
#include <glog/logging.h>

using namespace std;

DataConfiguration::DataConfiguration(DataNode *parent)
  : DataNode(parent)
{ }

DataConfiguration::~DataConfiguration()
{
  FORC(DataModules, m, _modules) delete (*m);
  _modules.clear();
}


void DataConfiguration::add(DataParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->closing(TAG_CONFIGURATION))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_CONFIGURATION))
  {
    return;
  }

  if(element->opening(TAG_MODULE))
  {
    DataModule* module = new DataModule(this);
    _modules.push_back(module);
    current = module;
    current->add(element);
  }
}

void DataConfiguration::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_CONFIGURATION_DEFINITION);
  root->add(NE(TAG_MODULE,  TAG_MODULE_DEFINITION,  1, TAG_XSD_UNBOUNDED));
  spec->add(root);

  DataModule::createXsd(spec);
}

DataModules DataConfiguration::modules()
{
  return _modules;
}
