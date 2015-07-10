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



#ifndef __DATA_EVOLUTION_H__
#define __DATA_EVOLUTION_H__

#include "DataNode.h"

#include "DataEvolutionNode.h"
#include "DataEvolutionEdge.h"

# define TAG_EVOLUTION                        (char*)"evolution"
# define TAG_EVOLUTION_DEFINITION             (char*)"evolution_definition"

class DataEvolution : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataEvolution(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataEvolution();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    DataEvolutionNode*  node();
    DataEvolutionEdge* edge();

  private:
    DataEvolutionNode  *_node;
    DataEvolutionEdge *_edge;

};

#endif // ___DATA_EVOLUTION_H__


