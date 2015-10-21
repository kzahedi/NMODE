#include "Evolve.h"

#include "enp/Data.h"
#include "enp/Random.h"

Evolve::Evolve()
{
  Random::initialise();
}

void Evolve::init(string xml)
{
  _data = Data::instance();
  _data->read(xml);

  _pop          = Population::instance();
  _reproduction = new Reproduction();
  // the initial population is always open to reproduction
  _reproduction->reproduce();

  _pop->addObserver(this);
  char buf[1024];
  getcwd(buf, 1024);

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

  sleep(1);

  chdir(buf);

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
