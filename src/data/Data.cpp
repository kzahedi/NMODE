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

#include "xsd/parser/YarsXSDSaxParser.h"

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
  _spec = new DataENP(NULL);
}

Data::~Data()
{
  delete _spec;
}

DataENP* Data::specification()
{
  return _spec;
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
  cout << "reading xmlFile: " << xmlFile << endl;
  YarsXSDSaxParser *parser = new YarsXSDSaxParser();
  // TODO parser should add new xml files to current data-structure (might already be the case?)
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
