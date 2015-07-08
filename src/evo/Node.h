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



#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <string>
#include <ostream>

#include "base/P3D.h"
#include "base/ENPException.h"

#include "Edge.h"

#define NODE_TYPE_SENSOR   1001
#define NODE_TYPE_ACTUATOR 1002
#define NODE_TYPE_HIDDEN   1003

using namespace std;

class Node
{
  public:
    Node();
    ~Node();

    //Node(const Node);
    //Node operator=(const Node);
    bool operator==(const Node o);
    bool operator!=(const Node o);

    void setPosition(P3D position);
    void setType(string type) throw (ENPException);
    void setLabel(string label);
    void setTransferfunction(string tf);

    P3D    position();
    int    type();
    string label();
    string transferfunction();
    bool   contains(Edge *e);
    bool   contains(Node *n);

    void   removeEdge(Node *src);

    Edges::iterator e_begin();
    Edges::iterator e_end();
    int             e_size();
    Edge*           edge(int index);

    void   setValue(double v);
    double value();

    void addEdge(Edge *e);
    bool removeEdge(Edge *e);

    friend std::ostream& operator<<(std::ostream& str, const Node& n)
    {
      str << n._label << ", " << n._type << ", " << n._position << ", " << n._transferfunction;
      return str;
    };


  private:

    P3D    _position;
    int    _type;
    double _value;
    string _label;
    string _transferfunction;
    Edges  _in;
};

typedef vector<Node*> Nodes;

#endif // __NODE_H__

