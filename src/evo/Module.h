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



#ifndef __MODULE_H__
#define __MODULE_H__

#include "Node.h"

class Module
{
  public:
    Module(string name);
    ~Module();

    //Module(const Module);
    //Module operator=(const Module);

    bool operator==(const Module m);
    bool operator!=(const Module m);

    void addNode(Node *neuron) throw (ENPException);
    string name();

    bool linked();
    void linkTo(Module *target);

    bool removeEdge(Edge *e);
    void addEdge(Node *src, Node *dst, double weight) throw (ENPException);

    Node*           node(int index);
    Nodes::iterator n_begin();
    Nodes::iterator n_end();
    int             n_size();
    int             s_size(); // number of sensor nodes
    int             a_size(); // number of actuator nodes
    int             h_size(); // number of hidden nodes

    Edges::iterator e_begin();
    Edges::iterator e_end();
    int             e_size();
    Edge*           edge(int index);

    friend std::ostream& operator<<(std::ostream& str, const Module& m)
    {
      str << "Module: " << m._name << endl;
      str << "  Nodes: " << endl;
      for(Nodes::const_iterator n = m._nodes.begin(); n != m._nodes.end(); n++)
      {
        str << "    [" << (*n)->label()            << ", "
                       << (*n)->type()             << ", "
                       << (*n)->position()         << ", "
                       << (*n)->transferfunction() << ", "
                       << (*n)->value()            << "]";
      }
      str << "  Edges: " << endl;
      for(Edges::const_iterator e = m._edges.begin(); e != m._edges.end(); e++)
      {
        str << "    [" << (*e)->source()->label()      << " -> "
                       << (*e)->destination()->label() << ": "
                       << (*e)->weight()               << "]";
      }
      return str;
    };

  private:
    Nodes   _nodes;
    Nodes   _sensors;
    Nodes   _actuators;
    Nodes   _hidden;
    Edges   _edges;
    string  _name;
    bool    _linked;
    Module *_target;
};

#endif // __MODULE_H__

