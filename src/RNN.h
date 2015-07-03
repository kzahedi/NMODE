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



#ifndef __RNN_H__
#define __RNN_H__

#include "P3D.h"

#include <vector>

using namespace std;

class Synapse;

#define NEURON_TRANSFER_FUNCTION_TANH 1
#define NEURON_TRANSFER_FUNCTION_SIGM 2
#define NEURON_TRANSFER_FUNCTION_ID   3

class Neuron
{
  public:
    Neuron();
    // ~Neuron();

    //Neuron(const Neuron);
    //Neuron operator=(const Neuron);

    void updateActivity();
    void updateOutput();

    double output();

  private:
    double           _activity;
    double           _output;
    double           _bias;
    int              _type;
    int              _transferfunction;
    P3D              _position;
    vector<Synapse*> _in;
};

class Synapse
{
  public:
    Synapse();
    // ~Synapse();

    //Synapse(const Synapse);
    //Synapse operator=(const Synapse);

    double getCurrentValue();

  private:
    Neuron *_src;
    // Neuron *_dst;
    double _weight;
};


class RNN
{
  public:
    RNN();
    // ~rnn();

    //rnn(const rnn);
    //rnn operator=(const rnn);

  private:
};

typedef vector<Neuron*>  Neurons;
typedef vector<Synapse*> Synapses;

#endif // __RNN_H__
