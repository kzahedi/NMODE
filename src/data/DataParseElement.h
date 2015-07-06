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



#ifndef __DATA_PARSE_ELEMENT_H__
#define __DATA_PARSE_ELEMENT_H__

#include "DataParseAttribute.h"

#include <string>
#include <vector>
#include <iostream>

# define YARS_DATA_PARSE_ELEMENT_TYPE_OPENING 2001
# define YARS_DATA_PARSE_ELEMENT_TYPE_CLOSING 2002

using namespace std;

/**
 * @brief Interface between parser and representation.
 *
 * @sa DataParseAttribute
 */
class DataParseElement : public std::vector<DataParseAttribute*>
{
  public:
    /**
     * @brief Constructor. The type is one of:
     * <ul>
     *   <li> YARS_DATA_PARSE_ELEMENT_TYPE_OPENING </li>
     *   <li> YARS_DATA_PARSE_ELEMENT_TYPE_CLOSING </li>
     * </ul>
     *
     * @param type
     */
    DataParseElement(int type);

    /**
     * @brief Destructor.
     */
    ~DataParseElement();

    /**
     * @brief Returns the name of the tag.
     *
     * @return name
     */
    string name();

    /**
     * @brief Sets the name, given as char*.
     *
     * @param name
     */
    void setName(char *name);

    /**
     * @brief Sets the name, given as string.
     *
     * @param name
     */
    void setName(string name);

    /**
     * @brief Adds an attribute to this element.
     *
     * @param attribute
     */
    void add(DataParseAttribute *attribute);

    /**
     * @brief Returns the attribute, which is identified by its name, on NULL
     * if no attribute with the specified name was found.
     *
     * @param name
     *
     * @return attribute, or NULL if not found
     * @s DataParseAttribute
     */
    DataParseAttribute* attribute(string name);
    bool hasAttriute(string name);

    /**
     * @brief Returns if this element is an specific opening tag.
     *
     * Returns type == YARS_DATA_PARSE_ELEMENT_TYPE_OPENING  && name == name
     *
     * @param name
     *
     * @return true/false
     */
    bool opening(char *name);

    /**
     * @brief Returns if this element is an specific opening tag.
     *
     * Returns type == YARS_DATA_PARSE_ELEMENT_TYPE_OPENING  && name == name
     *
     * @param name
     *
     * @return true/false
     */
    bool opening(string name);


    /**
     * @brief Returns if this element is a specific closing tag.
     *
     * Returns type == YARS_DATA_PARSE_ELEMENT_TYPE_CLOSING  && name == name
     *
     * @param name
     *
     * @return
     */
    bool closing(char *name);

    /**
     * @brief Returns if this element is a specific closing tag.
     *
     * Returns type == YARS_DATA_PARSE_ELEMENT_TYPE_CLOSING  && name == name
     *
     * @param name
     *
     * @return
     */
    bool closing(string name);

    void set(string name, double &value);
    void set(string name, string &value);
    void set(string name, bool &value);
    void set(string name, int &value);
    void set(string name, unsigned long &value);

    friend std::ostream& operator<<(std::ostream& str, const DataParseElement& d)
    {
      str << d._name << ": " << d._type;
      return str;
    };


  private:
    string _name;
    int    _type;
};

#endif // __DATA_PARSE_ELEMENT_H__
