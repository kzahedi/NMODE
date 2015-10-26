#include "Individual.h"
#include "RNN.h"

class RnnFromIndividual
{
  public:
    // RnnFromIndividual();
    // ~RnnFromIndividual();

    //RnnFromIndividual(const RnnFromIndividual);
    //RnnFromIndividual operator=(const RnnFromIndividual);

    static RNN* create(Individual*);

  private:

    static Neuron* __createNeuron(Node *n) throw (NMODEException);
    static Node*   __getNonHiddenNode(Individual* ind, Node *node);
};

