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


#include "XsdChoiceGraphNode.h"

#include "enp/macros.h"

#include <iostream>

using namespace std;

XsdChoiceGraphNode::XsdChoiceGraphNode(XsdChoice *spec)
{
  _spec       = spec;
}

string XsdChoiceGraphNode::customLabel(string label)
{
  _oss.str("");
  _oss << " [label=<";
  _oss << "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\" cellpadding=\"0\">";
  _oss << "<tr><td>";
  _oss << "<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">";
  _oss << "<tr><td colspan=\"2\" bgcolor=\"" << ELEMENT_BGCOLOR << "\">"<< label << "</td></tr>";
  FORF(vector<XsdAttribute*>, a, _spec, a_begin(), a_end())
  {
    _oss << "<tr><td rowspan=\"2\" bgcolor=\"" << ATTRIBUTE_BGCOLOR
         << "\">"<< (*a)->name() << "</td>";
    if((*a)->required())
    {
      _oss << "<td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\"> <font color=\""
           << REQUIRED_COLOR << "\"> required </font> </td>";
    }
    else
    {
      _oss << "<td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\"> <font color=\""
           << OPTIONAL_COLOR << "\"> optional </font> </td>";
    }
    _oss << "</tr>";
    if(!hasDefinition((*a)->type()))
    {
      _oss << "<tr><td bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\">"
           << (*a)->type() << "</td></tr>";
    }
    else
    {
      _oss << "<tr><td bgcolor=\"" << ATTRIBUTE_BGCOLOR
           << "\"> sd </td></tr>";
    }
  }
  _oss << "</table>";
  _oss << "</td>";

  stringstream oss_2;

  int index = 0;
  FORF(vector<XsdAttribute*>, a, _spec, a_begin(), a_end())
  {
    if(hasDefinition((*a)->type()))
    {
      oss_2 << "<tr><td port=\"" << index++ << "\" bgcolor=\"" << ATTRIBUTE_BGCOLOR << "\"></td></tr>";
    }
  }
  FORF(vector<XsdElement*>, e, _spec, e_begin(), e_end())
  {
    oss_2 << "<tr><td port=\"" << index++ << "\" bgcolor=\"" << ELEMENT_BGCOLOR << "\"></td></tr>";
  }
  FORF(vector<XsdSequence*>, s, _spec, s_begin(), s_end())
  {
    oss_2 << "<tr><td port=\"" << index++ << "\" bgcolor=\"" << ELEMENT_BGCOLOR << "\"></td></tr>";
  }

  if(oss_2.str().length() > 0)
  {
    _oss << "<td><table border=\"0\" cellborder=\"1\" cellspacing=\"0\">" << oss_2.str() << "</table></td>";
  }

  _oss << "</tr>";
  _oss << "</table>";
  _oss << ">];";
  return _oss.str();
}

string XsdChoiceGraphNode::name()
{
  return _spec->name();
}

XsdChoice* XsdChoiceGraphNode::spec()
{
  return _spec;
}
