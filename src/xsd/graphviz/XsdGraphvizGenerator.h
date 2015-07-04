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


#ifndef __YARS_XSD_GRAPHVIZ_GENERATOR_H__
#define __YARS_XSD_GRAPHVIZ_GENERATOR_H__

#include "xsd/graphviz/graph/XsdGraph.h"

#include <sstream>

using namespace std;

class XsdGraphvizGenerator
{
  public:
    XsdGraphvizGenerator();

    void generate(string parent, string name, bool leftToRight, int depth);

    friend std::ostream& operator<<(std::ostream& str, XsdGraphvizGenerator& g)
    {
      str << g._dot.str() << endl;
      return str;
    };

  private:
    void __generate(XsdGraphNodeInstance *node, int depth);

    stringstream  _dot;
    XsdGraph     *_graph;
};

#endif // __YARS_XSD_GRAPHVIZ_GENERATOR_H__
