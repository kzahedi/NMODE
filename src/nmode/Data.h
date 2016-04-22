#ifndef __NMODE_DATA_H__
#define __NMODE_DATA_H__

#include <vector>
#include <string>

#include <nmode/XsdSpecification.h>

#include <nmode/NMODE.h>
#include <nmode/Observer.h>

#define REP Data::instance()->specification()->reproduction()
#define SIM Data::instance()->specification()->simulator()
#define EVA Data::instance()->specification()->evaluation()
#define VIS Data::instance()->specification()->visualisation()

using namespace std;

class Data : public Observer
{
  public:
    static Data* instance();
    static void close();
    ~Data();
    NMODE* specification();
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
    string __visualisation();

    void   __writeCfg();

    static Data* _me;
    NMODE*       _root;
    string       _xml;
    bool         _initialisationCompleted;
};

#endif // __DATA_H__
