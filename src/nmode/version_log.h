#ifndef __CHANGE_LOG_H__
#define __CHANGE_LOG_H__

XmlChangeLog::add(0, 0, 0,  "Initial XML definition", true);
XmlChangeLog::add(0, 0, 1,  "<evolution> <neuron> ... </neuron> <synapse> ... </synapse> </evolution> <configuration> <module ...> <neuron ..> <position ...> <transferfunction ...> </neuron></configuration>", true);
XmlChangeLog::add(0, 0, 2, "added <simulator> tag", true);

#endif // __CHANGE_LOG_H__
