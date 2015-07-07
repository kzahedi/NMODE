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


Module::Module()
{
  _name = "name is missing";
  _linked = false;
}

Module::~Module()
{
  FORC(ModuleNeurons, n, _neurons) delete (*n);
  _neurons.clear();
}

void Module::addNeuron(ModuleNeuron *neuron)
{
  _neurons.push_back(neuron);
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
  ModuleNeurons mn = m._neurons;
  FORC(ModuleNeurons, a, _neurons)
  {
    bool foundNeuron = false;
    FORC(ModuleNeurons, b, mn)
    {
      if(**a == **b)
      {
        foundNeuron = true;
        break;
      }
    }
    if(foundNeuron == false) return false;
  }
  return true;
}

bool Module::operator!=(const Module m)
{
  ModuleNeurons mn = m._neurons;
  FORC(ModuleNeurons, a, _neurons)
  {
    bool foundNeuron = true;
    FORC(ModuleNeurons, b, mn)
    {
      if(**a != **b)
      {
        foundNeuron = false;
        break;
      }
    }
    if(foundNeuron == false) return true;
  }
  return false;
}


ModuleNeurons Module::neurons()
{
  return _neurons;
}
