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



#ifndef __DATA_NODE_H__
#define __DATA_NODE_H__

#include "DataParseElement.h"
#include "base/xsd/specification/specification.h"

#include <string>
#include <ostream>
#include <iostream>

# define DIV "_"
# define DEF "definition"


using namespace std;

/**
 * @brief Basic class for all objects that store XML data.
 */
class DataNode
{
  public:

    /**
     * @brief Default constructor. Takes parent node as parameter
     *
     * @param parent
     */
    DataNode(DataNode *parent);

    /**
     * @brief Destructor, does nothing
     */
    ~DataNode();

    /**
     * @brief This function must be implemented by every data storing class. It
     * takes a DataParseElement and should decide if the contained data is
     * either stored, passed on to a child, or if the current node is set to the
     * parent.
     *
     * @param DataParseElement
     * @sa DataParseElement
     */
    virtual void add(DataParseElement* ) = 0;

  protected:
    DataNode        *parent;
    static DataNode *current;
};

#endif // __DATA_NODE_H__
