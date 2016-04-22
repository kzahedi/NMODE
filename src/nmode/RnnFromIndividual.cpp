#include <nmode/RnnFromIndividual.h>

#include <nmode/macros.h>

#include <map>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

RNN* RnnFromIndividual::create(Individual *i)
{
  RNN *rnn = new RNN();

  map<Node*, Neuron*> nodeNeuronMap;

  Individual *ind = i->getRealisation();

  FORF(Modules, m, ind, m_begin(), m_end())
  {
    FORF(Nodes, n, *m, n_begin(), n_end())
    {
      if((*n)->type() != TAG_CONNECTOR)
      {
        Neuron *neuron = __createNeuron(*n);

        nodeNeuronMap.insert(std::make_pair(*n, neuron));

        if((*n)->type() == TAG_SENSOR)
        {
          rnn->addInputNeuron(neuron);
        }
        else if((*n)->type() == TAG_ACTUATOR)
        {
          rnn->addOutputNeuron(neuron);
        }
        else if((*n)->type() == TAG_INPUT ||
                (*n)->type() == TAG_OUTPUT ||
                (*n)->type() == TAG_HIDDEN )
        {
          rnn->addHiddenNeuron(neuron);
        }
      }
    }
  }

  FORF(Modules, m, ind, m_begin(), m_end())
  {
    FORF(Edges, e, *m, e_begin(), e_end())
    {
      Node *srcNode = (*e)->sourceNode();
      Node *dstNode = (*e)->destinationNode();

      if(srcNode->type() == TAG_CONNECTOR) srcNode = __getNonHiddenNode(ind, srcNode);
      if(dstNode->type() == TAG_CONNECTOR) dstNode = __getNonHiddenNode(ind, dstNode);

      Neuron *srcNeuron = nodeNeuronMap.find(srcNode)->second;
      Neuron *dstNeuron = nodeNeuronMap.find(dstNode)->second;

      Synapse *s = new Synapse();
      s->setSource(srcNeuron);
      s->setWeight((*e)->weight());
      dstNeuron->addSynapse(s);
    }
  }

  delete ind;

  return rnn;
}

Neuron* RnnFromIndividual::__createNeuron(Node *n) throw (NMODEException)
{
  Neuron *neuron = new Neuron();
  neuron->setBias(n->bias());
  if(n->transferfunction() == TAG_ID)
  {
    neuron->setTransferfunction(NEURON_TRANSFER_FUNCTION_ID);
  }
  else if(n->transferfunction() == TAG_TANH)
  {
    neuron->setTransferfunction(NEURON_TRANSFER_FUNCTION_TANH);
  }
  else if(n->transferfunction() == TAG_SIGM)
  {
    neuron->setTransferfunction(NEURON_TRANSFER_FUNCTION_SIGM);
  }
  else
  {
    throw NMODEException("RnnFromIndividual: unknown transfer function");
  }
  return neuron;
}

Node* RnnFromIndividual::__getNonHiddenNode(Individual* ind, Node *node)
{
  vector<string> strs;
  string label = node->label();
  split(strs, label, is_any_of("/"));
  string moduleName = trim(strs[0]);
  string nodeName   = trim(strs[1]);

  FORF(Modules, m, ind, m_begin(), m_end())
  {
    if((*m)->name() == moduleName)
    {
      FORF(Nodes, n, *m, n_begin(), n_end())
      {
        if((*n)->label() == nodeName)
        {
          return (*n);
        }
      }
    }
  }
  return NULL;
}
