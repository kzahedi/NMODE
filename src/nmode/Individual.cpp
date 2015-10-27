#include "Individual.h"

#include "glog/logging.h"

#include "nmode/macros.h"

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;
using namespace boost::algorithm;

#define TAG_ID        (char*)"id"
#define TAG_FITNESS   (char*)"fitness"
#define TAG_OFFSPRING (char*)"offspring"
#define TAG_CONNECTOR (char*)"connector"

Individual::Individual(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _id                 = 1;
  _fitness            = 0.0;
  _reproductionFactor = 0.0;
  _age                = 0;
  _nrOfOffspring      = 0;
  _rawFitness         = 0.0;
  _edgeCost           = 0.0;
  _nodeCost           = 0.0;
  _nrOfSynapses       = 0;
  _nrOfNeurons        = 0;
}

void Individual::add(ParseElement *element)
{
  VLOG(100) << "parsing " << element->name();

  if(element->closing(TAG_INDIVIDUAL))
  {
    linkConnectorNodes();
    VLOG(100) << "closing <Individual> " << element->name();
    current = parent;
  }

  if(element->opening(TAG_INDIVIDUAL))
  {
    VLOG(100) << "opening <Individual> " << element->name();
    element->set(TAG_ID,        _id);
    element->set(TAG_FITNESS,   _fitness);
    element->set(TAG_OFFSPRING, _nrOfOffspring);
    VLOG(100) << "setting id = " << _id << " fitness = " << _fitness << " offspring = " << _nrOfOffspring;
  }

  if(element->opening(TAG_MODULE))
  {
    Module *dpm = new Module(this);
    _modules.push_back(dpm);
    current = dpm;
    current->add(element);
  }
}

void Individual::createXsd(XsdSpecification *spec)
{
  XsdSequence *_root = new XsdSequence(TAG_INDIVIDUAL_DEFINITION);
  _root->add(NA(TAG_ID,        TAG_POSITIVE_INTEGER,  false));
  _root->add(NA(TAG_FITNESS,   TAG_XSD_DECIMAL,       false));
  _root->add(NA(TAG_OFFSPRING, TAG_POSITIVE_INTEGER,  false));
  _root->add(NE(TAG_MODULE,    TAG_MODULE_DEFINITION, 1, TAG_XSD_UNBOUNDED));
  spec->add(_root);

  Module::createXsd(spec);
}

int Individual::id()
{
  return _id;
}

double Individual::fitness()
{
  return _fitness;
}

Modules::iterator Individual::m_begin()
{
  return _modules.begin();
}

Modules::iterator Individual::m_end()
{
  return _modules.end();
}

int Individual::m_size()
{
  return _modules.size();
}

Modules Individual::modules()
{
  return _modules;
}

Module* Individual::module(int index)
{
  return _modules[index];
}

Module* Individual::moduleByName(string name)
{
  FORC(Modules, m, _modules) if((*m)->name() == name) return (*m);
  return NULL;
}

void Individual::setFitness(double f)
{
  _fitness = f;
}

void Individual::setId(int id)
{
  _id = id;
}

void Individual::addModule(Module *m)
{
  _modules.push_back(m);
}

Individual* Individual::getRealisation()
{
  VLOG(100) << "Individual::getRealisation";
  Individual *copy = new Individual(NULL);

  Modules mods;

  FORC(Modules, m, _modules)
  {
    VLOG(100) << "checking on " << (*m)->name();
    if((*m)->isCopy() == false)
    {
      VLOG(100) << "  its not a copy";
      Module *cm = (*m)->copy();
      mods.push_back(cm);
      copy->addModule(cm);
    }
  }

  FORC(Modules, m, _modules)
  {
    VLOG(100) << "checking on " << (*m)->name();
    if((*m)->isCopy())
    {
      VLOG(100) << "  it is a copy";
      FORC(Modules, c, mods)
      {
        if((*m)->ref() == (*c)->name())
        {
          Module *cm = (*m)->copy();
          VLOG(100) << "  found ref " << (*c)->name() << " for " << (*m)->name();
          cm->copyAndApplyTransition(*c);
          copy->addModule(cm);
        }
      }
    }
  }

  return copy;
}

Node* Individual::__getNonHiddenNodeFromModule(Module *m, string nodeLabel)
{
  FORF(Nodes, n, m, o_begin(), o_end()) if((*n)->label() == nodeLabel) return *n;
  FORF(Nodes, n, m, i_begin(), i_end()) if((*n)->label() == nodeLabel) return *n;
  FORF(Nodes, n, m, s_begin(), s_end()) if((*n)->label() == nodeLabel) return *n;
  FORF(Nodes, n, m, a_begin(), a_end()) if((*n)->label() == nodeLabel) return *n;
  return NULL;
}

Node* Individual::__getNonHiddenNode(string moduleName, string nodeLabel)
{
  Module *module = moduleByName(moduleName)->copy();
  if(module->isCopy())
  {
    Module *ref = moduleByName(module->ref());
    module->copyAndApplyTransition(ref);
  }
  Node *n = __getNonHiddenNodeFromModule(module, nodeLabel);
  delete module;
  return n;
}

void Individual::linkConnectorNodes() throw(NMODEException)
{
  VLOG(100) << "Individual::linkConnectorNodes";

  FORC(Modules, m, _modules)
  {
    VLOG(100) << "checking on " << (*m)->name();
    if((*m)->isCopy() == false)
    {
      for(Nodes::iterator n = (*m)->n_begin(); n != (*m)->n_end(); n++)
      {
        VLOG(100) << "checking if " << (*n)->label() << " is a connector node: " << (*n)->type();
        if((*n)->type() == TAG_CONNECTOR)
        {
          VLOG(100) << "found connector node " << (*n)->label();
          vector<string> strs;
          string label = (*n)->label();
          split(strs, label, is_any_of("/"));
          string module_name = trim(strs[0]);
          string node_name   = trim(strs[1]);
          Node* node         = __getNonHiddenNode(module_name, node_name);
          if(node == NULL)
          {
            stringstream sst;
            sst << "Node " << node_name << " not found in module " << module_name;
            throw NMODEException(sst.str());
          }
          (*n)->setPosition(node->position());
          (*n)->setIsSource(node->isSource());
          (*n)->setIsDestination(node->isDestination());
          (*n)->setTransferfunction(node->transferfunction());
          VLOG(100) << "Connector node " << (*n)->label() << ":";
          VLOG(100) << "  Position: " << (*n)->position();
        }
      }
    }
  }
}

double Individual::reproductionFactor()
{
  return _reproductionFactor;
}

void Individual::setReproductionFactor(double f)
{
  _reproductionFactor = f;
}

Individual* Individual::copy(bool reset)
{
  Individual *copy     = new Individual();
  if(reset)
  {
    copy->_fitness            = 0.0;
    copy->_reproductionFactor = 0.0;
    copy->_id                 = -1;
    copy->_age                = 0;
    copy->_nrOfOffspring      = 0;
    copy->_rawFitness         = 0.0;
    copy->_edgeCost           = 0.0;
    copy->_nodeCost           = 0.0;
  }
  else
  {
    copy->_fitness            = _fitness;
    copy->_reproductionFactor = _reproductionFactor;
    copy->_id                 = _id;
    copy->_age                = _age;
    copy->_nrOfOffspring      = _nrOfOffspring;
    copy->_rawFitness         = _rawFitness;
    copy->_edgeCost           = _edgeCost;
    copy->_nodeCost           = _nodeCost;
  }

  FORC(Modules, m, _modules) copy->addModule((*m)->copy());
  return copy;
}

void Individual::incAge()
{
  _age++;
}

void Individual::resetAge()
{
  _age = 0;
}

int Individual::age()
{
  return _age;
}

double Individual::rawFitness()
{
  return _rawFitness;
}

void Individual::setRawFitness(double f)
{
  _rawFitness = f;
}

double Individual::nodeCost()
{
  return _nodeCost;
}

void Individual::setNodeCost(double c)
{
  _nodeCost = c;
}

double Individual::edgeCost()
{
  return _edgeCost;
}

void Individual::setEdgeCost(double c)
{
  _edgeCost = c;
}

int Individual::nrOfOffspring()
{
  return _nrOfOffspring;
}

int  Individual::nrOfSynapses()
{
  return _nrOfSynapses;
}

void Individual::setNrOfSynapses(int nr)
{
  _nrOfSynapses = nr;
}

int Individual::nrOfNeurons()
{
  return _nrOfNeurons;
}

void Individual::setNrOfNeurons(int nr)
{
  _nrOfNeurons = nr;
}

void Individual::setNrOfOffspring(int o)
{
  _nrOfOffspring = o;
}