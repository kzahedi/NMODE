/*************************************************************************
 *                                                                       *
 * This file is part of Simulator of Neural Pathways (ENP).              *
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



#include "DataSimulator.h"

#include <iostream>

#define TAG_WD  (char*)"wd"
#define TAG_XML (char*)"xml"
#define TAG_NR  (char*)"nr"


using namespace std;

DataSimulator::DataSimulator(DataNode *parent)
  : DataNode(parent)
{ }

DataSimulator::~DataSimulator()
{
}


void DataSimulator::add(DataParseElement *element)
{
  if(element->closing(TAG_SIMULATOR))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_SIMULATOR))
  {
    element->set(TAG_WD,  _workingDirectory);
    element->set(TAG_XML, _xml);
    element->set(TAG_NR,  _nr);
    return;
  }
}

void DataSimulator::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_SIMULATOR_DEFINITION);
  root->add(NA(TAG_WD,  TAG_XSD_STRING,                true));
  root->add(NA(TAG_XML, TAG_XSD_STRING,                true));
  root->add(NA(TAG_NR,  TAG_POSITIVE_NON_ZERO_DECIMAL, true));
  spec->add(root);
}

string DataSimulator::workingDirectory()
{
  return _workingDirectory;
}

string DataSimulator::xml()
{
  return _xml;
}

int DataSimulator::nr()
{
  return _nr;
}

