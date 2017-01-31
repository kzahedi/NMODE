#include <nmode/Evolve.h>

#include <nmode/Data.h>
#include <nmode/Random.h>

#include <dlfcn.h>

Evolve::Evolve(bool printConfiguration)
{
  Random::initialise();
  _population = NULL;
  _printConfiguration = printConfiguration;
}

void Evolve::initFromDir(string dir)
{
  stringstream sst;
  sst << dir << "/" << "last_generation.xml";

  _data = Data::instance();
  _data->read(sst.str());

  _pop = Population::instance();
  // _pop->removeCurrentLogDir();
  _pop->setCurrentLogDir(dir);
  _pop->readStats(dir);

  _pop->setGeneration(_pop->generation() - 1);

  this->init(sst.str(), false);
}

// void Evolve::initFromDir(string dir)
// {
  // stringstream sst;
  // sst << dir << "/" << "last_generation.xml";

  // _data = Data::instance();
  // _data->read(sst.str());

  // _pop = Population::instance();
  // _pop->removeCurrentLogDir();
  // _pop->setCurrentLogDir(dir);
  // _pop->readStats(dir);

  // _pop->setGeneration(_pop->generation() - 1);

  // this->init(sst.str(), false);
// }



void Evolve::init(string xml, bool read, string log)
{
  if(read == true)
  {
    _data = Data::instance();
    _data->read(xml);
  }

  _pop          = Population::instance();
  if(log != "") _pop->setCurrentLogDir(log);
  _reproduction = new Reproduction();
  // the initial population is always open to reproduction
  _reproduction->firstReproduction();


  _pop->addObserver(this);
  char buf[1024];
  getcwd(buf, 1024);

  int nr = Data::instance()->specification()->simulator()->nr();

  string module = EVA->module();
  stringstream m;
#ifdef __APPLE__
  m << "lib/lib" << module << ".dylib";
#else // __APPLE__
  m << "lib/lib" << module << ".so";
#endif // __APPLE__

  void *controllerLib = dlopen(m.str().c_str(),RTLD_LAZY);

  if(!controllerLib)
  {
    cout << "failed to load \"" << m.str() << "\" with error message \"" << dlerror() << endl;
    exit(-1);
    return;
  }

  dlerror();

  create_e* create_controller = (create_e*)dlsym(controllerLib,"create");

  dlerror(); // TODO: error handling
  if(!controllerLib)
  {
    cout << "Robot::Cannot load symbol create" << endl;
    exit(-1);
  }

  for(int i = 0; i < nr; i++)
  {
    Evaluate *e = create_controller();
    e->printConfiguration(_printConfiguration);
    if(i > 0) e->nogui();
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
