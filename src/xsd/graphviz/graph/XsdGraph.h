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


#ifndef __YARS_XSD_GRAPH_H__
#define __YARS_XSD_GRAPH_H__

#include "XsdGraphNode.h"
#include "XsdGraphNodeInstance.h"
#include "XsdGraphLink.h"

#include <ostream>
#include <sstream>

using namespace std;

class XsdGraph
{
  public:
    XsdGraph();
    ~XsdGraph();

    XsdGraphNodeInstance* get(string parent, string name);

    std::vector<XsdGraphNodeInstance*>::iterator i_begin();
    std::vector<XsdGraphNodeInstance*>::iterator i_end();

  private:
    void __createGraph();
    void __add(XsdSequence          *seq);
    void __add(XsdChoice            *choice);
    void __add(XsdEnumeration       *enumeration);
    void __add(XsdInterval          *interval);
    void __add(XsdRegularExpression *regexp);

    void __add(XsdGraphNodeInstance *parent, XsdNode              *node);
    void __add(XsdGraphNodeInstance *parent, XsdElement           *element);
    void __add(XsdGraphNodeInstance *parent, XsdAttribute         *attribute);
    void __add(XsdGraphNodeInstance *parent, XsdSequence          *node);
    void __add(XsdGraphNodeInstance *parent, XsdChoice            *node);
    void __add(XsdGraphNodeInstance *parent, XsdRegularExpression *node);
    void __add(XsdGraphNodeInstance *parent, XsdInterval          *node);
    void __add(XsdGraphNodeInstance *parent, XsdEnumeration       *node);

    XsdGraphNode* __findNode(string          name);

    XsdGraphNodeInstance *_root;
    XsdSpecification     *_spec;

    std::vector<XsdGraphNode*>         _nodes;
    std::vector<XsdGraphNodeInstance*> _instances;
};

#endif // __YARS_XSD_GRAPH_H__
