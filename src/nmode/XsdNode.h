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


#ifndef __XSD_NODE_H__
#define __XSD_NODE_H__

# define XSD_NODE_TYPE_SEQUENCE    0
# define XSD_NODE_TYPE_ELEMENT     1
# define XSD_NODE_TYPE_CHOICE      2
# define XSD_NODE_TYPE_REG_EXP     3
# define XSD_NODE_TYPE_INTERVAL    4
# define XSD_NODE_TYPE_ATTRIBUTE   5
# define XSD_NODE_TYPE_ENUMERATION 6

#include <string>

using namespace std;

class XsdNode
{
  public:
    XsdNode(int nodeType);
    ~XsdNode();

    int    nodeType();
    void   setComment(string comment);
    string comment();
    virtual string name() = 0;

  private:
    int    _nodeType;
    string _comment;
};

#endif // __XSD_NODE_H__


