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

#include "XsdParseNode.h"
#include "enp/P3D.h"

#include <vector>

using namespace std;

# define TAG_MODULE_EDGE            (char*)"edge"
# define TAG_MODULE_EDGE_DEFINITION (char*)"module_edge_definition"

class Node;

class Edge : public XsdParseNode
{
  public:
    Edge(XsdParseNode *parent);
    ~Edge();

    //Edge(const Edge);
    //Edge operator=(const Edge);

    void add(ParseElement *element);
    static void createXsd(XsdSpecification *spec);

    string source();
    string destination();

    double weight();
    void   setWeight(double);

    Node* sourceNode();
    void  setSourceNode(Node*);
    Node* destinationNode();
    void  setDestinationNode(Node*);

    bool operator==(const Edge o);
    bool operator!=(const Edge o);

  private:
    string _source;
    string _destination;
    double _weight;
    Node  *_sourceNode;
    Node  *_destinationNode;
};

typedef vector<Edge*> Edges;

#endif // __DATA_MODULE_EDGE_H__
