#include <nmode/XmlChangeLogEntry.h>

XmlChangeLogEntry::XmlChangeLogEntry(Version v, string d, bool c)
{
  _version     = v;
  _description = d;
  _crucial     = c;
}

Version XmlChangeLogEntry::version()
{
  return _version;
}

bool XmlChangeLogEntry::crucial()
{
  return _crucial;
}

string XmlChangeLogEntry::description()
{
  return _description;
}
