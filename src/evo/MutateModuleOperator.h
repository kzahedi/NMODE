#ifndef __MODULE_MUTATION_OPERATOR_H__
#define __MODULE_MUTATION_OPERATOR_H__

#include "base/DataEvolutionNode.h"
#include "base/DataEvolutionEdge.h"
#include "base/DataModule.h"

class MutateModuleOperator
{
  public:
    // ~MutateModuleOperator();

    //MutateModuleOperator(const MutateModuleOperator);
    //MutateModuleOperator operator=(const MutateModuleOperator);

    static void mutate(DataModule *module,
                       DataEvolutionNode *_den,
                       DataEvolutionEdge *_dee);

  private:
    static void __mutateDelEdge(DataModule *m,    double probability);
    static void __mutateModifyEdge(DataModule *m, double probability,
                                                  double delta,
                                                  double max);
    static void __mutateAddEdge(DataModule *m,    double probability,
                                                  double max);
    static void __mutateAddNode(DataModule *m,    double probability,
                                                  double max);
    static void __mutateModifyNode(DataModule *m, double probability,
                                                  double delta,
                                                  double max);
    static void __mutateDelNode(DataModule *m,    double probability);
    static void __cleanup(DataModule *m);
};


#endif // __MODULE_MUTATION_OPERATOR_H__
