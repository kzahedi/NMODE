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


#include "XsdGraphvizGenerator.h"

#include "base/xsd/graphviz/graph/XsdGraphNodeInstance.h"

#include "base/macros.h"

#include <vector>
#include <iostream>

XsdGraphvizGenerator::XsdGraphvizGenerator()
{
  _graph = new XsdGraph();
}

void XsdGraphvizGenerator::generate(string parent, string name, bool leftToRight, int depth)
{
  _dot.str("");
  _dot << "digraph structs {"         << endl;
  if(leftToRight)
  {
    _dot << "  rankdir=LR;"             << endl;
    // _dot << "  layout=circo;"             << endl;
    // _dot << " ranksep=5;"<< endl << "  ratio=auto;"             << endl;
    // _dot << " outputMode=\"edgesfirst\";" << endl;

  }
  else
  {
    _dot << "  rankdir=TB;"             << endl;
  }
  //_dot << "  ranksep=\"equally\";"    << endl;
  _dot << "  node [shape=plaintext];" << endl;

  XsdGraphNodeInstance *node = _graph->get(parent, name);
  __generate(node, depth);

  _dot << "}" << endl;
}

void XsdGraphvizGenerator::__generate(XsdGraphNodeInstance *node, int depth)
{
  if(depth == 0) return;
  int d = depth - 1;
  _dot << " " << node->uniqueName() << " " << node->label() << endl;
  if(d != 0)
  {
    FORP(vector<XsdGraphNodeInstance*>, i, node)
    {
      __generate(*i, d);
      _dot << node->uniqueName() << ":" << (*i)->port() << " -> " << (*i)->uniqueName() << ";" << endl;
    }
  }
}
