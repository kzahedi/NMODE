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


#include "XsdElementGraphNode.h"

#include "nmode/macros.h"

#include <iostream>

using namespace std;

XsdElementGraphNode::XsdElementGraphNode(XsdElement *spec)
{
  _spec = spec;
}

string XsdElementGraphNode::customLabel(string label)
{
  _oss.str("");
  _oss << " [label=<";
  _oss << "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" cellpadding=\"0\">";
  _oss << "<tr><td>";
  _oss << "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">";
  _oss << "<tr><td colspan=\"2\" bgcolor=\"" << ELEMENT_BGCOLOR << "\">"<< label << "</td></tr>";
  if(_spec->type().length() > 0)
  {
    _oss << "<tr><td colspan=\"2\" bgcolor=\"" << ELEMENT_BGCOLOR << "\">"<< _spec->type() << "</td></tr>";
  }
  int attributeDefinitionIndex = 1;
  FORF(vector<XsdAttribute*>, a, _spec, a_begin(), a_end())
  {
    _oss << "<tr><td rowspan=\"2\" bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\">"<< (*a)->name() << "</td>";
    if((*a)->required())
    {
      _oss << "<td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\"> <font color=\"" << REQUIRED_COLOR << "\"> required </font> </td>";
    }
    else
    {
      _oss << "<td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\"> <font color=\"" << OPTIONAL_COLOR << "\"> optional </font> </td>";
    }
    _oss << "</tr>";
    if(!hasDefinition((*a)->type()))
    {
      _oss << "<tr><td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\">"<< (*a)->type() << "</td></tr>";
    }
    else
    {
      _oss << "<tr><td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\"> see #" << attributeDefinitionIndex++ << " </td></tr>";
    }
  }

  _oss << "</table>";
  _oss << "</td>";

  int portIndex = 0;
  stringstream oss_2;
  FORF(vector<XsdAttribute*>, a, _spec, a_begin(), a_end())
  {
    if(hasDefinition((*a)->type()))
    {
      oss_2 << "<tr><td port=\"" << portIndex << "\" bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\">#" << portIndex+1 << "</td></tr>";
      portIndex++;
    }
  }


  if(oss_2.str().length() > 0)
  {
    _oss << "<td><table border=\"0\" cellborder=\"1\" cellspacing=\"0\">";
    _oss << oss_2.str();
    _oss << "</table></td>";
  }

  _oss << "</tr>";
  _oss << "</table>";
  _oss << ">];";
  return _oss.str();
}

string XsdElementGraphNode::name()
{
  return _spec->name();
}

XsdElement* XsdElementGraphNode::spec()
{
  return _spec;
}

