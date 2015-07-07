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



#ifndef __MODULE_NEURON_H__
#define __MODULE_NEURON_H__

#include <vector>
#include <string>
#include <ostream>

#include "base/P3D.h"

#define MODULE_NEURON_TYPE_SENSOR   1001
#define MODULE_NEURON_TYPE_ACTUATOR 1002
#define MODULE_NEURON_TYPE_HIDDEN   1003

using namespace std;

class ModuleNeuron
{
  public:
    ModuleNeuron();
    ~ModuleNeuron();

    //ModuleNeuron(const ModuleNeuron);
    //ModuleNeuron operator=(const ModuleNeuron);
    bool operator==(const ModuleNeuron o);
    bool operator!=(const ModuleNeuron o);

    void setPosition(P3D position);
    void setType(string type);
    void setLabel(string label);
    void setTransferfunction(string tf);

    P3D    position();
    int    type();
    string label();
    string transferfunction();

    friend std::ostream& operator<<(std::ostream& str, const ModuleNeuron& n)
    {
      str << n._label << ", " << n._type << ", " << n._position << ", " << n._transferfunction;
      return str;
    };


  private:

    P3D    _position;
    int    _type;
    string _label;
    string _transferfunction;
};

typedef vector<ModuleNeuron*> ModuleNeurons;

#endif // __MODULE_NEURON_H__

