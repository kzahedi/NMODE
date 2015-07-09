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

#include <string>
#include <iostream>

#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

using namespace std;

namespace po = boost::program_options;

Configuration::Configuration(int argc, char* argv[], bool io)
{
  po::options_description desc("Options");
  po::options_description ioo("Input/Output Options");
  po::options_description cmdline_options;
  
  po::variables_map vm;

  desc.add_options()
    ("help",    "print help message")
    ("cfg",     po::value<string>(&_cfg), "cfg file");

  ioo.add_options()
    ("input",  po::value<string>(&_input),  "input module")
    ("output", po::value<string>(&_output), "output module");

  po::positional_options_description positional;
  positional.add("cfg", -1);

  cmdline_options.add(desc);
  if(io == true) cmdline_options.add(ioo);

  po::store(po::command_line_parser(argc, argv).
            options(cmdline_options).
            positional(positional).
            allow_unregistered().
            run(), vm);
  po::notify(vm);

  if (vm.count("help")) {
    cout << desc << "\n";
    if(io) cout << ioo << "\n";
    exit(0);
  }

  if(vm.count("cfg") == 0)
  {
    cerr << "Please give a configuration file. See " << argv[0] << " --help for more information." << endl;
    exit(-1);
  };

}

string Configuration::input()
{
  return _input;
}

string Configuration::output()
{
  return _output;
}

string Configuration::cfg()
{
  return _cfg;
}
