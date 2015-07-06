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



#ifndef __XML_CHANGE_LOG_H__
#define __XML_CHANGE_LOG_H__

#include "XmlChangeLogEntry.h"

#include "Version.h"

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class XmlChangeLog : public std::vector<XmlChangeLogEntry*>
{
  public:
    ~XmlChangeLog();

    static void add(Version version, string description, bool crucial = false);
    static void add(int major, int minor, int patch, string description, bool crucial = false);
    static Version version();
    static Version last_crucial_change();

    static void close();
    static string changes(Version version);

    static bool compare(XmlChangeLogEntry *a, XmlChangeLogEntry *b);

  private:
    XmlChangeLog();
    Version _version; // last version
    Version _last_crucial_change;

    static XmlChangeLog *_me;

};

#endif // __XML_CHANGE_LOG_H__
