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

#include <glog/logging.h>

#include "base/macros.h"
#include "base/Random.h"


// ModuleMutationOperator::ModuleMutationOperator()
// {
// }

#define FORALLEDGES for(Edges::iterator e = m->e_begin(); e != m->e_end(); e++)
#define FORALLNODES for(Nodes::iterator n = m->n_begin(); n != m->n_end(); n++)

#define DIST(a, b) sqrt((a.x - b.x) * (a.x - b.x) +\
                        (a.y - b.y) * (a.y - b.y) +\
                        (a.z - b.z) * (a.z - b.z));

void ModuleMutationOperator::mutate(Module *m,
                                    DataEvolutionNeuron *den,
                                    DataEvolutionSynapse *des)
{
  __mutateRemoveEdge(m, des->delProbability());
  __mutateModifyEdge(m, des->modifyProbability(), 
                        des->modifyDelta(), 
                        des->modifyMaxValue());
  __mutateAddEdge(m,    des->addProbability(),
                        des->addMaxValue());
  __mutateModifyNode(m, den->modifyProbability(),
                        den->modifyDelta(),
                        den->modifyMaxValue());
  __mutateAddNode(m,    den->addProbability(),
                        den->addMaxValue());
  __mutateDelNode(m,    den->delProbability());
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

void ModuleMutationOperator::__mutateModifyEdge(Module *m, double probability,
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
                                                        double max)
{
  if(Random::unit() >= probability) return;

  double probabilities[m->n_size()][m->a_size() + m->h_size()];
  double sum = 0.0;
  double d   = 0.0;

  for(int s_index = 0; s_index < m->n_size(); s_index++)
  {
    Node *src_node = m->node(s_index);
    for(int d_index = m->s_size(); d_index < m->n_size(); d_index++)
    {
      Node *dst_node = m->node(d_index);
      if(src_node->contains(dst_node))
      {
        d    = DIST(src_node->position(), dst_node->position());
        sum += d;
        probabilities[s_index][d_index] = d;
      }
      else
      {
        probabilities[s_index][d_index] = 0.0;
      }
    }
  }

  for(int s_index = 0; s_index < m->n_size(); s_index++)
  {
    for(int d_index = m->s_size(); d_index < m->n_size(); d_index++)
    {
      probabilities[s_index][d_index] /= sum;
    }
  }

  double p  = Random::unit();
  double s  = 0.0;
  for(int s_index = 0; s_index < m->n_size(); s_index++)
  {
    for(int d_index = m->s_size(); d_index < m->n_size(); d_index++)
    {
      s += probabilities[s_index][d_index];
      if(p < s)
      {
        Node *src = m->node(s_index);
        Node *dst = m->node(d_index);
        m->addEdge(src, dst, Random::rand(-max, max));
      }
    }
  }
}

void ModuleMutationOperator::__mutateAddNode(Module *m, double probability, double max)
{
  if(Random::unit() >= probability) return;

  int ei    = int(Random::unit() * m->e_size() + 0.5); // edge index

  Node *n   = new Node();

  Edge *e   = m->edge(ei);
  Node *src = e->source();
  Node *dst = e->destination();

  P3D sp    = src->position();
  P3D dp    = dst->position();
  P3D np    = (sp + dp) * 0.5;

  n->setType("hidden");
  n->setPosition(np);
  n->setValue(Random::rand(-max, max));

  e->setSource(n);
  m->addEdge(src, n, 1.0);
}

void ModuleMutationOperator::__mutateModifyNode(Module *m, double probability,
                                                           double delta,
                                                           double max)
{
  if(Random::unit() >= probability) return;

  int ni       = int(Random::unit() * m->n_size() + 0.5);
  Node *n      = m->node(ni);
  double value = n->value();
  value += Random::rand(-delta, delta);
  if(value >  max) value =  max;
  if(value < -max) value = -max;
  n->setValue(value);
}


void ModuleMutationOperator::__mutateDelNode(Module *m, double probability)
{
  if(Random::unit() >= probability) return;

  int ni   = int(Random::unit() * m->n_size() + 0.5);
  Node *nn = m->node(ni);
  FORALLNODES (*n)->removeEdge(nn);
}
