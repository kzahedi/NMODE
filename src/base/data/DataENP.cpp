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



#include "DataENP.h"
#include "XmlChangeLog.h"

#include "base/StringTokeniser.h"
#include "base/ENPErrorHandler.h"

#include <iostream>
#include <glog/logging.h>

using namespace std;

# define TAG_VERSION            (char*)"version"
# define TAG_VERSION_DEFINITION (char*)"version_definition"

DataENP::DataENP(DataNode *parent)
  : DataNode(parent)
{

#include "ChangeLog.h" // do not move from here
  
  _evolution     = NULL;
  _configuration = NULL;
  _simulator     = NULL;
  _population    = NULL;

}

DataENP::~DataENP()
{
  // nothing to be done
}


void DataENP::add(DataParseElement *element)
{
  if(current == NULL) current = this;
  if(current == this)
  {
    __getChild(element);
  }
  else
  {
    current->add(element);
  }

}

Version DataENP::version()
{
  return _version;
}

void DataENP::setVersion(Version version)
{
  _version = version;
}

void DataENP::createXsd(XsdSpecification *spec)
{
  XsdSequence *_root = new XsdSequence(TAG_ENP);
  _root->add(NA(TAG_VERSION,       TAG_VERSION_DEFINITION,       true));
  _root->add(NE(TAG_SIMULATOR,     TAG_SIMULATOR_DEFINITION,     1, 1));
  _root->add(NE(TAG_EVOLUTION,     TAG_EVOLUTION_DEFINITION,     1, 1));
  _root->add(NE(TAG_CONFIGURATION, TAG_CONFIGURATION_DEFINITION, 1, 1));
  _root->add(NE(TAG_POPULATION,    TAG_POPULATION_DEFINITION   , 0, 1));
  spec->setRoot(_root);

  XsdRegularExpression *versionDefinition =
    new XsdRegularExpression(TAG_VERSION_DEFINITION,
        TAG_XSD_STRING, TAG_VERSION_REGULAR_EXPRESSION);
  spec->add(versionDefinition);

  DataEvolution::createXsd(spec);
  DataConfiguration::createXsd(spec);
  DataPopulation::createXsd(spec);
}


void DataENP::__getChild(DataParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->opening(TAG_ENP))
  {
    string v;
    element->set(TAG_VERSION, v);
    std::vector<string> vs = StringTokeniser::tokenise(v, ".");
    _version.major = atoi(vs[0].c_str());
    _version.minor = atoi(vs[1].c_str());
    _version.patch = atoi(vs[2].c_str());
    if(_version > XmlChangeLog::version())
    {
      ENPErrorHandler *e = ENPErrorHandler::instance();
      (*e).precision(1);
      (*e).setf(ios::fixed,ios::floatfield);
      (*e) << "XML version mismatch. The given XML is of version ";
      (*e) << _version << " but this enp binary only supports XML version ";
      (*e) << XmlChangeLog::version() << endl;
      (*e).unsetf(ios::floatfield);
      ENPErrorHandler::push();
      exit(-1);
    }
    if(_version < XmlChangeLog::version() && _version < XmlChangeLog::last_crucial_change())
    {
      ENPErrorHandler *e = ENPErrorHandler::instance();
      (*e).precision(1);
      (*e).setf(ios::fixed,ios::floatfield);
      (*e) << "XML version mismatch" << endl;
      (*e) << "Showing differences from your XML’s version ";
      (*e) << _version << " to the current version ";
      (*e) << XmlChangeLog::version() << ":" << endl;
      (*e) << XmlChangeLog::changes(_version);
      (*e).unsetf(ios::floatfield);
      ENPErrorHandler::push();
      exit(-1);
    }
    else if(_version < XmlChangeLog::version())
    {
      cout.precision(1);
      cout.setf(ios::fixed,ios::floatfield);
      cout << "Non-critical XML version mismatch" << endl;
      cout << "Showing differences from your XML’s version ";
      cout << _version << " to the current version ";
      cout << XmlChangeLog::version() << ":" << endl;
      cout << XmlChangeLog::changes(_version);
      cout.unsetf(ios::floatfield);
    }
    return;
  }

  if(element->opening(TAG_EVOLUTION))
  {
    _evolution = new DataEvolution(this);
    current = _evolution;
    current->add(element);
  }

  if(element->opening(TAG_CONFIGURATION))
  {
    _configuration = new DataConfiguration(this);
    current = _configuration;
    current->add(element);
  }

  if(element->opening(TAG_SIMULATOR))
  {
    _simulator = new DataSimulator(this);
    current = _simulator;
    current->add(element);
  }

  if(element->opening(TAG_POPULATION))
  {
    VLOG(100) << "Found tag: " << TAG_POPULATION;
    _population = new DataPopulation(this);
    current = _population;
    current->add(element);
  }

}

DataEvolution* DataENP::evolution()
{
  return _evolution;
}

DataConfiguration* DataENP::configuration()
{
  return _configuration;
}

DataSimulator* DataENP::simulator()
{
  return _simulator;
}

