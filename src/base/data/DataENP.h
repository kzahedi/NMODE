/*************************************************************************
 *                                                                       *
 * This file is part of Evolution of Neural Pathways (ENP).              *
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



#ifndef __DATA_ENP_H__
#define __DATA_ENP_H__

#include "DataNode.h"
#include "Version.h"

#include "DataEvolution.h"
#include "DataConfiguration.h"
#include "DataSimulator.h"
#include "DataPopulation.h"

# define TAG_ENP                        (char*)"enp"
# define TAG_ENP_DEFINITION             (char*)"enp_definition"
# define TAG_VERSION_REGULAR_EXPRESSION (char*)"[0-9]+.[0-9]+.[0-9]+"

class DataENP : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataENP(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataENP();

    Version version();
    void setVersion(Version version);

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    DataSimulator     *simulator();
    DataEvolution     *evolution();
    DataConfiguration *configuration();

  private:
    void __getChild(DataParseElement *element);

    Version            _version;
    DataSimulator     *_simulator;
    DataEvolution     *_evolution;
    DataConfiguration *_configuration;
    DataPopulation    *_population;

};

#endif // ___DATA_ENP_H__


