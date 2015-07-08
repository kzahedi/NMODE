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

#include "base/macros.h"

Node::Node()
{
  _type = -1;
}

Node::~Node()
{
}

void Node::setPosition(P3D position)
{
  _position = position;
}

void Node::setType(string type) throw (ENPException)
{
  _type = -1;
  if(type == "sensor")   _type = MODULE_NODE_TYPE_SENSOR;
  if(type == "actuator") _type = MODULE_NODE_TYPE_ACTUATOR;
  if(type == "hidden")   _type = MODULE_NODE_TYPE_HIDDEN;
  if(_type == -1) throw ENPException("Node::setType uknown type");
}

void Node::setLabel(string label)
{
  _label = label;
}

void Node::setTransferfunction(string tf)
{
  _transferfunction = tf;
}

P3D Node::position()
{
  return _position;
}

int Node::type()
{
  return _type;
}

string Node::label()
{
  return _label;
}

string Node::transferfunction()
{
  return _transferfunction;
}

bool Node::operator==(const Node o)
{
  return (_position         == o._position &&
          _label            == o._label    &&
          _type             == o._type     &&
          _transferfunction == o._transferfunction);
}

bool Node::operator!=(const Node o)
{
  return (_position         != o._position ||
          _label            != o._label    ||
          _type             != o._type     ||
          _transferfunction != o._transferfunction);
}

Edges::iterator Node::e_begin()
{
  return _in.begin();
}

Edges::iterator Node::e_end()
{
  return _in.end();
}

void Node::addEdge(Edge *e)
{
  _in.push_back(e);
}

bool Node::removeEdge(Edge *e)
{
  FORC(Edges, i, _in)
  {
    if((**i) == *e)
    {
      _in.erase(i);
      return true;
    }
  }
  return false;
}
