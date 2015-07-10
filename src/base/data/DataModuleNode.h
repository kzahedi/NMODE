/*************************************************************************
 *                                                                       *
 * This file is part of Module of Neural Pathways (ENP).              *
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



#ifndef __DATA_MODULE_NODE_H__
#define __DATA_MODULE_NODE_H__

#include "DataNode.h"

#include "base/P3D.h"

# define TAG_MODULE_NODE            (char*)"node"
# define TAG_MODULE_NODE_DEFINITION (char*)"module_node_definition"

class DataModuleNode : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataModuleNode(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataModuleNode();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    string type();
    string label();
    P3D    position();
    string transferfunction();

  private:
    string _type;
    string _label;
    P3D    _position;
    string _transferfunction;
};

typedef vector<DataModuleNode*> DataModuleNodes;

#endif // ___DATA_MODULE_NODE_H__


