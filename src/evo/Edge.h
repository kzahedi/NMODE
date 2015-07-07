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



#ifndef __EDGE_H__
#define __EDGE_H__

#include <vector>
#include <string>
#include <ostream>

#include "base/P3D.h"

#define EDGE_TYPE_SENSOR   1001
#define EDGE_TYPE_ACTUATOR 1002
#define EDGE_TYPE_HIDDEN   1003

using namespace std;

class Node;

class Edge
{
  public:
    Edge();
    ~Edge();

    //Edge(const Edge);
    //Edge operator=(const Edge);
    // bool operator==(const Edge o);
    // bool operator!=(const Edge o);

    void setSource(Node *src);
    void setDestination(Node *dest);
    void setWeight(double weight);

    Node* source();
    Node* destination();
    double      weight();

  private:

    Node  *_src;
    Node  *_dest;
    double _weight;
};

typedef vector<Edge*> Edges;

#endif // __EDGE_H__

