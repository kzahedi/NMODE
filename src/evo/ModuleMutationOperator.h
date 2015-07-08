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



#ifndef __MODULE_MUTATION_OPERATOR_H__
#define __MODULE_MUTATION_OPERATOR_H__

#include "data/DataEvolutionNeuron.h"
#include "data/DataEvolutionSynapse.h"
#include "Module.h"

class ModuleMutationOperator
{
  public:
    // ~ModuleMutationOperator();

    //ModuleMutationOperator(const ModuleMutationOperator);
    //ModuleMutationOperator operator=(const ModuleMutationOperator);

    static void mutate(Module *module,
                       DataEvolutionNeuron *_den,
                       DataEvolutionSynapse *_des);

  private:
    static void __mutateDelEdge(Module *m, double probability);
    static void __mutateModifyEdge(Module *m, double probability,
                                              double delta,
                                              double max);
    static void __mutateAddEdge(Module *m,    double probability,
                                              double max);
    static void __mutateAddNode(Module *m,    double probability,
                                              double max);
    static void __mutateModifyNode(Module *m, double probability,
                                              double delta,
                                              double max);

    static void __mutateDelNode(Module *m,    double probability);
};


#endif // __MODULE_MUTATION_OPERATOR_H__
