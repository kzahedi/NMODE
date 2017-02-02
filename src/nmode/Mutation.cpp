#include <nmode/Mutation.h>

#include <glog/logging.h>

#include <nmode/macros.h>
#include <nmode/Random.h>
#include <nmode/Data.h>

#include <sstream>

#define FORALLEDGES for(Edges::iterator e = m->e_begin(); e != m->e_end(); e++)
#define FORALLNODES for(Nodes::iterator n = m->n_begin(); n != m->n_end(); n++)

#define MIN_DIST 0.25

#define LOG_MODULE \
  VLOG(50) << "     Module: " << m->name();\
  for(Nodes::iterator n = m->n_begin(); n != m->n_end(); n++) \
    VLOG(50) << "      Node: " << (*n)->label() << " " << (*n)->bias(); \
  for(Edges::iterator e = m->e_begin(); e != m->e_end(); e++) \
    VLOG(50) << "      Edge: " << (*e)->source() << " -> " <<  (*e)->destination() << " = " << (*e)->weight();


Mutation::Mutation()
{
}

void Mutation::mutate(Population *p)
{
  VLOG(50) << ">> start mutate population: " << p->i_size();
  for(Individuals::iterator ind = p->i_begin(); ind != p->i_end(); ind++)
  {
    mutate(*ind);
  }
  VLOG(50) << ">> end mutate population";
}

void Mutation::mutate(Individual *i)
{
  VLOG(50) << ">> start mutate population";
  Data *data = Data::instance();
  CfgMutationEdge *dee = data->specification()->mutation()->edge();
  CfgMutationNode *den = data->specification()->mutation()->node();
  bool modified = false;
  int attemps = 0;
  while(modified == false && attemps < 10000)
  {
    attemps++;
    for(Modules::iterator mod = i->m_begin(); mod != i->m_end(); mod++)
    {
      if((*mod)->isCopy() == false)
      {
        modified |= mutate(*mod, den, dee);
      }
    }
  }
  VLOG(50) << ">> end mutate individual";
}


bool Mutation::mutate(Module *m, CfgMutationNode *den, CfgMutationEdge *dee)
{
  VLOG(50) << ">> mutate";
  m->setModified(false);

  CfgMutationEdge *e = dee;
  CfgMutationNode *n = den;

  if(m->mutation() != NULL)
  {
    e = m->mutation()->edge();
    n = m->mutation()->node();
    VLOG(50) << "** Found module specific mutation parameters:" << m->name();
    VLOG(50) << *n;
    VLOG(50) << *e;
  }
  else
  {
    VLOG(50) << "## Did not find module specific mutation parameters:" << m->name();
    VLOG(50) << *n;
    VLOG(50) << *e;
  }

  m->setModified(false);
  VLOG(50) << "### BEFORE MUTATION";
  LOG_MODULE;
  __mutateDelEdge(m,    e->delProbability());
  __mutateModifyEdge(m, e->modifyProbability(),
                        e->modifyDelta(),
                        e->modifyMaxValue());
  __mutateModifyNode(m, n->modifyProbability(),
                        n->modifyDelta(),
                        n->modifyMaxValue());
  __mutateDelNode(m,    n->delProbability());
  __mutateAddNode(m,    n->addProbability(),
                        n->addMaxValue());
  __mutateAddEdge(m,    e->addProbability(),
                        e->addMaxValue(),
                        e->minDistance());
  // __mutateAddSelf(m,    e->selfProbability(),
                        // e->selfMaxValue());
  __cleanup(m);
  VLOG(50) << "<< mutate";
  VLOG(50) << "### AFTER MUTATION";
  LOG_MODULE;
  VLOG(50) << "### AFTER MUTATION";
  return m->modified();
}

void Mutation::__mutateDelEdge(Module *m, double probability)
{
  if(m->e_size() == 0) return;
  VLOG(50) << ">>>>> del edge";
  LOG_MODULE;

  int nr_of_synapses_to_removed = (int)(Random::unit() * probability * m->e_size());

  for(int i = 0; i < nr_of_synapses_to_removed; i++)
  {
    m->setModified(true);
    int edgeIndex = (int)(Random::unit() * m->e_size());
    m->removeEdge(m->edge(edgeIndex));
  }

  LOG_MODULE;
  VLOG(50) << "<<<<< del edge";
}

void Mutation::__mutateModifyEdge(Module *m,
                                  double probability,
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

void Mutation::__mutateAddEdge(Module *m,
                               double probability,
                               double max,
                               double minDist)
{
  VLOG(50) << ">>>>> add edge";
  LOG_MODULE;
  CfgMutationEdge *dee = Data::instance()->specification()->mutation()->edge();

  double probabilities[m->n_size()][m->n_size()];
  double d   =  0.0;

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
    if(src_node->isInactive()) continue;
    if(src_node->isSource())
    {
      for(int d_index = 0; d_index < m->n_size(); d_index++)
      {
        Node *dst_node = m->node(d_index);
        if(dst_node->isInactive()) continue;
        if(dst_node->isDestination())
        {
          if(dst_node->contains(src_node) == false)
          {
            // USE FIXED PROBABILITY FOR ALL EDGES
            d = MAX(minDist, DIST(src_node->position(), dst_node->position()));
            if(d < MIN_DIST) d = 0;
            // probabilities[s_index][d_index] = exp(-d);
            if(dee->mode() == EDGE_ADD_MODE_UNIFORM)
            {
              probabilities[s_index][d_index] = 1.0;
            }
            else
            {
              probabilities[s_index][d_index] = 1.0/d;
            }

            VLOG(50) << "    edge from "
              << src_node->label() << " to "
              << dst_node->label() << " does not exist. setting distance to " << d;
            // probabilities[s_index][d_index] = 1.0;
          }
        }
      }
    }
  }

  double pmax =  0.0;
  if(dee->mode() == EDGE_ADD_MODE_DISTANCE)
  {
    for(int s_index = 0; s_index < m->n_size(); s_index++)
    {
      for(int d_index = 0; d_index < m->n_size(); d_index++)
      {
        if(pmax < probabilities[s_index][d_index]) pmax = probabilities[s_index][d_index];
      }
    }
  }

  if(pmax > 0.0)
  {
    for(int s_index = 0; s_index < m->n_size(); s_index++)
    {
      for(int d_index = 0; d_index < m->n_size(); d_index++)
      {
        // cout << probabilities[s_index][d_index] << " -> ";
        probabilities[s_index][d_index] = probabilities[s_index][d_index] / pmax;
        // cout << probabilities[s_index][d_index] << endl;
      }
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
    sst.unsetf(std::ios::fixed);
    VLOG(50) << sst.str();
  }

  for(int s_index = 0; s_index < m->n_size(); s_index++)
  {
    for(int d_index = 0; d_index < m->n_size(); d_index++)
    {
      double p = probabilities[s_index][d_index] * probability;
      if(Random::unit() <= p)
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
        LOG_MODULE;
        VLOG(50) << "<<<<< add edge";
        m->setModified(true);
      }
    }
  }

  LOG_MODULE;
  VLOG(50) << "<<<<< add edge";
}

void Mutation::__mutateAddNode(Module *m, double probability, double max)
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

  double p  = Random::unit();
  double s  = 0.0;
  int    ei = -1;

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
  bool found = true;
  int newNodeIndex = -1;
  while(found == true)
  {
    newNodeIndex++;
    oss.str("");
    oss << "hidden " << newNodeIndex;
    found = m->nodeExists(oss.str());
  }
  VLOG(50) << "new node name: " << oss.str();
  n->setType("hidden");
  n->setPosition(np);
  n->setBias(Random::rand(-max, max));
  n->setLabel(oss.str());
  n->setTransferfunction("tanh");

  e->setSourceNode(n);
  m->addNode(n);
  Edge *ne = m->addEdge(src, n, 1.0);
  LOG_MODULE;

  VLOG(50) << "    node added with label " << n->label();
  VLOG(50) << "    adding edge from: " << src->label() << " " << n->label();
  VLOG(50) << "    source neuron's position " << src->position();
  VLOG(50) << "    destination neuron's position " << dst->position();
  VLOG(50) << "    new neuron's position " << n->position();
  VLOG(50) << "    new synapse goes from " << e->sourceNode()->label() << " -> "
           << e->destinationNode()->label() << " with " << e->weight();
  VLOG(50) << "    new synapse goes from " << ne->sourceNode()->label() << " -> "
           << ne->destinationNode()->label() << " with " << ne->weight();
  VLOG(50) << "<<<<< add node";
}

void Mutation::__mutateModifyNode(Module *m,
                                  double probability,
                                  double delta,
                                  double max)
{
  // if(Random::unit() >= probability) return;
  VLOG(50) << ">>>>> modify node";
  LOG_MODULE;
  VLOG(50) << "    will modify one node";

  // int ni        = int(Random::unit() * m->n_size());
  // Node *n       = m->node(ni);
  FORALLNODES
  {
    if((*n)->type() == TAG_CONNECTOR || (*n)->isInactive() == true) continue;
    if(Random::unit() >= probability) continue;
    m->setModified(true);
    double value  = (*n)->bias();
    double d  = Random::rand(-delta, delta);
    value        += d;
    if(value >  max) value =  max;
    if(value < -max) value = -max;
    (*n)->setBias(value);
    VLOG(50) << "  ****** node bias set to " << (*n)->bias();
  }
  LOG_MODULE;
  VLOG(50) << "<<<<< modify node";
}


void Mutation::__mutateDelNode(Module *m, double probability)
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


void Mutation::__cleanup(Module *m)
{
  VLOG(50) << ">>>>> clean up";
  LOG_MODULE;
  for(Edges::iterator e = m->e_begin(); e != m->e_end(); e++)
  {
    if((*e)->sourceNode() == NULL || (*e)->destinationNode() == NULL) m->removeEdge(*e);
  }
  Edges toBeRemoved;
  for(Edges::iterator e = m->e_begin(); e != m->e_end(); e++)
  {
    for(Edges::iterator f = m->e_begin(); f != m->e_end(); f++)
    {
      if((*e)->sourceNode()->label() == (*f)->sourceNode()->label() &&
         (*e)->sourceNode()          != (*f)->sourceNode()          &&
         (*e)                        != (*f))
      {
        toBeRemoved.push_back(*e);
      }
    }
  }
  for(Edges::iterator e = toBeRemoved.begin(); e != toBeRemoved.end(); e++)
  {
    m->removeEdge(*e);
  }
  LOG_MODULE;
  VLOG(50) << "<<<<< clean up";
}
