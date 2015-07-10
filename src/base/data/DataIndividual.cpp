#include "DataIndividual.h"

#include "glog/logging.h"

#define TAG_ID        (char*)"id"
#define TAG_FITNESS   (char*)"fitness"
#define TAG_OFFSPRING (char*)"offspring"

DataIndividual::DataIndividual(DataNode *parent)
  : DataNode(parent)
{
  _id        = 1;
  _fitness   = 0.0;
  _offspring = 0;
}

void DataIndividual::add(DataParseElement *element)
{
  VLOG(100) << "parsing " << element->name();
  if(element->closing(TAG_INDIVIDUAL))
  {
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
    DataModule *dpm = new DataModule(this);
    _modules.push_back(dpm);
    current = dpm;
    current->add(element);
  }
}

void DataIndividual::createXsd(XsdSpecification *spec)
{
  XsdSequence *_root = new XsdSequence(TAG_INDIVIDUAL_DEFINITION);
  _root->add(NA(TAG_ID,        TAG_POSITIVE_INTEGER,  false));
  _root->add(NA(TAG_FITNESS,   TAG_XSD_DECIMAL,       false));
  _root->add(NA(TAG_OFFSPRING, TAG_POSITIVE_INTEGER,  false));
  _root->add(NE(TAG_MODULE,    TAG_MODULE_DEFINITION, 1, TAG_XSD_UNBOUNDED));
  spec->add(_root);

  DataModule::createXsd(spec);
}

int DataIndividual::id()
{
  return _id;
}

double DataIndividual::fitness()
{
  return _fitness;
}

int DataIndividual::offspring()
{
  return _offspring;
}

DataModules::iterator DataIndividual::m_begin()
{
  return _modules.begin();
}

DataModules::iterator DataIndividual::m_end()
{
  return _modules.end();
}

int DataIndividual::m_size()
{
  return _modules.size();
}

DataModules DataIndividual::modules()
{
  return _modules;
}

