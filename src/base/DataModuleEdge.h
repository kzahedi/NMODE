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



#ifndef __DATA_MODULE_EDGE_H__
#define __DATA_MODULE_EDGE_H__

#include "DataNode.h"
#include "base/P3D.h"

#include <vector>

using namespace std;

# define TAG_MODULE_EDGE            (char*)"edge"
# define TAG_MODULE_EDGE_DEFINITION (char*)"module_edge_definition"

class DataModuleNode;

class DataModuleEdge : public DataNode
{
  public:
    DataModuleEdge(DataNode *parent);
    ~DataModuleEdge();

    //DataModuleEdge(const DataModuleEdge);
    //DataModuleEdge operator=(const DataModuleEdge);

    void add(DataParseElement *element);
    static void createXsd(XsdSpecification *spec);

    string source();
    string destination();

    double weight();
    void   setWeight(double);

    DataModuleNode* sourceNode();
    void            setSourceNode(DataModuleNode*);
    DataModuleNode* destinationNode();
    void            setDestinationNode(DataModuleNode*);

    bool operator==(const DataModuleEdge o);
    bool operator!=(const DataModuleEdge o);

  private:
    string          _source;
    string          _destination;
    double          _weight;
    DataModuleNode *_sourceNode;
    DataModuleNode *_destinationNode;
};

typedef vector<DataModuleEdge*> DataModuleEdges;

#endif // __DATA_MODULE_EDGE_H__
