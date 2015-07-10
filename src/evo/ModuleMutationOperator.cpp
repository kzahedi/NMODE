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
                        (a.z - b.z) * (a.z - b.z));

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
    weights[i] = w;
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

  double probabilities[m->n_size()][m->a_size() + m->h_size()];
  double sum = 0.0;
  double d   = 0.0;

  cout << " hier 0: " << m->n_size() << endl;
  for(int s_index = 0; s_index < m->n_size(); s_index++)
  {
    cout << " hier 100 " << endl;
    Node *src_node = m->node(s_index);
    for(int d_index = 0; d_index < m->n_size() - m->s_size(); d_index++)
    {
      cout << " hier 101 " << endl;
      Node *dst_node = m->node(d_index + m->s_size());
      if(src_node->contains(dst_node))
      {
        cout << " hier 102 " << endl;
        d    = DIST(src_node->position(), dst_node->position());
        sum += d;
        probabilities[s_index][d_index] = d;
      }
      else
      {
        cout << " hier 103: " << s_index << " " << d_index << endl;
        probabilities[s_index][d_index] = 0.0;
      }
    }
  }

  cout << " hier 1 " << endl;

  for(int s_index = 0; s_index < m->n_size(); s_index++)
  {
    for(int d_index = 0; d_index < m->n_size() - m->s_size(); d_index++)
    {
      probabilities[s_index][d_index] /= sum;
    }
  }

  cout << " hier 2 " << endl;

  if(VLOG_IS_ON(50))
  {
    VLOG(50) << "probabilities";
    stringstream sst;
    sst.precision(3);
    sst.setf(ios::fixed,ios::floatfield);
    for(int s_index = 0; s_index < m->n_size(); s_index++)
    {
      sst << probabilities[s_index][0];
      for(int d_index = 1; d_index < m->n_size() - m->s_size(); d_index++)
      {
        sst << " " << probabilities[s_index][d_index];
      }
      sst << endl;
    }
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
        Edge *e   = m->addEdge(src, dst, Random::rand(-max, max));
        VLOG(50) << "adding edge from " << m->node(s_index)->label() << " to "
                                        << m->node(d_index)->label() << " with "
                                        << e->weight();

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
  m->addEdge(src, n, 1.0);
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
