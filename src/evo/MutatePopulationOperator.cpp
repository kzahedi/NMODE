#include "MutateIndividualOperator.h"

#include <glog/logging.h>

#include "base/macros.h"
#include "base/Random.h"
#include "base/data/Data.h"

#include "MutateModuleOperator.h"

#include <sstream>

void MutateIndividualOperator::mutate(Individual *m)
{
  VLOG(50) << ">> start mutate individual";
  Data *data = Data::instance();
  DataEvolutionEdge *dee = data->specification()->evolution()->edge();
  DataEvolutionNode *den = data->specification()->evolution()->node();
  for(Modules::iterator mod = m->m_begin(); mod != m->m_end(); mod++)
  {
    if((*mod)->isCopy() == false)
    {
      MutateModuleOperator::mutate(*mod, den, dee);
    }
  }
  VLOG(50) << ">> end mutate individual";
}

