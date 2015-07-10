#ifndef __MODULE_MUTATION_OPERATOR_H__
#define __MODULE_MUTATION_OPERATOR_H__

#include "base/data/DataEvolutionNode.h"
#include "base/data/DataEvolutionEdge.h"
#include "Module.h"

class ModuleMutationOperator
{
  public:
    // ~ModuleMutationOperator();

    //ModuleMutationOperator(const ModuleMutationOperator);
    //ModuleMutationOperator operator=(const ModuleMutationOperator);

    static void mutate(Module *module,
                       DataEvolutionNode *_den,
                       DataEvolutionEdge *_dee);

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
};


#endif // __MODULE_MUTATION_OPERATOR_H__
