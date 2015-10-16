#include "Evolve.h"
#include "base/Data.h"

Evolve::Evolve()
{
}

void Evolve::init(string xml)
{
  _data = Data::instance();
  _data->read(xml);

  _pop          = Population::instance();
  _reproduction = new Reproduction();

  _pop->addObserver(this);

  int nr = Data::instance()->specification()->simulator()->nr();
  cout << "nr: " << nr << endl;
  for(int i = 0; i < nr; i++)
  {
    Evaluate *e = new Evaluate();
    // e->setPopulationContainer(_pc);
    _evaluators.push_back(e);
  }

  for(int i = 0; i < nr; i++)
  {
    boost::thread* p = new boost::thread(&Evaluate::run, _evaluators[i]);
    _threads.push_back(p);
  }

  for(int i = 0; i < nr; i++)
  {
    _threads[i]->join();
  }

  // _reproduction
}

void Evolve::notify(ObservableMessage *message)
{
  switch(message->type())
  {
    case __M_NEXT_GENERATION:
       _reproduction->reproduce();
      break;
  }
}
