#ifndef __DATA_H__
#define __DATA_H__

#include <vector>
#include <string>

#include "XsdSpecification.h"

#include "ENP.h"
#include "Observer.h"

#define REP Data::instance()->specification()->reproduction()
#define SIM Data::instance()->specification()->simulator()
#define EVA Data::instance()->specification()->evaluation()

using namespace std;

class Data : public Observer
{
  public:
    static Data* instance();
    static void close();
    ~Data();
    ENP* specification();
    XsdSpecification* xsd();
    void clear();
    void read(string xmlFile);
    string xml();
    void notify(ObservableMessage *message);

  private:
    Data();

    string __toXml(Population *population);
    string __toXml(Individual *individual);
    string __toXml(Module *module);

    string __simulator();
    string __evaluator();
    string __reproduction();
    string __evolution();
    string __configuration();
    string __population();

    static Data *_me;
    ENP         *_root;
    string       _xml;
    bool         _initialisationCompleted;
};

#endif // __DATA_H__
