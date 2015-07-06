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


#ifndef __YARS_XSD_SPECIFICATION_H__
#define __YARS_XSD_SPECIFICATION_H__

#include "XsdSequence.h"
#include "XsdEnumeration.h"
#include "XsdChoice.h"
#include "XsdInterval.h"
#include "XsdRegularExpression.h"


# define NE new XsdElement
# define NA new XsdAttribute

# define DEFINITION "definition"

#include <vector>
using namespace std;

# define TAG_XSD_DECIMAL               (char*)"xs:decimal"
# define TAG_XSD_INTEGER               (char*)"xs:integer"
# define TAG_XSD_STRING                (char*)"xs:string"

# define TAG_PID_DEFINITION            (char*)"pid"             DIVIDER DEFINITION

# define TAG_POSITIVE_NON_ZERO_INTEGER (char*)"positive_non_zero_integer" DIVIDER DEFINITION
# define TAG_POSITIVE_INTEGER          (char*)"positive_integer"          DIVIDER DEFINITION
# define TAG_UNIT_INTERVAL             (char*)"unit_interval"             DIVIDER DEFINITION
# define TAG_POSITIVE_NON_ZERO_DECIMAL (char*)"positive_non_zero_decimal" DIVIDER DEFINITION
# define TAG_POSITIVE_DECIMAL          (char*)"positive_decimal"          DIVIDER DEFINITION
# define TAG_NAME_DEFINITION           (char*)"name"                      DIVIDER DEFINITION

# define TAG_TRUE_FALSE_DEFINITION     (char*)"true"   DIVIDER "false" DIVIDER DEFINITION

/** \brief Singleton.
 *
 * This class store the structure of the XSD grammar.
 */
class XsdSpecification
{

  public:
    XsdSpecification();
    ~XsdSpecification();

    void setRoot(XsdSequence *root);
    void add(XsdSequence          *sequence);
    void add(XsdEnumeration       *enumeration);
    void add(XsdChoice            *choice);
    void add(XsdInterval          *interval);
    void add(XsdRegularExpression *regExp);

    XsdSequence *root();

    std::vector<XsdSequence*>::iterator          s_begin();
    std::vector<XsdSequence*>::iterator          s_end();
    int                                          s_size();

    std::vector<XsdEnumeration*>::iterator       e_begin();
    std::vector<XsdEnumeration*>::iterator       e_end();
    int                                          e_size();

    std::vector<XsdChoice*>::iterator            c_begin();
    std::vector<XsdChoice*>::iterator            c_end();
    int                                          c_size();

    std::vector<XsdInterval*>::iterator          i_begin();
    std::vector<XsdInterval*>::iterator          i_end();
    int                                          i_size();

    std::vector<XsdRegularExpression*>::iterator r_begin();
    std::vector<XsdRegularExpression*>::iterator r_end();
    int                                          r_size();

    std::vector<XsdNode*>::iterator              n_begin();
    std::vector<XsdNode*>::iterator              n_end();
    int                                          n_size();

  private:

    XsdSequence *_root;

    std::vector<XsdSequence*>          _sequences;
    std::vector<XsdEnumeration*>       _enumerations;
    std::vector<XsdChoice*>            _choices;
    std::vector<XsdInterval*>          _intervals;
    std::vector<XsdRegularExpression*> _regExps;
    std::vector<XsdNode*>              _nodes;
};

#endif // __YARS_XSD_SPECIFICATION_H__
