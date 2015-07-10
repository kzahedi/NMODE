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



#include "Data.h"

#include "base/xsd/parser/YarsXSDSaxParser.h"
#include "base/data/XmlChangeLog.h"

#include <glog/logging.h>

Data* Data::_me = NULL;

Data* Data::instance()
{
  if(_me == NULL)
  {
    _me = new Data();
  }
  return _me;
}

Data::Data()
{
  _root = new DataENP(NULL);
}

Data::~Data()
{
  delete _root;
}

DataENP* Data::specification()
{
  return _root;
}

void Data::clear()
{
}

void Data::close()
{
  // if(_me != NULL) delete _me;
}

void Data::read(string xmlFile)
{
  YarsXSDSaxParser *parser = new YarsXSDSaxParser();
  parser->read(xmlFile);
  if(parser->errors() > 0)
  {
    for(std::vector<string>::iterator i = parser->w_begin(); i != parser->w_end(); i++) cout << "WARNING: " << *i << endl;
    for(std::vector<string>::iterator i = parser->e_begin(); i != parser->e_end(); i++) cout << "ERROR: " << *i << endl;
    for(std::vector<string>::iterator i = parser->f_begin(); i != parser->f_end(); i++) cout << "FATAL: " << *i << endl;
    delete parser;
    exit(-1);
  }
  delete parser;
}

XsdSpecification* Data::xsd()
{
  XsdSpecification *spec = new XsdSpecification();
  DataENP::createXsd(spec);
  return spec;
}

string Data::header()
{
  stringstream sst;

#define SIM  _root->simulator()
#define EVON _root->evolution()->node()
#define EVOE _root->evolution()->edge()

  sst << "<?xml version=\"1.0\"?>" << endl << endl;
  sst << "<enp version=\""     << XmlChangeLog::version() << "\">" << endl;
  sst << "  <simulator wd=\""  << SIM->workingDirectory() <<  "\"" << endl;
  sst << "             xml=\"" << SIM->xml() << "\"" << endl;
  sst << "             nr=\""  << SIM->nr() << "\"/>" << endl;

  sst << "  <evolution>" << endl;
  sst << "    <node cost=\"" << EVON->cost() << "\">" << endl;
  sst << "      <modify probability=\"" << EVON->modifyProbability() << "\" "
    << "maximum=\"" << EVON->modifyMaxValue() << "\" "
    << "delta=\""   << EVON->modifyDelta() << "\"/>" << endl;
  sst << "      <add    probability=\"" << EVON->addProbability() << "\" "
    << "maximum=\"" << EVON->addMaxValue() << "\"/>" << endl;
  sst << "      <delete probability=\"" << EVON->delProbability() << "\"/>" << endl;
  sst << "    </node>" << endl;
  sst << "    <edge cost=\"" << EVOE->cost() << "\">" << endl;
  sst << "      <modify probability=\"" << EVON->modifyProbability() << "\" "
    << "maximum=\"" << EVOE->modifyMaxValue() << "\" "
    << "delta=\""   << EVOE->modifyDelta() << "\"/>" << endl;
  sst << "      <add    probability=\"" << EVOE->addProbability() << "\" "
    << "maximum=\"" << EVOE->addMaxValue() << "\"/>" << endl;
  sst << "      <delete probability=\"" << EVOE->delProbability() << "\"/>" << endl;
  sst << "    </edge>" << endl;
  sst << "  </evolution>" << endl;

  sst << "  <configuration>" << endl;

  for(DataModules::iterator
      m = _root->configuration()->m_begin();
      m != _root->configuration()->m_end();
      m++)
  {

    sst << "    <module name=\"" << (*m)->name() << "\">" << endl;

    for(DataNodes::iterator n = (*m)->n_begin(); n != (*m)->n_end(); n++)
    {
      sst << "      <node type=\"" << (*n)->type() << "\" label=\"" << (*n)->label() << "\">" << endl;
      sst << "        <position x=\"" << (*n)->position().x
        << "\" y=\"" << (*n)->position().y << "\" z=\"" << (*n)->position().z << "\"/>" << endl;
      sst << "        <transferfunction name=\"" << (*n)->transferfunction() << "\"/>" << endl;
      sst << "      </node>" << endl;
    }
    sst << "    </module>" << endl;
  }
  sst << "  </configuration>" << endl;
  return sst.str();
}

string Data::footer()
{
  stringstream sst;
  sst << "</enp>" << endl;
  return sst.str();
}
