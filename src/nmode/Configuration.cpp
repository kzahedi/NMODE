#include <nmode/Configuration.h>

#include <nmode/macros.h>

#include <iostream>
#include <glog/logging.h>

using namespace std;

Configuration::Configuration(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _individual = new Individual(NULL);
}

Configuration::~Configuration()
{
  // delete _individual;
}

void Configuration::add(ParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->closing(TAG_CONFIGURATION))
  {
    _individual->linkConnectorNodes();
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
    _individual->addModule(module);
    current = module;
    current->add(element);
  }
}

void Configuration::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_CONFIGURATION_DEFINITION);
  root->add(NE(TAG_MODULE,  TAG_MODULE_DEFINITION,  0, TAG_XSD_UNBOUNDED));
  spec->add(root);

  Module::createXsd(spec);
}

Modules::iterator Configuration::m_begin()
{
  return _individual->m_begin();
}

Modules::iterator Configuration::m_end()
{
  return _individual->m_end();
}

int Configuration::m_size()
{
  return _individual->m_size();
}

Modules Configuration::modules()
{
  return _individual->modules();
}

Module* Configuration::module(int index)
{
  return _individual->module(index);
}

Individual* Configuration::individual()
{
  return _individual;
}
