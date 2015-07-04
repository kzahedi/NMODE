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


#ifndef __YARS_XSD_ELEMENT_H__
#define __YARS_XSD_ELEMENT_H__

#include "XsdNode.h"
#include "XsdAttribute.h"

#include <string>
#include <vector>

# define YARS_STRING_XSD_UNBOUNDED (char*)"unbounded"

using namespace std;

class XsdElement : public XsdNode
{
  public:
    XsdElement();
    XsdElement(string name, string type, int minOccurs);
    XsdElement(string name, string type, int minOccurs, int maxOccurs);
    XsdElement(string name, string type, string minOccurs = "", string maxOccurs = "");
    XsdElement(string name, string type, int minOccurs, string maxOccurs);
    void setName(string name);
    void setType(string type);
    void setMinOccurs(string minOccurs);
    void setMinOccurs(int minOccurs);
    void setMaxOccurs(string maxOccurs);
    void setMaxOccurs(int maxOccurs);

    string name();
    string type();

    string minOccurs();
    bool   minOccursGiven();
    string maxOccurs();
    bool   maxOccursGiven();

    void   add(XsdAttribute *attribute);
    std::vector<XsdAttribute*>::iterator a_begin();
    std::vector<XsdAttribute*>::iterator a_end();
    int a_size();

  private:
    string _name;
    string _type;
    string _minOccurs;
    string _maxOccurs;
    bool   _minOccursGiven;
    bool   _maxOccursGiven;
    std::vector<XsdAttribute*> _attributes;
};

#endif // __YARS_XSD_ELEMENT_H__


