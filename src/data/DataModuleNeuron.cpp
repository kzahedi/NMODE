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



#include "DataModuleNeuron.h"

#include <iostream>

#define TAG_X                           (char*)"x"
#define TAG_Y                           (char*)"y"
#define TAG_Z                           (char*)"z"
#define TAG_NAME                        (char*)"name"
#define TAG_TYPE                        (char*)"type"
#define TAG_ACTUATOR                    (char*)"actuator"
#define TAG_SENSOR                      (char*)"sensor"
#define TAG_NAME                        (char*)"name"
#define TAG_TYPE_DEFINITION             (char*)"type_definition"
#define TAG_LABEL                       (char*)"label"
#define TAG_POSITION                    (char*)"position"
#define TAG_XYZ_DEFINITION              (char*)"xyz_definition"
#define TAG_TRANSFERFUNCTION            (char*)"transferfunction"
#define TAG_TRANSFERFUNCTION_DEFINITION (char*)"transferfunction_definition"

using namespace std;

DataModuleNeuron::DataModuleNeuron(DataNode *parent)
  : DataNode(parent)
{ }

DataModuleNeuron::~DataModuleNeuron()
{ }


void DataModuleNeuron::add(DataParseElement *element)
{
  if(element->closing(TAG_MODULE_NEURON))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_MODULE_NEURON))
  {
    element->set(TAG_TYPE,  _type);
    element->set(TAG_LABEL, _label);
  }

  if(element->opening(TAG_POSITION))
  {
    element->set(TAG_X, _position.x);
    element->set(TAG_Y, _position.y);
    element->set(TAG_Z, _position.z);
  }

  if(element->opening(TAG_TRANSFERFUNCTION))
  {
    element->set(TAG_NAME, _transferfunction);
  }
}

void DataModuleNeuron::createXsd(XsdSpecification *spec)
{
  XsdSequence  *root = new XsdSequence(TAG_MODULE_NEURON_DEFINITION);
  root->add(NA(TAG_TYPE,             TAG_TYPE_DEFINITION,             true));
  root->add(NA(TAG_LABEL,            TAG_XSD_STRING,                  true));
  root->add(NE(TAG_POSITION,         TAG_XYZ_DEFINITION,              1, 1));
  root->add(NE(TAG_TRANSFERFUNCTION, TAG_TRANSFERFUNCTION_DEFINITION, 1, 1));
  spec->add(root);

  XsdSequence  *tfunc = new XsdSequence(TAG_TRANSFERFUNCTION_DEFINITION);
  tfunc->add(NA(TAG_TRANSFERFUNCTION, TAG_XSD_STRING, true));
  spec->add(root);

  XsdEnumeration *type = new XsdEnumeration(TAG_TYPE_DEFINITION, TAG_XSD_STRING);
  type->add(TAG_SENSOR);
  type->add(TAG_ACTUATOR);
  spec->add(type);

}

string DataModuleNeuron::type()
{
  return _type;
}

string DataModuleNeuron::label()
{
  return _label;
}

P3D DataModuleNeuron::position()
{
  return _position;
}

string DataModuleNeuron::transferfunction()
{
  return _transferfunction;
}

