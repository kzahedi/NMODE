#ifndef __NMODE_FILESYSTEM_OPERATIONS_H__
#define __NMODE_FILESYSTEM_OPERATIONS_H__

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <vector>
#include <iostream>

#include <nmode/NMODEException.h>

namespace fs = boost::filesystem;
using namespace std;

class FileSystemOperations
{
  public:
  static bool doesDirExist(fs::path dirPath);
  static bool doesFileExist(fs::path filePath);
  static bool doesDirExist(string *dirName);
  static bool doesFileExist(string *fileName);
  static bool doesExecutableExist(string exe) throw (NMODEException);
  static void createDir(string dirName)       throw (NMODEException);

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
