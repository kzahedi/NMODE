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


#include "XsdIntervalGraphNode.h"

#include "base/macros.h"

XsdIntervalGraphNode::XsdIntervalGraphNode(XsdInterval *spec)
{
  _spec = spec;

  _type = "interval";
  _oss << "<tr> <td bgcolor=\"" << SPECIFICATION_BGCOLOR << "\"> min:  " << spec->minimum() << " </td> </tr>";
  _oss << "<tr> <td bgcolor=\"" << SPECIFICATION_BGCOLOR << "\"> max:  " << spec->maximum() << " </td> </tr>";
  _oss << "<tr> <td bgcolor=\"" << SPECIFICATION_BGCOLOR << "\"> type: " << spec->type() << " </td> </tr>";
  _specification = _oss.str();
}

string XsdIntervalGraphNode::customLabel(string label)
{
  _oss.str("");
  _oss << " [label=<";
  _oss << "<table bgcolor=\"" << INTERVAL_BGCOLOR << "\" border=\"0\" cellborder=\"1\" cellspacing=\"0\" cellpadding=\"0\">";
  _oss << "<tr><td> " << label  << "</td></tr>"; //<< "&nbsp;:&nbsp;" << _type << "</td></tr>";
  _oss << _specification;
  _oss << "</table>";
  _oss << ">];";
  return _oss.str();
}

string XsdIntervalGraphNode::name()
{
  return _spec->name();
}

XsdInterval* XsdIntervalGraphNode::spec()
{
  return _spec;
}