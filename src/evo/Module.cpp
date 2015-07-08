/*************************************************************************
 *                                                                       *
 * This file is part of Yet Another Robot Simulator (YARS).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/YARS                                  *
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



#include "Module.h"

#include <iostream>

#include "base/macros.h"


Module::Module(string name)
{
  _name   = name;
  _linked = false;
}

Module::~Module()
{
  FORC(Nodes, n, _nodes) delete (*n);
  _nodes.clear();
}

void Module::addNode(Node *node) throw (ENPException)
{
  _nodes.push_back(node);
  switch(node->type())
  {
    case NODE_TYPE_SENSOR:
      _sensors.push_back(node);
      break;
    case NODE_TYPE_ACTUATOR:
      _sensors.push_back(node);
      break;
    case NODE_TYPE_HIDDEN:
      _hidden.push_back(node);
      break;
    default:
      throw ENPException("Module::addNode: unknown node type");
  }
}

string Module::name()
{
  return _name;
}

void Module::linkTo(Module *target)
{
  _linked = true;
  _target = target;
}


bool Module::operator==(const Module m)
{
  Nodes mn = m._nodes;
  FORC(Nodes, a, _nodes)
  {
    bool foundNode = false;
    FORC(Nodes, b, mn)
    {
      if(**a == **b)
      {
        foundNode = true;
        break;
      }
    }
    if(foundNode == false) return false;
  }
  return true;
}

bool Module::operator!=(const Module m)
{
  Nodes mn = m._nodes;
  FORC(Nodes, a, _nodes)
  {
    bool foundNode = true;
    FORC(Nodes, b, mn)
    {
      if(**a != **b)
      {
        foundNode = false;
        break;
      }
    }
    if(foundNode == false) return true;
  }
  return false;
}


Nodes::iterator Module::n_begin()
{
  return _nodes.begin();
}

Nodes::iterator Module::n_end()
{
  return _nodes.end();
}

int Module::n_size()
{
  return _nodes.size();
}

Edges::iterator Module::e_begin()
{
  return _edges.begin();
}

Edges::iterator Module::e_end()
{
  return _edges.end();
}

int Module::e_size()
{
  return _edges.size();
}

bool Module::removeEdge(Edge *e)
{
  FORC(Edges, i, _edges)
  {
    if((**i) == *e)
    {
      _edges.erase(i);
      return true;
    }
  }
  return false;
}

int Module::s_size()
{
  return _sensors.size();
}

int Module::a_size()
{
  return _actuators.size();
}

int Module::h_size()
{
  return _hidden.size();
}


void Module::addEdge(Node *src, Node *dst, double weight) throw (ENPException)
{
  if(dst->contains(src)) throw ENPException("Module::addEdge: The destination node already contains an edge from the source node");
  Edge *e = new Edge();
  e->setSource(src);
  e->setDestination(dst);
  e->setWeight(weight);

  dst->addEdge(e);

  _edges.push_back(e);
}


Node* Module::node(int index)
{
  return _nodes[index];
}


Edge* Module::edge(int index)
{
  return _edges[index];
}
