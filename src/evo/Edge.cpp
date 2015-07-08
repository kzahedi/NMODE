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



#include "Edge.h"

Edge::Edge()
{
}

Edge::~Edge()
{ }

void Edge::setSource(Node *src)
{
  _src = src;
}

void Edge::setDestination(Node *dest)
{
  _dest = dest;
}

void Edge::setWeight(double weight)
{
  _weight = weight;
}

Node* Edge::source()
{
  return _src;
}

Node* Edge::destination()
{
  return _dest;
}

double Edge::weight()
{
  return _weight;
}

bool Edge::operator==(const Edge o)
{
  return (_weight == o._weight &&
          _src    == o._src    &&
          _dest   == o._dest);
}

bool Edge::operator!=(const Edge o)
{
  return (_weight != o._weight ||
          _src    != o._src    ||
          _dest   != o._dest);
}

