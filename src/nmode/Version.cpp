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
