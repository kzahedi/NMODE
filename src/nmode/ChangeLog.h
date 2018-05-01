#ifndef __NMODE_VERSIONS_H__
#define __NMODE_VERSIONS_H__

XmlChangeLog::add(0, 0, 0, "Initial XML definition",                                     true);
XmlChangeLog::add(0, 1, 0, "Ready for publication",                                      true);
XmlChangeLog::add(0, 1, 1, "minDistance attribute in <add edge>",                        false);
XmlChangeLog::add(0, 1, 2, "path attribute added to simulator section",                  false);
XmlChangeLog::add(0, 1, 3, "log file type is now an option in <evaluation>",             false);
XmlChangeLog::add(0, 1, 4, "keeping old log files is now optional in <log>",             false);
XmlChangeLog::add(0, 1, 5, "<evaluation ...> now also takes iterations",                 false);
XmlChangeLog::add(0, 2, 0, "added support for OpenAI",                                   false);
XmlChangeLog::add(0, 3, 0, "changed from rank based to Age-Fitness Pareto Optimisation", false);
XmlChangeLog::add(0, 3, 1, "number of logged individuals",                               false);

#endif // __VERSIONS_H__
