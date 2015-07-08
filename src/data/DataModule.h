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



#ifndef __DATA_MODULE_H__
#define __DATA_MODULE_H__

#include "DataNode.h"

#include "DataModuleNode.h"

# define TAG_MODULE            (char*)"module"
# define TAG_MODULE_DEFINITION (char*)"module_definition"

class DataModule : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataModule(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataModule();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    DataModuleNodes nodes();

    string name();

  private:
    string _name;

    DataModuleNodes _nodes;
};

typedef vector<DataModule*> DataModules;

#endif // ___DATA_MODULE_H__


