#ifndef __YARS_XSD_INTERVAL_H__
#define __YARS_XSD_INTERVAL_H__

#include <nmode/XsdNode.h>

#include <string>
#include <vector>

using namespace std;

class XsdInterval : public XsdNode
{
  public:
    XsdInterval(string name, string type, int minimum, int maximum);
    XsdInterval(string name, string type, string minimum, string maximum);

    string minimum();
    string maximum();
    string name();
    string type();

  private:
    void __init(string name, string type, string min, string max);
    string _name;
    string _type;
    string _min;
    string _max;
};

#endif // __YARS_XSD_INTERVAL_H__
