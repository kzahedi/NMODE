#include "base/Configuration.h"
#include "base/Data.h"
#include "base/Population.h"
#include "base/Exporter.h"
#include "base/Random.h"

#include "evo/MutatePopulationOperator.h"

#include <glog/logging.h>

#include <iostream>
#include <fstream>

using namespace std;

string prefix(int i)
{
  stringstream sst;
  sst << i;
  string s = sst.str();

  while(s.length() < 4)
  {
    s = "0" + s;
  }
  return s;
}

int main(int argc, char** argv)
{
  google::InitGoogleLogging(argv[0]);
  Configuration *configuration = new Configuration(argc, argv, true);
  Random::initialise();
  stringstream sst;
  sst << "Random:";
  for(int i = 0; i < 10; i++)
  {
    sst << " " << Random::rand(0, 100);
  }
  VLOG(10) << sst.str();
  sst.str("");
  Data *data = Data::instance();

  LOG_IF(INFO, configuration->input().size()  > 0) << "Input file given "    << configuration->input();
  LOG_IF(INFO, configuration->output().size() > 0) << "Output file given "   << configuration->output();
  LOG_IF(INFO, configuration->cfg().size()    > 0) << "Configuration given " << configuration->cfg();

  VLOG(5) << "reading file " << configuration->cfg();
  data->read(configuration->cfg());
  Population *pop = data->specification()->population();

  cout << "Population: " << pop << endl;

  for(int i = 0; i < 100; i++)
  {
    VLOG(50) << " generation " << i;
    sst.str("");
    sst << "generation_" << prefix(i) << ".xml";
    cout << "opening " << sst.str() << endl;

    MutatePopulationOperator::mutate(pop);

    std::ofstream ofs;
    ofs.open (sst.str(), std::ofstream::out);
    sst.str("");
    sst << data->header();
    sst << Exporter::toXml(pop);
    sst << data->footer();
    ofs << sst.str();
    ofs.close();
  }

  VLOG(5) << "done.";

  return 0;
}
