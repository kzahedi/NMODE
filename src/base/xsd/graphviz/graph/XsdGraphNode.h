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


#ifndef __YARS_XSD_GRAPH_NODE_H__
#define __YARS_XSD_GRAPH_NODE_H__

#include "base/xsd/specification/XsdSpecification.h"

#include <string>
#include <vector>

#define ATTRIBUTE_BGCOLOR     "#fee1b7"
#define ELEMENT_BGCOLOR       "#adc9f0"
#define CHOICE_BGCOLOR        "#adf0ad"
#define SPECIFICATION_BGCOLOR "#fefeb7"

#define REGEXP_BGCOLOR        "#f3afd7"
#define INTERVAL_BGCOLOR      "#d9adf0"
#define ENUM_BGCOLOR          "#b8adf0"

#define OPTIONAL_COLOR        "#00A000"
#define REQUIRED_COLOR        "#ff0000"

using namespace std;

class XsdGraphNode
{
  public:
    XsdGraphNode();
    virtual ~XsdGraphNode() { };

    virtual string   customLabel(string label) = 0;
    virtual string   name()                    = 0;
    virtual XsdNode* spec()                    = 0;

    string uniqueNodeName();
    void   setUniqueNodeName(string n);
    bool   hasDefinition(string type);

  private:
    string            _uniqueName;
};

#endif // __YARS_XSD_GRAPH_NODE_H__
