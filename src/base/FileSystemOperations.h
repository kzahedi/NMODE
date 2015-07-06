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



#ifndef __YARS_FILESYSTEM_OPERATIONS_H__
#define __YARS_FILESYSTEM_OPERATIONS_H__

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <vector>
#include <iostream>

#include "base/ENPException.h"

namespace fs = boost::filesystem;
using namespace std;

class FileSystemOperations
{
  public:
  static bool doesDirExist(fs::path dirPath);
  static bool doesFileExist(fs::path filePath);
  static bool doesDirExist(string *dirName);
  static bool doesFileExist(string *fileName);
  static bool doesExecutableExist(string exe) throw (ENPException);
  static void createDir(string dirName)       throw (ENPException);

  static string* getFirstExistingDirContainingDir(std::vector<string> dirs,
      string *containedDirName);
  static string* getFirstExistingDirContainingFile(std::vector<string> dirs,
      string *containedFileName);
  static string* getFirstExistingDir(std::vector<string> dirs);
  static string* getFirstExistingFile(std::vector<string> files);

  static void checkValidPath(string *name, bool isDir, bool fatal);
      // description);
  static void checkValidPathFromAlternatives(string *name, string *pathName,
      std::vector<string> *pathCandidates, bool fatal);
  // string description);

  protected:
    FileSystemOperations();
    ~FileSystemOperations();
};

#endif
