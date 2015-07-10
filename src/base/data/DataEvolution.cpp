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



#include "DataEvolution.h"

#include <iostream>
#include <glog/logging.h>

using namespace std;

DataEvolution::DataEvolution(DataXsdNode *parent)
  : DataXsdNode(parent)
{ }

DataEvolution::~DataEvolution()
{
  delete _node;
  delete _edge;
}


void DataEvolution::add(DataParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->closing(TAG_EVOLUTION))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_EVOLUTION))
  {
    return;
  }

  if(element->opening(TAG_EVOLUTION_NODE))
  {
    _node = new DataEvolutionNode(this);
    current = _node;
    current->add(element);
  }

  if(element->opening(TAG_EVOLUTION_EDGE))
  {
    _edge = new DataEvolutionEdge(this);
    current  = _edge;
    current->add(element);
  }

}

void DataEvolution::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_EVOLUTION_DEFINITION);
  root->add(NE(TAG_EVOLUTION_NODE,  TAG_EVOLUTION_NODE_DEFINITION,  1, 1));
  root->add(NE(TAG_EVOLUTION_EDGE, TAG_EVOLUTION_EDGE_DEFINITION, 1, 1));
  spec->add(root);

  DataEvolutionNode::createXsd(spec);
  DataEvolutionEdge::createXsd(spec);
}

DataEvolutionNode* DataEvolution::node()
{
  return _node;
}

DataEvolutionEdge* DataEvolution::edge()
{
  return _edge;
}

