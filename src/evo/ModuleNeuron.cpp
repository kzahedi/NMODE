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

ModuleNeuron::ModuleNeuron()
{
}

ModuleNeuron::~ModuleNeuron()
{
}

void ModuleNeuron::setPosition(P3D position)
{
  _position = position;
}

void ModuleNeuron::setType(string type)
{
  _type = type;
}

void ModuleNeuron::setLabel(string label)
{
  _label = label;
}

void ModuleNeuron::setTransferfunction(string tf)
{
  _transferfunction = tf;
}

P3D ModuleNeuron::position()
{
  return _position;
}

string ModuleNeuron::type()
{
  return _type;
}

string ModuleNeuron::label()
{
  return _label;
}

string ModuleNeuron::transferfunction()
{
  return _transferfunction;
}

bool ModuleNeuron::operator==(const ModuleNeuron o)
{
  return (_position         == o._position &&
          _label            == o._label    &&
          _type             == o._type     &&
          _transferfunction == o._transferfunction);
}

bool ModuleNeuron::operator!=(const ModuleNeuron o)
{
  return (_position         != o._position ||
          _label            != o._label    ||
          _type             != o._type     ||
          _transferfunction != o._transferfunction);
}
