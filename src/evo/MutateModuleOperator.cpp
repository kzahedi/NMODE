#include "MutateModuleOperator.h"

#include <glog/logging.h>

#include "base/macros.h"
#include "base/Random.h"
#include "base/Module.h"

#include <sstream>

// MutateModuleOperator::MutateModuleOperator()
// {
// }

#define FORALLEDGES for(Edges::iterator e = m->e_begin(); e != m->e_end(); e++)
#define FORALLNODES for(Nodes::iterator n = m->n_begin(); n != m->n_end(); n++)

#define LOG_MODULE \
  VLOG(50) << "     Module: " << m->name();\
  for(Nodes::iterator n = m->n_begin(); n != m->n_end(); n++) \
    VLOG(50) << "      Node: " << (*n)->label(); \
  for(Edges::iterator e = m->e_begin(); e != m->e_end(); e++) \
    VLOG(50) << "      Edge: " << (*e)->source() << " -> " <<  (*e)->destination() << " = " << (*e)->weight();


void MutateModuleOperator::mutate(Module *m,
                                  EvolutionNode *den,
                                  EvolutionEdge *dee)
{
  VLOG(50) << ">> mutate";
  m->setModified(false);
  while(m->modified() == false)
  {
    __mutateDelEdge(m,    dee->delProbability());
    __mutateModifyEdge(m, dee->modifyProbability(),
                          dee->modifyDelta(),
                          dee->modifyMaxValue());
    __mutateAddEdge(m,    dee->addProbability(),
                          dee->addMaxValue());
    __mutateModifyNode(m, den->modifyProbability(),
                          den->modifyDelta(),
                          den->modifyMaxValue());
    __mutateDelNode(m,    den->delProbability());
    __mutateAddNode(m,    den->addProbability(),
                          den->addMaxValue());
    __cleanup(m);
  VLOG(50) << "<< mutate";
  }
}

void MutateModuleOperator::__mutateDelEdge(Module *m, double probability)
{
  if(m->e_size()    == 0)           return;
  if(Random::unit() >= probability) return;
  VLOG(50) << ">>>>> del edge";
  LOG_MODULE;
  m->setModified(true);
  double weights[m->e_size()];
  double sum = 0.0;

  for(int i = 0; i < m->e_size(); i++)
  {
    double w = m->edge(i)->weight();
    weights[i] = fabs(w);
    sum += fabs(w);
  }

  for(int i = 0; i < m->e_size(); i++)
  {
    weights[i] /= sum;
  }

  if(VLOG_IS_ON(50))
  {
    stringstream sst;
    sst << "    weights " << weights[0];
    for(int i = 1; i < m->e_size(); i++)
    {
      sst << " " << weights[i];
    }
    VLOG(50) << "  weights " << sst.str();
  }

  double p = Random::unit();
  double s = 0.0;

  VLOG(50) << "    p = " << p;

  for(int i = 0; i < m->e_size(); i++)
  {
    s += weights[i];
    if(s <= p)
    {
      VLOG(50) << "    removing edge " << i << ": "
               << m->edge(i)->source()
               << " -> "
               << m->edge(i)->destination() << " with "
               << m->edge(i)->weight();
      m->removeEdge(m->edge(i));
      return;
    }
  }
  LOG_MODULE;
  VLOG(50) << "<<<<< del edge";
}

void MutateModuleOperator::__mutateModifyEdge(Module *m, double probability,
                                                           double delta,
                                                           double max)
{
  VLOG(50) << ">>>>> modify edge";
  LOG_MODULE;
  FORALLEDGES
  {
    if(Random::unit() < probability)
    {
      VLOG(50) << "    will modify edge " << (*e)->source()
               << " -> " <<  (*e)->destination()
               << ": " << (*e)->weight();
      m->setModified(true);
      double weight = (*e)->weight()+ (2.0 * Random::unit() - 1.0) * delta;
      if(weight >  max) weight =  max;
      if(weight < -max) weight = -max;
      (*e)->setWeight(weight);
      VLOG(50) << "    new weight is " << (*e)->weight();
    }
  }
  LOG_MODULE;
  VLOG(50) << "<<<<< modify edge";
}

void MutateModuleOperator::__mutateAddEdge(Module *m, double probability,
                                                        double max)
{
  if(Random::unit() >= probability) return;
  VLOG(50) << ">>>>> add edge";
  LOG_MODULE;
  m->setModified(true);

  double probabilities[m->n_size()][m->n_size()];
  double d   =  0.0;
  double min = -1.0;


  for(int s_index = 0; s_index < m->n_size(); s_index++)
  {
    for(int d_index = 0; d_index < m->n_size(); d_index++)
    {
      probabilities[s_index][d_index] = 0.0;
    }
  }

  for(int s_index = 0; s_index < m->n_size(); s_index++)
  {
    Node *src_node = m->node(s_index);

    if(src_node->isSource())
    {

      for(int d_index = 0; d_index < m->n_size(); d_index++)
      {
        Node *dst_node = m->node(d_index);

        if(dst_node->isDestination())
        {

          if(dst_node->contains(src_node))
          {
            VLOG(50) << "    edge from "
              << src_node->label() << " to "
              << dst_node->label() << " already exists";
            probabilities[s_index][d_index] = 0.0;
          }
          else
          {

            d  = DIST(src_node->position(), dst_node->position());
            d *= d;
            probabilities[s_index][d_index] = d;
            if(min < 0.0) min = d;
            if(min < d)   min = d;
            VLOG(50) << "    edge from "
              << src_node->label() << " to "
              << dst_node->label() << " does not exist. setting distance to " << d;
          }
        }
      }
    }
  }

  double sum =  0.0;
  for(int s_index = 0; s_index < m->n_size(); s_index++)
  {
    for(int d_index = 0; d_index < m->n_size(); d_index++)
    {
      if(probabilities[s_index][d_index] > 0.0)
      {
        probabilities[s_index][d_index] = min / probabilities[s_index][d_index];
        sum += probabilities[s_index][d_index];
      }
    }
  }

  for(int s_index = 0; s_index < m->n_size(); s_index++)
  {
    for(int d_index = 0; d_index < m->n_size(); d_index++)
    {
      probabilities[s_index][d_index] = probabilities[s_index][d_index] / sum;
    }
  }

  if(VLOG_IS_ON(50))
  {
    stringstream sst;
    sst << "    probabilities " << m->n_size() << "x" << m->n_size();
    sst.precision(3);
    sst.setf(ios::fixed,ios::floatfield);
    sst << "[ ";
    for(int s_index = 0; s_index < m->n_size(); s_index++)
    {
      sst << " [ " << probabilities[s_index][0];
      for(int d_index = 0; d_index < m->n_size(); d_index++)
      {
        sst << ", " << probabilities[s_index][d_index];
      }
      sst << " ]";
    }
    sst << " ]";
    VLOG(50) << sst.str();
  }

  double p  = Random::unit();
  double s  = 0.0;
  VLOG(50) << "    p = " << p;
  for(int s_index = 0; s_index < m->n_size(); s_index++)
  {
    for(int d_index = 0; d_index < m->n_size(); d_index++)
    {
      s += probabilities[s_index][d_index];
      VLOG(50) << "    s = " << s;
      if(p <= s)
      {
        Node *src = m->node(s_index);
        Node *dst = m->node(d_index);
        VLOG(50) << "    adding edge from " << src->label() << " -> " << dst->label();
        VLOG(50) << "    before number of edges: " << m->e_size();
        Edge *e   = m->addEdge(src, dst, Random::rand(-max, max));
        VLOG(50) << "    adding edge from "
                 << m->node(s_index)->label() << " to "
                 << m->node(d_index)->label() << " with "
                 << e->weight();
        VLOG(50) << "    after number of edges: " << m->e_size();
        return;
      }
    }
  }
  LOG_MODULE;
  VLOG(50) << "<<<<< add edge";
}

void MutateModuleOperator::__mutateAddNode(Module *m, double probability, double max)
{
  if(m->e_size() == 0) return;
  if(Random::unit() >= probability) return;
  VLOG(50) << ">>>>> add node";
  LOG_MODULE;
  VLOG(50) << "    number of edges: " << m->e_size();
  VLOG(50) << "    will add one node";
  m->setModified(true);

  double probabilities[m->e_size()];
  double sum = 0;
  for(int i = 0; i < m->e_size(); i++)
  {
    double d = DIST(m->edge(i)->sourceNode()->position(),
                    m->edge(i)->destinationNode()->position());
    sum += d;
    probabilities[i] = d;
  }

  if(sum < 0.000001) return; // only self connections so far

  for(int i = 0; i < m->e_size(); i++) probabilities[i] /= sum;

  // if(VLOG_IS_ON(50))
  // {
    // cout << "probabilities:";
    // for(int i = 0; i < m->e_size(); i++) cout << " " << probabilities[i];
    // cout << endl;
  // }

  double p = Random::unit();
  double s = 0.0;
  int ei = -1;
  for(int i = 0; i < m->e_size(); i++)
  {
    s += probabilities[i];
    if(p <= s)
    {
      ei = i;
      break;
    }
  }

  VLOG(50) << "    edge index into which a neuron will be inserted: " << ei;

  Node *n = new Node(NULL);

  Edge *e   = m->edge(ei);
  Node *src = e->sourceNode();
  Node *dst = e->destinationNode();

  P3D sp    = src->position();
  P3D dp    = dst->position();
  P3D np    = (sp + dp) * 0.5;

  stringstream oss;
  oss << "hidden " << m->getNewNodeId();
  n->setType("hidden");
  n->setPosition(np);
  n->setBias(Random::rand(-max, max));
  n->setLabel(oss.str());
  n->setTransferfunction("tanh");

  VLOG(50) << "    node added with label " << n->label();

  e->setSourceNode(n);
  VLOG(50) << "    adding edge from: " << src->label() << " " << n->label();
  Edge *ne = m->addEdge(src, n, 1.0);
  VLOG(50) << "    source neuron's position " << src->position();
  VLOG(50) << "    destination neuron's position " << dst->position();
  VLOG(50) << "    new neuron's position " << n->position();
  VLOG(50) << "    new synapse goes from " << e->source() << " -> "
           << e->destination() << " with " << e->weight();
  VLOG(50) << "    new synapse goes from " << ne->source() << " -> "
           << ne->destination() << " with " << ne->weight();

  m->addNode(n);
  LOG_MODULE;
  VLOG(50) << "<<<<< add node";
}

void MutateModuleOperator::__mutateModifyNode(Module *m, double probability,
                                                           double delta,
                                                           double max)
{
  if(Random::unit() >= probability) return;
  VLOG(50) << ">>>>> modify node";
  LOG_MODULE;
  VLOG(50) << "    will modify one node";
  m->setModified(true);

  int ni        = int(Random::unit() * m->n_size());
  Node *n       = m->node(ni);
  double value  = n->bias();
  value        += Random::rand(-delta, delta);
  if(value >  max) value =  max;
  if(value < -max) value = -max;
  n->setBias(value);
  LOG_MODULE;
  VLOG(50) << "<<<<< modify node";
}


void MutateModuleOperator::__mutateDelNode(Module *m, double probability)
{
  if(m->h_size() == 0) return; // no hidden node to remove
  if(Random::unit() >= probability) return;
  VLOG(50) << ">>>>> del node";
  LOG_MODULE;
  m->setModified(true);

  int ni   = int(Random::unit() * m->h_size());
  Node *nn = m->hiddenNode(ni);
  VLOG(50) << "    will remove hidden node (index: " << ni << ") label " << nn->label();
  m->removeNode(nn);
  LOG_MODULE;
  VLOG(50) << "<<<<< del node";
}


void MutateModuleOperator::__cleanup(Module *m)
{
  VLOG(50) << ">>>>> clean up";
  LOG_MODULE;
  for(Edges::iterator e = m->e_begin(); e != m->e_end(); e++)
  {
    if((*e)->sourceNode() == NULL || (*e)->destinationNode() == NULL) m->removeEdge(*e);
  }
  LOG_MODULE;
  VLOG(50) << "<<<<< clean up";
}
