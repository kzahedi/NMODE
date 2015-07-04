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



#include "RNN.h"

#include "base/macros.h"
#include "base/ENPException.h"

/***************************************************************************
 *                            Neuron functions                             *
 ***************************************************************************/

#define SIGM(x) (1.0 / (1.0 + exp(-x)))

Neuron::Neuron()
{
  _activity = 0.0;
  _output   = 0.0;
  _bias     = 0.0;
}

Neuron::~Neuron()
{
  FORC(Synapses, s, _in) delete (*s);
  _in.clear();
}

void Neuron::updateActivity()
{
  _activity = _bias;
  FORC(Synapses, s, _in) _activity += (*s)->value();
}

void Neuron::updateOutput()
{
  switch(_transferfunction)
  {
    case NEURON_TRANSFER_FUNCTION_ID:
      _output = _activity;
      break;
    case NEURON_TRANSFER_FUNCTION_SIGM:
      _output = SIGM(_activity);
      break;
    case NEURON_TRANSFER_FUNCTION_TANH:
      _output = tanh(_activity);
      break;
    default:
      throw ENPException("Neuron::updateOutput: unknown transferfunction");
      break;
  }
}

double Neuron::output()
{
  return _output;
}

void Neuron::setBias(double value)
{
  _bias = value;
}

void Neuron::setTransferfunction(int transferfunction) throw(ENPException)
{
  if(transferfunction != NEURON_TRANSFER_FUNCTION_ID &&
     transferfunction != NEURON_TRANSFER_FUNCTION_SIGM &&
     transferfunction != NEURON_TRANSFER_FUNCTION_TANH)
  {
    throw ENPException("Neuron::setTransferfunction: unknown transferfunction");
  }
  _transferfunction = transferfunction;
}

void Neuron::addSynapse(Synapse *s)
{
  _in.push_back(s);
}



/***************************************************************************
 *                            Synapse functions                            *
 ***************************************************************************/


Synapse::Synapse() { }

double Synapse::value()
{
  return _weight * _src->output();
}

void Synapse::setSource(Neuron *s)
{
  _src = s;
}

void Synapse::setWeight(double w)
{
  _weight = w;
} 

/***************************************************************************
 *                              RNN Functions                              *
 ***************************************************************************/

RNN::RNN()
{
}

void RNN::addNeuron(Neuron *n)
{
  _neurons.push_back(n);
}

void RNN::update()
{
  FORC(Neurons, n, _neurons) (*n)->updateActivity();
  FORC(Neurons, n, _neurons) (*n)->updateOutput();
}
