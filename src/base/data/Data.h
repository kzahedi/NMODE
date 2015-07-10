#ifndef __DATA_H__
#define __DATA_H__

#include <vector>
#include <string>

#include "base/xsd/specification/XsdSpecification.h"

#include "DataENP.h"


using namespace std;

class Data
{
  public:
    static Data* instance();
    static void close();
    ~Data();
    DataENP* specification();
    XsdSpecification* xsd();
    void clear();
    void read(string xmlFile);
    string header();
    string footer();

  private:
    Data();
    static Data *_me;
    DataENP     *_root;
};

#endif // __DATA_H__
