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



#ifndef __DATA__EDGE_H__
#define __DATA__EDGE_H__

#include "DataNode.h"
#include "base/P3D.h"

#include <vector>

using namespace std;

# define TAG_EDGE            (char*)"edge"
# define TAG_EDGE_DEFINITION (char*)"population_module_edge_definition"

class DataPopulationModuleEdge : public DataNode
{
  public:
    DataPopulationModuleEdge(DataNode *parent);
    // ~DataPopulationModuleEdge();

    //DataPopulationModuleEdge(const DataPopulationModuleEdge);
    //DataPopulationModuleEdge operator=(const DataPopulationModuleEdge);

    void add(DataParseElement *element);
    static void createXsd(XsdSpecification *spec);

    string source();
    string destination();
    double weight();

  private:
    string _source;
    string _destination;
    double _weight;
};

typedef vector<DataPopulationModuleEdge*> DataPopulationModuleEdges;

#endif // __DATA__EDGE_H__
