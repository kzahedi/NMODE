#include <nmode/ReplayEvolution.h>

#include <nmode/Data.h>
#include <nmode/Random.h>
#include "ext/alphanum.hpp"

#include <dlfcn.h>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>


ReplayEvolution::ReplayEvolution()
{
  Random::initialise();
  _population = NULL;
}

void ReplayEvolution::replayEvolution(string dir)
{

  const std::string target_path( dir );
  const boost::regex my_filter( ".*/generation.*xml" );

  std::vector< std::string > all_matching_files;

  boost::filesystem::directory_iterator end_itr; // Default ctor yields past-the-end
  for( boost::filesystem::directory_iterator i( target_path ); i != end_itr; ++i )
  {
    if( !boost::filesystem::is_regular_file( i->status() ) ) continue;
    boost::smatch what;
    if( !boost::regex_match( i->path().string(), what, my_filter ) ) continue;
    all_matching_files.push_back( i->path().string() );
  }

  std::sort(all_matching_files.begin(), all_matching_files.end(), doj::alphanum_less<std::string>());

  _data = Data::instance();
  _data->readForReplay(all_matching_files[0]);

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

  _e = create_controller();

  for(int i = 4; i < (int)all_matching_files.size(); i = i + 5)
  {
    replayBestIndividual(all_matching_files[i]);
  }
}

void ReplayEvolution::replayBestIndividual(string xml)
{
  _data = Data::instance();
  _data->readForReplay(xml);

  _pop = Population::instance();
  _pop->reset();

  _pop->i_resize(1);

  for(int i = 0; i < _pop->i_size(); i++)
  {
    _pop->individual(i)->setNr(i+1);
  }

  _e->runOne(_pop->individual(0));
}

void ReplayEvolution::notify(ObservableMessage *message)
{
  // nothing
}
