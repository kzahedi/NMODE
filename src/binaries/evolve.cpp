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



#include "base/Configuration.h"
#include "base/data/Data.h"

#include <glog/logging.h>

#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
  FLAGS_alsologtostderr = 1;
  FLAGS_log_dir = ".";

  google::InitGoogleLogging(argv[0]);
  Configuration *configuration = new Configuration(argc, argv, true);

  Data *data = Data::instance();

  LOG_IF(INFO, configuration->input().size() > 0) 
    << "Input file given " << configuration->input();
  LOG_IF(INFO, configuration->output().size() > 0)
    << "Output file given " << configuration->output();
  LOG_IF(INFO, configuration->cfg().size() > 0)
    << "Configuration given " << configuration->cfg();

  VLOG(5) << "reading file " << configuration->cfg();
  data->read(configuration->cfg());

  VLOG(5) << "done.";
  return 0;
}
