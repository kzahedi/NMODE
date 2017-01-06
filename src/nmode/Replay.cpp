#include <nmode/Replay.h>

#include <nmode/Data.h>
#include <nmode/Random.h>

#include <dlfcn.h>

Replay::Replay()
{
  Random::initialise();
  _population = NULL;
}

void Replay::initFromDir(string dir)
{
  stringstream sst;
  sst << dir << "/" << "last_generation.xml";

  _data = Data::instance();
  _data->read(sst.str());

  this->init(sst.str(), false);
}

void Replay::init(string xml, bool read, string log)
{
  if(read == true)
  {
    _data = Data::instance();
    _data->read(xml);
  }

  _pop = Population::instance();
  char buf[1024];
  getcwd(buf, 1024);

  for(int i = 0; i < _pop->i_size(); i++)
  {
    _pop->individual(i)->setNr(i+1);
  }

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

  Evaluate *e = create_controller();
  chdir(buf);
  e->run();
}

void Replay::notify(ObservableMessage *message)
{
  // nothing
}
