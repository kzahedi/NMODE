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


#ifndef __YARS_XSD_SEQUENCE_H__
#define __YARS_XSD_SEQUENCE_H__

#include "XsdNode.h"
#include "XsdElement.h"
#include "XsdAttribute.h"
#include "XsdChoice.h"
#include "XsdRegularExpression.h"
#include "XsdInterval.h"

#include <string>
#include <vector>

using namespace std;

class XsdSequence : public XsdNode
{

  public:
    XsdSequence();
    XsdSequence(string name);

    void setName(char *name);
    void setName(string name);
    void add(XsdElement *element);
    void add(XsdAttribute *attribute);
    void add(XsdChoice *choice);
    void add(XsdRegularExpression *regExp);
    void add(XsdInterval *interval);
    void add(std::vector<XsdElement*> elements);

    string name();

    std::vector<XsdElement*>::iterator           e_begin();
    std::vector<XsdElement*>::iterator           e_end();
    int                                     e_size();

    std::vector<XsdAttribute*>::iterator         a_begin();
    std::vector<XsdAttribute*>::iterator         a_end();
    int                                     a_size();

    std::vector<XsdChoice*>::iterator            c_begin();
    std::vector<XsdChoice*>::iterator            c_end();
    int                                     c_size();

    std::vector<XsdRegularExpression*>::iterator r_begin();
    std::vector<XsdRegularExpression*>::iterator r_end();
    int                                     r_size();

    std::vector<XsdInterval*>::iterator          i_begin();
    std::vector<XsdInterval*>::iterator          i_end();
    int                                     i_size();

    std::vector<XsdNode*>::iterator              n_begin();
    std::vector<XsdNode*>::iterator              n_end();
    int                                     n_size();

  private:
    string                             _name;
    std::vector<XsdElement*>           _elements;
    std::vector<XsdAttribute*>         _attributes;
    std::vector<XsdChoice*>            _choices;
    std::vector<XsdRegularExpression*> _regExps;
    std::vector<XsdInterval*>          _intervals;
    std::vector<XsdNode*>              _children;

};

#endif // __YARS_XSD_SEQUENCE_H__


