#ifndef __DATA_H__
#define __DATA_H__

#include <vector>
#include <string>

#include "XsdSpecification.h"

#include "ENP.h"


using namespace std;

class Data
{
  public:
    static Data* instance();
    static void close();
    ~Data();
    ENP* specification();
    XsdSpecification* xsd();
    void clear();
    void read(string xmlFile);
    string header();
    string footer();

  private:
    Data();
    static Data *_me;
    ENP     *_root;
};

#endif // __DATA_H__
