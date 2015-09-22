#include "Individual.h"

#include "glog/logging.h"

#include "base/macros.h"

#define TAG_ID        (char*)"id"
#define TAG_FITNESS   (char*)"fitness"
#define TAG_OFFSPRING (char*)"offspring"
#define TAG_CONNECTOR (char*)"connector"

Individual::Individual(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _id        = 1;
  _fitness   = 0.0;
  _offspring = 0;
}

void Individual::add(ParseElement *element)
{
  VLOG(100) << "parsing " << element->name();

  if(element->closing(TAG_INDIVIDUAL))
  {
    // __linkConnectorNodes();
    VLOG(100) << "closing " << element->name();
    current = parent;
  }

  if(element->opening(TAG_INDIVIDUAL))
  {
    element->set(TAG_ID,        _id);
    element->set(TAG_FITNESS,   _fitness);
    element->set(TAG_OFFSPRING, _offspring);
    VLOG(100) << "setting id = " << _id << " fitness = " << _fitness << " offspring = " << _offspring;
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

int Individual::offspring()
{
  return _offspring;
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
  Individual *copy = new Individual(NULL);

  Modules mods;

  FORC(Modules, m, _modules)
  {
    if((*m)->isCopy() == false)
    {
      mods.push_back(*m);
    }
  }

  FORC(Modules, m, _modules)
  {
    if((*m)->isCopy())
    {
      FORC(Modules, c, mods)
      {
        if((*m)->ref() == (*c)->name())
        {
          Module new_module = (*c);
          copy->addModule(&new_module);
        }
      }
    }
  }

  return copy;
}
