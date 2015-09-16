#include "MutatePopulationOperator.h"

#include <glog/logging.h>

#include "base/macros.h"
#include "base/Random.h"
#include "base/Data.h"

#include "MutateIndividualOperator.h"

#include <sstream>

void MutatePopulationOperator::mutate(Population *p)
{
  VLOG(50) << ">> start mutate population";
  for(Individuals::iterator ind = p->i_end(); ind != p->i_end(); ind++)
  {
      MutateIndividualOperator::mutate(*ind);
  }
  VLOG(50) << ">> end mutate population";
}
