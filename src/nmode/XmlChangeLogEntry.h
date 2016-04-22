#ifndef __NMODE_XML_CHANGE_LOG_ENTRY_H__
#define __NMODE_XML_CHANGE_LOG_ENTRY_H__

#include <nmode/Version.h>

#include <string>

using namespace std;

class XmlChangeLogEntry
{
  public:
    XmlChangeLogEntry(Version version, string description, bool crucial);
    Version version();
    bool crucial();
    string description();

  private:

    Version _version;
    string _description;
    bool   _crucial;

};


#endif // __XML_CHANGE_LOG_ENTRY_H__
