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


#ifndef __DATA_PARSE_ATTRIBUTE_H__
#define __DATA_PARSE_ATTRIBUTE_H__

#include <string>

using namespace std;

/**
 * @brief Container for the attributes of an xml element
 * @sa DataParseElement
 */
class DataParseAttribute
{
  public:
    /**
     * @brief Constructor
     */
    DataParseAttribute();

    /**
     * @brief Destructor (Does nothing)
     */
    ~DataParseAttribute();

    /**
     * @brief Set the name of the attribute.
     *
     * @param name
     */
    void setName(string name);

    /**
     * @brief Set the value of the attribute. The value is naturally given as
     * string, because it is retrieved from an XML file.
     *
     * @param value
     */
    void setValue(string value);

    /**
     * @brief Returns the name of the attribute.
     *
     * @return name
     */
    string name();

    /**
     * @brief Returns the string-value of the value.
     *
     * @return value (string)
     */
    string value();

    /**
     * @brief Returns the value converted by atoi. DataParseAttribute cannot know
     * of which type the value is. Therefore, there is no error handling.
     *
     * @return value (int)
     */
    int intValue();

    /**
     * @brief Returns the value converted from atoi to unsigned long.
     * DataParseAttribute cannot know of which type the value is. Therefore,
     * there is no error handling.
     *
     * @return value (int)
     */
    unsigned long unsignedlongValue();

    /**
     * @brief Returns if value is equal to "true". DataParseAttribute cannot know
     * of which type the value is. Therefore, there is no error handling.
     *
     * @return value (bool)
     */
    bool boolValue();

    /**
     * @brief Returns the value converted by atof. DataParseAttribute cannot know
     * of which type the value is. Therefore, there is no error handling.
     *
     * @return value (double)
     */
    double realValue();

  private:
    string _name;
    string _value;
};

#endif // __DATA_PARSE_ATTRIBUTE_H__
