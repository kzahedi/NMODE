#include "ModuleMutationOperator.h"

#include <glog/logging.h>

#include "base/macros.h"
#include "base/Random.h"

#include <sstream>

// ModuleMutationOperator::ModuleMutationOperator()
// {
// }

#define FORALLEDGES for(Edges::iterator e = m->e_begin(); e != m->e_end(); e++)
#define FORALLNODES for(Nodes::iterator n = m->n_begin(); n != m->n_end(); n++)

#define DIST(a, b) sqrt((a.x - b.x) * (a.x - b.x) +\
                        (a.y - b.y) * (a.y - b.y) +\
                        (a.z - b.z) * (a.z - b.z))

void ModuleMutationOperator::mutate(Module *m,
                                    DataEvolutionNode *den,
                                    DataEvolutionEdge *dee)
{
  VLOG(50) << "starting mutate";
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
    __mutateAddNode(m,    den->addProbability(),
                          den->addMaxValue());
    __mutateDelNode(m,    den->delProbability());
  }
}

void ModuleMutationOperator::__mutateDelEdge(Module *m, double probability)
{
  VLOG(50) << "mutate del edge called";
  if(m->e_size()    == 0)           return;
  if(Random::unit() >= probability) return;
  VLOG(50) << "  will mutate edge";
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
    sst << weights[0];
    for(int i = 1; i < m->e_size(); i++)
    {
      sst << " " << weights[i];
    }
    VLOG(50) << sst.str();
  }

  double p = Random::unit();
  double s = 0.0;

  VLOG(50) << "p = " << p;

  for(int i = 0; i < m->e_size(); i++)
  {
    s += weights[i];
    if(s <= p)
    {
      VLOG(50) << "removing edge " << i << ": " << m->edge(i)->source()->label() << " -> "
               << m->edge(i)->destination()->label() << " with "
               << m->edge(i)->weight();
      m->removeEdge(m->edge(i));
      return;
    }
  }
}

void ModuleMutationOperator::__mutateModifyEdge(Module *m, double probability,
                                                           double delta,
                                                           double max)
{
  VLOG(50) << "mutate modify edge called";
  FORALLEDGES
  {
    if(Random::unit() < probability)
    {
      VLOG(50) << "  will modify edge " << (*e)->source()->label()
               << " -> " <<  (*e)->destination()->label()
               << ": " << (*e)->weight();
      m->setModified(true);
      double weight = (*e)->weight()+ (2.0 * Random::unit() - 1.0) * delta;
      if(weight >  max) weight =  max;
      if(weight < -max) weight = -max;
      (*e)->setWeight(weight);
      VLOG(50) << "new weight is " << (*e)->weight();
    }
  }
}

void ModuleMutationOperator::__mutateAddEdge(Module *m, double probability,
                                                        double max)
{
  VLOG(50) << "mutate add edge called";
  if(Random::unit() >= probability) return;
  VLOG(50) << "  will add one edge";
  m->setModified(true);

  double probabilities[m->src_indices_size()][m->dst_indices_size()];
  double d   =  0.0;
  double min = -1.0;

  for(int s_index = 0; s_index < m->src_indices_size(); s_index++)
  {
    Node *src_node = m->node(m->src_index(s_index));
    for(int d_index = 0; d_index < m->dst_indices_size(); d_index++)
    {
      Node *dst_node = m->node(m->dst_index(d_index));
      if(src_node->contains(dst_node))
      {
        VLOG(50) << "edge from " << s_index << " to " << d_index << " already exists";
        probabilities[s_index][d_index] = 0.0;
      }
      else
      {
        VLOG(50) << "source node position " << src_node->position();
        VLOG(50) << "destination node position " << dst_node->position();
        d = DIST(src_node->position(), dst_node->position()) + 1.0;
        probabilities[s_index][d_index] = d;
        if(min < 0.0) min = d;
        if(min < d)   min = d;
        VLOG(50) << "edge from " << s_index << " to " << d_index << " does not exist. setting distance to " << d;
      }
    }
  }

  double sum =  0.0;
  for(int s_index = 0; s_index < m->src_indices_size(); s_index++)
  {
    for(int d_index = 0; d_index < m->dst_indices_size(); d_index++)
    {
      if(probabilities[s_index][d_index] > 0.0)
      {
        probabilities[s_index][d_index] = min / probabilities[s_index][d_index];
        sum += probabilities[s_index][d_index];
      }
    }
  }

  for(int s_index = 0; s_index < m->src_indices_size(); s_index++)
  {
    for(int d_index = 0; d_index < m->dst_indices_size(); d_index++)
    {
      probabilities[s_index][d_index] = probabilities[s_index][d_index] / sum;
    }
  }

  if(VLOG_IS_ON(50))
  {
    stringstream sst;
    sst << "probabilities " << m->src_indices_size() << "x" << m->dst_indices_size();
    sst.precision(3);
    sst.setf(ios::fixed,ios::floatfield);
    sst << "[ ";
    for(int s_index = 0; s_index < m->src_indices_size(); s_index++)
    {
      sst << " [ " << probabilities[s_index][0];
      for(int d_index = 0; d_index < m->dst_indices_size(); d_index++)
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
  VLOG(50) << "p = " << p;
  for(int s_index = 0; s_index < m->n_size(); s_index++)
  {
    for(int d_index = m->s_size(); d_index < m->n_size(); d_index++)
    {
      s += probabilities[s_index][d_index];
      if(p <= s)
      {
        Node *src = m->node(s_index);
        Node *dst = m->node(d_index);
        VLOG(50) << "adding edge from " << src->label() << " -> " << dst->label();
        Edge *e   = m->addEdge(src, dst, Random::rand(-max, max));
        VLOG(50) << "adding edge from " << m->node(s_index)->label() << " to "
                                        << m->node(d_index)->label() << " with "
                                        << e->weight();
        return;
      }
    }
  }
}

void ModuleMutationOperator::__mutateAddNode(Module *m, double probability, double max)
{
  VLOG(50) << "mutate add node called";
  if(Random::unit() >= probability) return;
  VLOG(50) << "  will add one node";
  m->setModified(true);

  int ei    = int(Random::unit() * m->e_size() + 0.5); // edge index
  VLOG(50) << "edge index into which a neuron will be inserted: " << ei;

  Node *n   = new Node();

  Edge *e   = m->edge(ei);
  Node *src = e->source();
  Node *dst = e->destination();

  P3D sp    = src->position();
  P3D dp    = dst->position();
  P3D np    = (sp + dp) * 0.5;

  stringstream oss;
  oss << "hidden " << m->n_size();
  n->setType("hidden");
  n->setPosition(np);
  n->setBias(Random::rand(-max, max));
  n->setLabel(oss.str());

  e->setSource(n);
  VLOG(50) << "adding node from: " << src->label() << " " << n->label();
  Edge *ne = m->addEdge(src, n, 1.0);
  VLOG(50) << "source neuron's position " << src->position();
  VLOG(50) << "destination neuron's position " << dst->position();
  VLOG(50) << "new neuron's position " << n->position();
  VLOG(50) << "new synapse goes from " << e->source()->label() << " -> "
           << e->destination()->label() << " with " << e->weight();
  VLOG(50) << "new synapse goes from " << ne->source()->label() << " -> "
           << ne->destination()->label() << " with " << ne->weight();

}

void ModuleMutationOperator::__mutateModifyNode(Module *m, double probability,
                                                           double delta,
                                                           double max)
{
  VLOG(50) << "mutate modify node called";
  if(Random::unit() >= probability) return;
  VLOG(50) << "  will modify one node";
  m->setModified(true);

  int ni        = int(Random::unit() * m->n_size() + 0.5);
  Node *n       = m->node(ni);
  double value  = n->bias();
  value        += Random::rand(-delta, delta);
  if(value >  max) value =  max;
  if(value < -max) value = -max;
  n->setBias(value);
}


void ModuleMutationOperator::__mutateDelNode(Module *m, double probability)
{
  VLOG(50) << "mutate del node called";
  if(Random::unit() >= probability) return;
  VLOG(50) << "  will del one node";
  m->setModified(true);

  int ni   = int(Random::unit() * m->n_size() + 0.5);
  Node *nn = m->node(ni);
  FORALLNODES (*n)->removeEdge(nn);
}
