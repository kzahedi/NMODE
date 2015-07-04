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
#include "FileSystemOperations.h"

#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

#include <sstream>
#include <stdlib.h>
#ifndef _MSC_VER
#  include <unistd.h>
#else
#  include <io.h>
#endif // _MSC_VER

using namespace boost;

FileSystemOperations::FileSystemOperations()
{ }

FileSystemOperations::~FileSystemOperations()
{ }

bool FileSystemOperations::doesDirExist(fs::path dirPath)
{
  if(fs::exists(dirPath) && fs::is_directory(dirPath))
    return true;
  else
    return false;
}

bool FileSystemOperations::doesFileExist(fs::path filePath)
{
  if(fs::exists(filePath) && (! fs::is_directory(filePath)))
    return true;
  else
    return false;
}

bool FileSystemOperations::doesDirExist(string *dirName)
{
  //fs::path dirPath = fs::path(*dirName, fs::native);
  fs::path dirPath = fs::path(*dirName);
  if(doesDirExist(dirPath))
    return true;
  else
    return false;
}

bool FileSystemOperations::doesFileExist(string *fileName)
{
  fs::path filePath = fs::path(*fileName);
  if(doesFileExist(filePath))
    return true;
  else
    return false;
}

string* FileSystemOperations::getFirstExistingDirContainingDir(std::vector<string>
    dirs, string *containedDirName)
{
  fs::path path;

  // check if this is an absolute path
  path = fs::path(*containedDirName);
  if(path.is_complete())
  {
    if(doesDirExist(path))
    {
      // Y_DEBUG("FileSystemOperations: dir %s is given as absolute path.",
          // fs::path(path).string().c_str());
      return (new string(""));
    }
    else
    {
      // Y_DEBUG("FileSystemOperations: dir %s is given as absolute path "
          // " but does not exist.", fs::path(path).string().c_str());
      return NULL;
    }
  }

  // .. if not check if it is contained in the search hierarchy
  for(unsigned int i=0; i < dirs.size(); i++)
  {
    path = fs::path(dirs[i]);

    if(doesDirExist(path))
    {
      if(doesDirExist(path / fs::path(*containedDirName)))
      {
        // Y_DEBUG("FileSystemOperations: dir %s in dir %s found.",
            // (*containedDirName).c_str(),
            // path.string().c_str());
        return (new string(dirs[i]));
      }
    }
  }

  return NULL;
}

string* FileSystemOperations::getFirstExistingDirContainingFile(std::vector<string>
    dirs, string *containedFileName)
{
  fs::path path;

  // check if this is an absolute path
  path = fs::path(*containedFileName);
  if(path.is_complete())
  {
    if(doesFileExist(path))
    {
      // Y_DEBUG("FileSystemOperations: file %s is given as absolute path.",
          // fs::path(path).string().c_str());
      return (new string(""));
    }
    else
    {
      // Y_DEBUG("FileSystemOperations: file %s is given as absolute path "
          // "but does not exist.", fs::path(path).string().c_str());
      return NULL;
    }
  }

  // .. if not check if it is contained in the search hierarchy
  for(unsigned int i=0; i < dirs.size(); i++)
  {
    path = fs::path(dirs[i]);

    if(doesDirExist(path))
    {
      if(doesFileExist(path / fs::path(*containedFileName)))
      {
        // Y_DEBUG("FileSystemOperations: file %s in dir %s found.",
          // (*containedFileName).c_str(),
          // path.string().c_str());
        return (new string(dirs[i]));
      }
    }
  }

  return NULL;
}

string* FileSystemOperations::getFirstExistingDir(std::vector<string> dirs)
{
  fs::path path;

  for(unsigned int i=0; i < dirs.size(); i++)
  {
    path = fs::path(dirs[i]);

    if(doesDirExist(path))
    {
      // Y_DEBUG("FileSystemOperations: dir %s found.",
        // path.string().c_str());
      return (new string(dirs[i]));
    }
  }

  return NULL;
}

string* FileSystemOperations::getFirstExistingFile(std::vector<string> files)
{
  fs::path path;

  for(unsigned int i=0; i < files.size(); i++)
  {
    path = fs::path(files[i]);

    if(doesFileExist(path))
    {
      // Y_DEBUG("FileSystemOperations: file %s found.",
        // path.string().c_str());
      return (new string(files[i]));
    }
  }

  return NULL;
}

void FileSystemOperations::checkValidPath(string *name, bool isDir, bool fatal)
    // string description)
{

  fs::path path;
  if(name->c_str()[0] != '/') // path is a local path starting with a letter
  {
    path = fs::initial_path() / fs::path(*name);
    *name = path.string();
  }
  path = fs::path(*name);

  if(! path.is_complete())
  {
    path = fs::system_complete(path);
  }

  if(((isDir && doesDirExist(path)) || (!isDir && doesFileExist(path))))
  {
    // Y_INFO("Using %s %s", description.c_str(),
        // path.string().c_str());
  }
  else
  {
    if(fatal)
    {
      // Y_FATAL("ERROR: %s %s does not exist --> exiting.",
          // description.c_str(), path.string().c_str());
      exit(-1);
    }
    else
    {
      // Y_FATAL("WARNING: %s %s does not exist.",
          // description.c_str(), path.string().c_str());
    }
  }
}

void FileSystemOperations::checkValidPathFromAlternatives(string *name, string
    *pathName, std::vector<string> *pathCandidates, bool fatal)
// , string description)
{
  fs::path path;

  if(pathName == NULL)
  {
    if(fatal)
    {
      // Y_FATAL("ERROR: %s %s could not be found in:", description.c_str(),
          // (*name).c_str());
      for(unsigned int i=0; i<(*pathCandidates).size(); i++)
      {
        // Y_FATAL("  %s", (*pathCandidates)[i].c_str());
      }
      // Y_FATAL("--> exiting!");
      exit(-1);
    }
    else
    {
      // Y_INFO("WARNING: %s %s could not be found in:", description.c_str(),
          // (*name).c_str());
      for(unsigned int i=0; i<(*pathCandidates).size(); i++)
      {
        // Y_INFO("  %s", (*pathCandidates)[i].c_str());
      }
    }
  }
  else
  {
    path = fs::path(*name);

    if(! path.is_complete())
    {
      path = fs::system_complete(
          fs::path(*pathName) / fs::path(*name));
    }

    if(fs::exists(path))
    {
      // Y_INFO("Using %s %s", description.c_str(),
          // path.string().c_str());
    }
    else
    {
      if(fatal)
      {
        // Y_FATAL("ERROR: %s %s does not exist --> exiting.",
            // description.c_str(), path.string().c_str());
        exit(-1);
      }
      else
      {
        // Y_FATAL("WARNING: %s %s does not exist.",
            // description.c_str(), path.string().c_str());
      }
    }
  }
}

void FileSystemOperations::createDir(string dirName) throw (ENPException)
{
  if(fs::exists(dirName))
  {
    std::stringstream oss; 
    oss << "FileSystemOperations::createDir: The directory " << dirName
        << " already exists.";
    throw ENPException(oss.str());
  }
  fs::create_directory(dirName);
}

bool FileSystemOperations::doesExecutableExist(string exe) throw (ENPException)
{
  fs::path path;
  string path_string = string(getenv("PATH"));
  if (path_string.length() == 0) throw ENPException("Cannot read PATH system variable.");

  char_separator<char> sep(":");
  tokenizer< char_separator<char> > tokens(path_string, sep);

  BOOST_FOREACH(string t, tokens)
  {
    path = fs::system_complete( fs::path(t) / fs::path(exe));
#ifndef _MSC_VER
    if (access(path.string().c_str(), X_OK) == 0) return true;
#else // _MSC_VER
    if (_access(path.string().c_str(), 0)) return true;
#endif // _MSC_VER
  }
  return false;
}
