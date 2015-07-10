/*************************************************************************
 *                                                                       *
 * This file is part of Evolution of Neural Pathways (ENP).              *
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



#include "DataIndividual.h"

#include "glog/logging.h"

#define TAG_ID        (char*)"id"
#define TAG_FITNESS   (char*)"fitness"
#define TAG_OFFSPRING (char*)"offspring"

DataIndividual::DataIndividual(DataXsdNode *parent)
  : DataXsdNode(parent)
{
  _id         = 1;
  _fitness    = 0.0;
}

void DataIndividual::add(DataParseElement *element)
{
  VLOG(100) << "parsing " << element->name();
  if(element->closing(TAG_INDIVIDUAL))
  {
    current = parent;
  }

  if(element->opening(TAG_MODULE))
  {
    DataModule *dpm = new DataModule(this);
    _modules.push_back(dpm);
    current = dpm;
    current->add(element);
  }
}

void DataIndividual::createXsd(XsdSpecification *spec)
{
  XsdSequence *_root = new XsdSequence(TAG_INDIVIDUAL_DEFINITION);
  _root->add(NA(TAG_ID,        TAG_POSITIVE_INTEGER, false));
  _root->add(NA(TAG_FITNESS,   TAG_XSD_DECIMAL,      false));
  _root->add(NA(TAG_OFFSPRING, TAG_POSITIVE_INTEGER, false));
  spec->add(_root);

  DataModule::createXsd(spec);
}
