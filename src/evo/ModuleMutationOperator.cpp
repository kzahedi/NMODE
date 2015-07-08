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



#include "ModuleMutationOperator.h"

#include "base/macros.h"
#include "base/Random.h"


// ModuleMutationOperator::ModuleMutationOperator()
// {
// }

#define FORALLEDGES for(Edges::iterator e = m->e_begin(); e != m->e_end(); e++)

void ModuleMutationOperator::mutate(Module *m,
                                    DataEvolutionNeuron *den,
                                    DataEvolutionSynapse *des)
{
  __mutateRemoveEdge(m, des->delProbability());
  __mutateModifyEdge(m, des->modifyProbability(), 
                        des->modifyDelta(), 
                        des->modifyMaxValue());
  __mutateAddEdge(m,    des->addProbability(),
                        des->addMaxValue(),
                        des->addIteartions());
}


void ModuleMutationOperator::__mutateRemoveEdge(Module *m, double probability)
{
  Edges toBeRemoved;
  FORALLEDGES
  {
    if(Random::unit() < probability)
    {
      toBeRemoved.push_back(*e);
    }
  }

  // for(Edges::reverse_iterator e = toBeRemoved.end();
      // e != toBeRemoved.begin(); e--)
  // {
    // Node *dest = (*e)->destination();
    // dest->removeEdge(*e);
    // m->removeEdge(*e);
  // }
}

static void ModuleMutationOperator__mutateModifyEdge(Module *m, double probability,
                                                                double delta,
                                                                double max)
{
  FORALLEDGES
  {
    if(Random::unit() < probability)
    {
      double weight = (*e)->weight()+ (2.0 * Random::unit() - 1.0) * delta;
      if(weight >  max) weight =  max;
      if(weight < -max) weight = -max;
      (*e)->setWeight(weight);
    }
  }
}

void ModuleMutationOperator::__mutateAddEdge(Module *m, double probability,
                                                        double max,
                                                        int    iterations)
{
  if(Random::unit() < probability)
  {
    for(int i = 0; i < iterations; i++)
    {
      // HIER
    }
  }
}

