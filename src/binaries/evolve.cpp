#include "base/Configuration.h"
#include "base/data/Data.h"
#include "evo/Population.h"
#include "evo/ModuleMutationOperator.h"

#include <glog/logging.h>

#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
  google::InitGoogleLogging(argv[0]);
  Configuration *configuration = new Configuration(argc, argv, true);

  Data *data = Data::instance();

  LOG_IF(INFO, configuration->input().size() > 0) 
    << "Input file given " << configuration->input();
  LOG_IF(INFO, configuration->output().size() > 0)
    << "Output file given " << configuration->output();
  LOG_IF(INFO, configuration->cfg().size() > 0)
    << "Configuration given " << configuration->cfg();

  VLOG(5) << "reading file " << configuration->cfg();
  data->read(configuration->cfg());

  Population *pop = new Population();
  pop->initialise();

  Individual *ind = pop->individual(0);
  Module     *mod = ind->module(0);

  DataEvolutionEdge *dee = data->specification()->evolution()->edge();
  DataEvolutionNode *den = data->specification()->evolution()->node();

  ModuleMutationOperator::mutate(mod, den, dee);

  VLOG(5) << "done.";

  return 0;
}
