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


#ifndef __XSD_GRAPH_LINK_H__
#define __XSD_GRAPH_LINK_H__

class XsdGraphNode;

#include "XsdGraphNode.h"

class XsdGraphLink
{
  public:
    XsdGraphLink();
    string label();
    void   setLabel(string label);

    XsdGraphNode* source();
    XsdGraphNode* destination();
    string        destinationName();
    void          setDestinationName(string dName);
    void          setSource(XsdGraphNode *source);
    void          setDestination(XsdGraphNode *destination);

  private:
    XsdGraphNode *_source;
    XsdGraphNode *_destination;
    string        _label;
    string        _destinationName;
};

#endif // __XSD_GRAPH_LINK_H__
