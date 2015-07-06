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



#include "Version.h"

Version::Version()
{
  major = 0;
  minor = 0;
  patch = 0;
}

Version::Version(int maj, int min, int pat)
{
  major = maj;
  minor = min;
  patch = pat;
}

Version::Version(const Version &v)
{
  major = v.major;
  minor = v.minor;
  patch = v.patch;
}

Version& Version::operator=(const Version &v)
{
  major = v.major;
  minor = v.minor;
  patch = v.patch;
  return *this;
}

bool Version::operator<(const Version &v)
{
  if(major > v.major) return false;
  if(major < v.major) return true;

  // v.major == major
  if(minor > v.minor) return false;
  if(minor < v.minor) return true;

  // v.major == major && v.minor == minor

  if(patch > v.patch) return false;
  if(patch < v.patch) return true;
  return false; // if v == *this -> false
}

bool Version::operator>(const Version &v)
{
  if(major > v.major) return true;
  if(major < v.major) return false;

  // v.major == major
  if(minor > v.minor) return true;
  if(minor < v.minor) return false;

  // v.major == major && v.minor == minor

  if(patch > v.patch) return true;
  if(patch < v.patch) return false;
  return false; // if v == *this -> false
}

bool Version::operator==(const Version &v)
{
  return (v.major == major) && (v.minor == minor) && (v.patch == patch);
}
