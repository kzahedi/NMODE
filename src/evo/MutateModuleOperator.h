#ifndef __MODULE_MUTATION_OPERATOR_H__
#define __MODULE_MUTATION_OPERATOR_H__

#include "base/EvolutionNode.h"
#include "base/EvolutionEdge.h"
#include "base/Module.h"

class MutateModuleOperator
{
  public:
    // ~MutateModuleOperator();

    //MutateModuleOperator(const MutateModuleOperator);
    //MutateModuleOperator operator=(const MutateModuleOperator);

    static void mutate(Module *module,
                       EvolutionNode *_den,
                       EvolutionEdge *_dee);

  private:
    static void __mutateDelEdge(Module *m,    double probability);
    static void __mutateModifyEdge(Module *m, double probability,
                                              double delta,
                                              double max);
    static void __mutateAddEdge(Module *m,    double probability,
                                              double max);
    static void __mutateAddNode(Module *m,    double probability,
                                              double max);
    static void __mutateModifyNode(Module *m, double probability,
                                              double delta,
                                              double max);
    static void __mutateDelNode(Module *m,    double probability);
    static void __cleanup(Module *m);
};


#endif // __MODULE_MUTATION_OPERATOR_H__
