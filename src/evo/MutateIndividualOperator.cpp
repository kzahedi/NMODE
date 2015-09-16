#include "MutateIndividualOperator.h"

#include <glog/logging.h>

#include "base/macros.h"
#include "base/Random.h"
#include "base/Data.h"

#include "MutateModuleOperator.h"

#include <sstream>

void MutateIndividualOperator::mutate(Individual *i)
{
  VLOG(50) << ">> start mutate population";
  Data *data = Data::instance();
  EvolutionEdge *dee = data->specification()->evolution()->edge();
  EvolutionNode *den = data->specification()->evolution()->node();
  for(Modules::iterator mod = i->m_begin(); mod != i->m_end(); mod++)
  {
    if((*mod)->isCopy() == false)
    {
      MutateModuleOperator::mutate(*mod, den, dee);
    }
  }
  VLOG(50) << ">> end mutate individual";
}
