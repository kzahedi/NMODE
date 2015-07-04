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


#ifndef __YARS_XSD_CHOCIE_H__
#define __YARS_XSD_CHOCIE_H__

#include "XsdNode.h"
#include "XsdElement.h"
#include "XsdAttribute.h"

#include <string>
#include <vector>

class XsdSequence;

using namespace std;

class XsdChoice : public XsdNode
{

  public:
    XsdChoice(string name);
    XsdChoice(string name, int minOccurs, int maxOccurs);
    XsdChoice(string name, string minOccurs, string maxOccurs);

    string name();
    void setName(string name);
    void add(XsdElement *element);
    void add(XsdAttribute *attribute);
    void add(XsdSequence *sequence);
    void add(std::vector<XsdElement*> elements);

    std::vector<XsdElement*>::iterator e_begin();
    std::vector<XsdElement*>::iterator e_end();
    int e_size();

    std::vector<XsdAttribute*>::iterator a_begin();
    std::vector<XsdAttribute*>::iterator a_end();
    int a_size();

    std::vector<XsdSequence*>::iterator s_begin();
    std::vector<XsdSequence*>::iterator s_end();
    int s_size();


    bool   maxOccursGiven();
    bool   minOccursGiven();
    string maxOccurs();
    string minOccurs();

    void setMaxOccurs(string maxOccurs);
    void setMinOccurs(string minOccurs);

  private:
    string _minOccurs;
    string _maxOccurs;
    string _name;
    bool   _minOccursGiven;
    bool   _maxOccursGiven;
    std::vector<XsdElement*>     _elements;
    std::vector<XsdAttribute*>   _attributes;
    std::vector<XsdSequence*>    _sequences;

};

#endif // __YARS_XSD_CHOCIE_H__



