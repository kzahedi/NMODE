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


#include "XsdGraphvizExporter.h"

#include "base/FileSystemOperations.h"

class Pair
{
  public:
    Pair(string p, string n, bool rl = true, int d = -1, string f = "")
    {
      parent   = p;
      name     = n;
      depth    = d;
      lr       = rl;
      if(f == "")
      {
        stringstream oss;
        oss << p << "_" << n;
        filename = oss.str();
      }
      else
      {
        filename = f;
      }
    }

    string parent;
    string name;
    string filename;
    int    depth;
    bool   lr;
};

void XsdGraphvizExporter::writeDotFile(string filetype)
{

  cout << "Exporting to ./" << filetype << endl;

  std::vector<Pair*> name;

  name.push_back(new   Pair( (char*)"rosiml",      (char*)"robot",     true,   2));
  name.push_back(new   Pair( (char*)"rosiml",      (char*)"simulator"));
  name.push_back(new   Pair( (char*)"rosiml",      (char*)"logging"));
  name.push_back(new   Pair( (char*)"rosiml",      (char*)"traces"));
  name.push_back(new   Pair( (char*)"rosiml",      (char*)"screens",     true,   -1));
  name.push_back(new   Pair( (char*)"rosiml",      (char*)"macros",      true,   3));

  name.push_back(new   Pair( (char*)"screens",     (char*)"screen"));
  name.push_back(new   Pair( (char*)"screens",     (char*)"sky"));
  name.push_back(new   Pair( (char*)"screens",     (char*)"followables"));
  name.push_back(new   Pair( (char*)"screens",     (char*)"shadow"));
  name.push_back(new   Pair( (char*)"screens",     (char*)"cameras",     true));

  name.push_back(new   Pair( (char*)"traces",      (char*)"trace"));

  name.push_back(new   Pair( (char*)"rosiml",      (char*)"environment", true,   2));
  name.push_back(new   Pair( (char*)"environment", (char*)"ground"));
  name.push_back(new   Pair( (char*)"environment", (char*)"lightSource"));
  name.push_back(new   Pair( (char*)"environment", (char*)"macro"));

  name.push_back(new   Pair( (char*)"robot",     (char*)"sensors",     true,   2));
  name.push_back(new   Pair( (char*)"robot",     (char*)"actuators",   true,   2));
  name.push_back(new   Pair( (char*)"robot",     (char*)"controller"));
  name.push_back(new   Pair( (char*)"body",        (char*)"box"));
  name.push_back(new   Pair( (char*)"body",        (char*)"capsule"));
  name.push_back(new   Pair( (char*)"body",        (char*)"cylinder"));
  name.push_back(new   Pair( (char*)"body",        (char*)"sphere"));
  name.push_back(new   Pair( (char*)"body",        (char*)"mesh"));

  name.push_back(new   Pair( (char*)"sensors",     (char*)"proximity"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"camera"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"ambientLight"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"internalEnergy"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"orientation"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"position"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"lightDependentResistor"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"sharpDM2Y3A003K0F"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"sharpGP2D12_37"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"feedback"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"velocity"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"deflection"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"signal"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"binaryContact"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"generic", true, -1, "sensors_generic"));

  name.push_back(new   Pair( (char*)"sensors",     (char*)"proximity"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"camera"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"ambientLight"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"internalEnergy"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"lightDependentResistor"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"sharpDM2Y3A003K0F"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"sharpGP2D12_37"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"feedback"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"velocity"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"deflection"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"signal"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"binaryContact"));
  name.push_back(new   Pair( (char*)"sensors",     (char*)"universal", true, -1, "sensors_universal"));

  name.push_back(new   Pair( (char*)"logging",     (char*)"console", true, -1, "logging_console"));
  name.push_back(new   Pair( (char*)"logging",     (char*)"gnuplot", true, -1, "logging_gnuplot"));
  name.push_back(new   Pair( (char*)"logging",     (char*)"selforg", true, -1, "logging_selforg"));
  name.push_back(new   Pair( (char*)"logging",     (char*)"matrixviz", true, -1, "logging_matrixviz"));
  name.push_back(new   Pair( (char*)"logging",     (char*)"object", true, -1, "logging_object"));
  name.push_back(new   Pair( (char*)"logging",     (char*)"actuator", true, -1, "logging_actuator"));
  name.push_back(new   Pair( (char*)"logging",     (char*)"sensor", true, -1, "logging_sensor"));
  name.push_back(new   Pair( (char*)"logging",     (char*)"controller", true, -1, "logging_controller"));

  name.push_back(new   Pair( (char*)"actuators",   (char*)"hinge"));
  name.push_back(new   Pair( (char*)"actuators",   (char*)"slider"));
  name.push_back(new   Pair( (char*)"actuators",   (char*)"generic", true, -1, "actuators_generic"));

  name.push_back(new   Pair( (char*)"hinge",       (char*)"noise"));
  name.push_back(new   Pair( (char*)"hinge",       (char*)"filter"));

  name.push_back(new   Pair( (char*)"signals",     (char*)"keyboard"));
  name.push_back(new   Pair( (char*)"signals",     (char*)"periodic"));
  name.push_back(new   Pair( (char*)"signals",     (char*)"triggered"));

  name.push_back(new   Pair( "",                   (char*)"rosiml",      true,   3));
  name.push_back(new   Pair( "",                   (char*)"rosiml",      true,  -1, "rosiml_complete"));

  XsdGraphvizGenerator *xsd = new XsdGraphvizGenerator();

  stringstream dir;
  dir << "./" << filetype;
  fs::path dotDir = "./dot";
  fs::path exportDir = dir.str();


  if(!fs::exists(dotDir))    fs::create_directory(dotDir);
  if(!fs::exists(exportDir)) fs::create_directory(exportDir);

  ofstream myfile;

  stringstream filename;
  for(std::vector<Pair*>::iterator i = name.begin(); i != name.end(); i++)
  {
    filename.str("");
    if((*i)->filename.length() == 0) filename << "./dot/" << (*i)->name     << ".dot";
    else                             filename << "./dot/" << (*i)->filename << ".dot";
    xsd->generate((*i)->parent, (*i)->name, (*i)->lr, (*i)->depth);
    myfile.open(filename.str().c_str());
    myfile << (*xsd) << endl;
    myfile.close();
    cout << "writing " << filename.str() << endl;
  }

  if (FileSystemOperations::doesExecutableExist(filetype))
  {
    cout << "Found dot executable. Exporting dot -> " << filetype << endl;
    stringstream oss;
    for(std::vector<Pair*>::iterator i = name.begin(); i != name.end(); i++)
    {
      oss.str("");
      filename.str("");
      if((*i)->filename.length() == 0) filename << "./dot/" << (*i)->name     << ".dot";
      else                             filename << "./dot/" << (*i)->filename << ".dot";
      oss << "dot -T" << filetype << " " << filename.str() << " -o ";
      // oss << "twopi -T" << filetype << " " << filename.str() << " -o ";
      filename.str("");
      if((*i)->filename.length() == 0) filename << filetype << "/" << (*i)->name << "." << filetype;
      else                             filename << filetype << "/" << (*i)->filename << "." << filetype;
      oss << filename.str();
      system(oss.str().c_str());
      cout << oss. str() << endl;
    }
  }
  else
  {
    cout << "Cannot find dot executable." << endl;
  }

  cout << "done." << endl;
}
