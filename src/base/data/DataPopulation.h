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



#ifndef __DATA_POPULATION_H__
#define __DATA_POPULATION_H__

#include "DataXsdNode.h"
#include "DataIndividual.h"

# define TAG_POPULATION            (char*)"population"
# define TAG_POPULATION_DEFINITION (char*)"population_definition"

class DataPopulation : public DataXsdNode
{
  public:
    DataPopulation(DataXsdNode *parent);
    // ~DataPopulation();

    //DataPopulation(const DataPopulation);
    //DataPopulation operator=(const DataPopulation);

    void add(DataParseElement *element);
    static void createXsd(XsdSpecification *spec);

    
    DataIndividuals::iterator i_begin();
    DataIndividuals::iterator i_end();
    int                       i_size();
    DataIndividuals           individuals();

  private:

    int             _generation;
    DataIndividuals _individuals;
};

#endif // __DATA_POPULATION_H__


