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


#ifndef __YARS_XSD_NAMES_H__
#define __YARS_XSD_NAMES_H__

#include "XSDString.h"

# define YARS_XSD_NS                                X("http://www.w3.org/2001/XMLSchema")
# define YARS_XSD_ELEMENT_FORM_DEFAULT              X("elementFormDefault")
# define YARS_XSD_QUALIFIED                         X("qualified")

# define YARS_XSD_NAME                              X("name")
# define YARS_XSD_TYPE                              X("type")
# define YARS_XSD_VALUE                             X("value")

# define YARS_XSD_MIN_OCCURS                        X("minOccurs")
# define YARS_XSD_MAX_OCCURS                        X("maxOccurs")
# define YARS_XSD_USE                               X("use")
# define YARS_XSD_REQUIRED                          X("required")
# define YARS_XSD_OPTIONAL                          X("optional")
# define YARS_XSD_BASE                              X("base")

# define YARS_XSD_SCHEMA                            X("xs:schema")
# define YARS_XSD_ELEMENT                           X("xs:element")
# define YARS_XSD_COMPLEX_TYPE                      X("xs:complexType")
# define YARS_XSD_SEQUENCE                          X("xs:sequence")
# define YARS_XSD_ATTRIBUTE                         X("xs:attribute")
# define YARS_XSD_ENUMERATION                       X("xs:enumeration")
# define YARS_XSD_RESTRICTION                       X("xs:restriction")
# define YARS_XSD_SIMPLE_TYPE                       X("xs:simpleType")
# define YARS_XSD_CHOICE                            X("xs:choice")
# define YARS_XSD_MIN_INCLUSIVE                     X("xs:minInclusive")
# define YARS_XSD_MAX_INCLUSIVE                     X("xs:maxInclusive")
# define YARS_XSD_PATTERN                           X("xs:pattern")


#endif // __YARS_XSD_NAMES_H__


