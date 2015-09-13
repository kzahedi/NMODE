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




#include "DataEvolutionNode.h"

#include <iostream>


#define TAG_MODIFY               (char*)"modify"
#define TAG_MODIFY_DEFINITION    (char*)"modify_definition"
#define TAG_ADD                  (char*)"add"
#define TAG_ADD_DEFINITION       (char*)"add_definition"
#define TAG_DEL                  (char*)"delete"
#define TAG_DEL_DEFINITION       (char*)"delete_definition"
#define TAG_PROBABILITY          (char*)"probability"
#define TAG_MAX                  (char*)"maximum"
#define TAG_DELTA                (char*)"delta"
#define TAG_COST                 (char*)"cost"


using namespace std;

DataEvolutionNode::DataEvolutionNode(DataNode *parent)
  : DataNode(parent)
{
  _modifyProbability = 0.1;
  _modifyMaxValue    = 4.0;
  _modifyDelta       = 0.5;
  _addProbability    = 0.01;
  _addMaxValue       = 1.0;
  _delProbability    = 0.1;
  _cost              = 0.0;
}

DataEvolutionNode::~DataEvolutionNode()
{
  // nothing to be done
}

void DataEvolutionNode::add(DataParseElement *element)
{
  if(element->closing(TAG_EVOLUTION_NODE))
  {
    current = parent;
  }

  if(element->opening(TAG_EVOLUTION_NODE))
  {
    element->set(TAG_COST, _cost);
  }

  if(element->opening(TAG_MODIFY))
  {
    element->set(TAG_PROBABILITY, _modifyProbability);
    element->set(TAG_MAX,         _modifyMaxValue);
    element->set(TAG_DELTA,       _modifyDelta);
  }

  if(element->opening(TAG_ADD))
  {
    element->set(TAG_PROBABILITY, _addProbability);
    element->set(TAG_MAX,         _addMaxValue);
  }

  if(element->opening(TAG_DEL))
  {
    element->set(TAG_PROBABILITY, _delProbability);
  }

}

void DataEvolutionNode::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_EVOLUTION_NODE_DEFINITION);
  root->add(NA(TAG_COST,   TAG_POSITIVE_DECIMAL,     false));
  root->add(NE(TAG_MODIFY, TAG_MODIFY_DEFINITION,    1, 1));
  root->add(NE(TAG_ADD,    TAG_ADD_DEFINITION,       1, 1));
  root->add(NE(TAG_DEL,    TAG_DEL_DEFINITION,       1, 1));
  spec->add(root);

  XsdSequence *modify = new XsdSequence(TAG_MODIFY_DEFINITION);
  modify->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL, true));
  modify->add(NA(TAG_MAX,         TAG_POSITIVE_DECIMAL, true));
  modify->add(NA(TAG_DELTA,       TAG_POSITIVE_DECIMAL, true));
  spec->add(modify);
  
  XsdSequence *add = new XsdSequence(TAG_ADD_DEFINITION);
  add->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL, true));
  add->add(NA(TAG_MAX,         TAG_POSITIVE_DECIMAL, true));
  spec->add(add);

  XsdSequence *del = new XsdSequence(TAG_DEL_DEFINITION);
  del->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL, true));
  spec->add(del);
}

double DataEvolutionNode::modifyProbability()
{
  return _modifyProbability;
}

double DataEvolutionNode::modifyMaxValue()
{
  return _modifyMaxValue;
}

double DataEvolutionNode::modifyDelta()
{
  return _modifyDelta;
}

double DataEvolutionNode::addProbability()
{
  return _addProbability;
}

double DataEvolutionNode::addMaxValue()
{
  return _addMaxValue;
}

double DataEvolutionNode::delProbability()
{
  return _delProbability;
}

double DataEvolutionNode::cost()
{
  return _cost;
}
