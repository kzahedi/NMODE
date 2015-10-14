#include "Evolve.h"

Evolve::Evolve()
{
}

void Evolve::init(string xml)
{
  _data = Data::instance();
  _data->read(xml);
  _pop = _data->specification()->population();


  _pc = new PopulationContainer();
  _pc->update(_pop);
  _pc->addObserver(this);

  Evaluate *e1 = new Evaluate("/Users/zahedi/projects/builds/yars-build","xml/braitenberg_tcpip.xml");
  Evaluate *e2 = new Evaluate("/Users/zahedi/projects/builds/yars-build","xml/braitenberg_tcpip.xml");

  e1->setPopulationContainer(_pc);
  e2->setPopulationContainer(_pc);

  boost::thread* p1 = new boost::thread(&Evaluate::run, e1);
  boost::thread* p2 = new boost::thread(&Evaluate::run, e2);

  p1->join();
  p2->join();

  // _reproduction

}

void Evolve::notify(ObservableMessage *message)
{
  switch(message->type())
  {
    case __M_NEXT_GENERATION:
      _pc->update(_pop);
      break;
  }
}
