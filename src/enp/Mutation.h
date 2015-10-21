#ifndef __MUTATION_H__
#define __MUTATION_H__
#include "Population.h"
#include "Individual.h"
#include "Module.h"
#include "EvolutionEdge.h"
#include "EvolutionNode.h"

class Mutation
{
  public:
    Mutation();
    // ~Mutation();

    //Mutation(const Mutation);
    //Mutation operator=(const Mutation);

    void mutate(Population*);
    void mutate(Individual*);
    void mutate(Module*, EvolutionNode*, EvolutionEdge*);

  private:
    void __mutateDelEdge(Module*,    double);
    void __mutateModifyEdge(Module*, double, double, double);
    void __mutateAddEdge(Module*,    double, double);
    void __mutateAddNode(Module*,    double, double);
    void __mutateModifyNode(Module*, double, double, double);
    void __mutateDelNode(Module*,    double);
    void __cleanup(Module*);

};

#endif // __MUTATION_H__
