#include "DataConfiguration.h"

#include "base/macros.h"

#include <iostream>
#include <glog/logging.h>

using namespace std;

DataConfiguration::DataConfiguration(DataNode *parent)
  : DataNode(parent)
{ }

DataConfiguration::~DataConfiguration()
{
  FORC(DataModules, m, _modules) delete (*m);
  _modules.clear();
}


void DataConfiguration::add(DataParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->closing(TAG_CONFIGURATION))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_CONFIGURATION))
  {
    return;
  }

  if(element->opening(TAG_MODULE))
  {
    DataModule* module = new DataModule(this);
    _modules.push_back(module);
    current = module;
    current->add(element);
  }
}

void DataConfiguration::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_CONFIGURATION_DEFINITION);
  root->add(NE(TAG_MODULE,  TAG_MODULE_DEFINITION,  0, TAG_XSD_UNBOUNDED));
  spec->add(root);

  DataModule::createXsd(spec);
}


DataModules::iterator DataConfiguration::m_begin()
{
  return _modules.begin();
}

DataModules::iterator DataConfiguration::m_end()
{
  return _modules.end();
}

int DataConfiguration::m_size()
{
  return _modules.size();
}

DataModules DataConfiguration::modules()
{
  return _modules;
}
