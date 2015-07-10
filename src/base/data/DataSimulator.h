/*************************************************************************
 *                                                                       *
 * This file is part of Simulator of Neural Pathways (ENP).              *
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



#ifndef __DATA_SIMULATOR_H__
#define __DATA_SIMULATOR_H__

#include "DataXsdNode.h"

# define TAG_SIMULATOR            (char*)"simulator"
# define TAG_SIMULATOR_DEFINITION (char*)"simulator_definition"

class DataSimulator : public DataXsdNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataSimulator(DataXsdNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataSimulator();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    string workingDirectory();
    string xml();
    int    nr();

  private:

    string _workingDirectory;
    string _xml;
    int    _nr;

};

#endif // ___DATA_SIMULATOR_H__


