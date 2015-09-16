#include "DataConfiguration.h"

#include "base/macros.h"

#include <iostream>
#include <glog/logging.h>

using namespace std;

DataConfiguration::DataConfiguration(XsdParseNode *parent)
  : XsdParseNode(parent)
{ }

DataConfiguration::~DataConfiguration()
{
  FORC(Modules, m, _modules) delete (*m);
  _modules.clear();
}


void DataConfiguration::add(ParseElement *element)
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
    Module* module = new Module(this);
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

  Module::createXsd(spec);
}


Modules::iterator DataConfiguration::m_begin()
{
  return _modules.begin();
}

Modules::iterator DataConfiguration::m_end()
{
  return _modules.end();
}

int DataConfiguration::m_size()
{
  return _modules.size();
}

Modules DataConfiguration::modules()
{
  return _modules;
}
