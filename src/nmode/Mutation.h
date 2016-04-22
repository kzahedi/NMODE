#ifndef __NMODE_MUTATION_H__
#define __NMODE_MUTATION_H__

#include <nmode/Population.h>
#include <nmode/Individual.h>
#include <nmode/Module.h>
#include <nmode/CfgMutationEdge.h>
#include <nmode/CfgMutationNode.h>

class Mutation
{
  public:
    Mutation();
    // ~Mutation();

    //Mutation(const Mutation);
    //Mutation operator=(const Mutation);

    void mutate(Population*);
    void mutate(Individual*);
    bool mutate(Module*, CfgMutationNode*, CfgMutationEdge*);

  private:
    void __mutateDelEdge(Module*,    double);
    void __mutateModifyEdge(Module*, double, double, double);
    void __mutateAddEdge(Module*,    double, double);
    void __mutateAddSelf(Module*,    double, double);
    void __mutateAddNode(Module*,    double, double);
    void __mutateModifyNode(Module*, double, double, double);
    void __mutateDelNode(Module*,    double);
    void __cleanup(Module*);

};

#endif // __MUTATION_H__
