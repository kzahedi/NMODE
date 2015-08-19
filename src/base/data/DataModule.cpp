#include "DataModule.h"

#include "base/macros.h"

#include <iostream>
#include <glog/logging.h>

#define TAG_NAME                   (char*)"name"
#define NO_NAME                    (char*)""
#define OPTION_A                   (char*)"option_a"
#define OPTION_B                   (char*)"option_b"

#define TAG_MODULE_COPY            (char*)"copy"
#define TAG_MODULE_COPY_DEFINITION (char*)"copy_definition"
#define TAG_MODULE_MIRROR          (char*)"mirror"
#define TAG_MODULE_ROTATE          (char*)"rotate"
#define TAG_MODULE_TRANSLATE       (char*)"translate"
#define TAG_MODULE_P3D_DEFINITION  (char*)"p3d_definition"
#define TAG_MODULE_B3D_DEFINITION  (char*)"b3d_definition"
#define TAG_TRUE_FALSE_DEFINITION  (char*)"true_definition"

#define TAG_X                      (char*)"x"
#define TAG_Y                      (char*)"y"
#define TAG_Z                      (char*)"z"

using namespace std;

DataModule::DataModule(DataNode *parent)
  : DataNode(parent)
{
  _mirror = new bool[3];
}

DataModule::~DataModule()
{
  delete _mirror;
}

void DataModule::add(DataParseElement *element)
{

  VLOG(100) << "parsing " << element->name();
  if(element->closing(TAG_MODULE))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_MODULE))
  {
    element->set(TAG_NAME, _name);
    VLOG(100) << "setting name to " << _name;
  }

  VLOG(100) << "checking for " << TAG_MODULE_NODE;
  if(element->opening(TAG_MODULE_NODE))
  {
    VLOG(100) << "found " << TAG_MODULE_NODE;
    DataModuleNode *node = new DataModuleNode(this);
    _nodes.push_back(node);
    current = node;
    node->add(element);
  }

  VLOG(100) << "checking for " << TAG_MODULE_EDGE;
  if(element->opening(TAG_MODULE_EDGE))
  {
    VLOG(100) << "found " << TAG_MODULE_EDGE;
    DataModuleEdge *edge = new DataModuleEdge(this);
    _edges.push_back(edge);
    current = edge;
    edge->add(element);
  }

  VLOG(100) << "checking for " << TAG_MODULE_ROTATE;
  if(element->opening(TAG_MODULE_ROTATE))
  {
    VLOG(100) << "found " << TAG_MODULE_ROTATE;
    P3D r;
    element->set(TAG_X, r.x);
    element->set(TAG_Y, r.y);
    element->set(TAG_Z, r.z);
    _rotation << r;
    VLOG(100) << "  found " << _rotation;
  }

  VLOG(100) << "checking for " << TAG_MODULE_MIRROR;
  if(element->opening(TAG_MODULE_MIRROR))
  {
    VLOG(100) << "found " << TAG_MODULE_MIRROR;
    P3D r;
    element->set(TAG_X, _mirror[0]);
    element->set(TAG_Y, _mirror[1]);
    element->set(TAG_Z, _mirror[2]);
    VLOG(100) << "found " << _mirror[0] << " " << _mirror[1] << " " << _mirror[2];
  }

  VLOG(100) << "checking for " << TAG_MODULE_TRANSLATE;
  if(element->opening(TAG_MODULE_TRANSLATE))
  {
    VLOG(100) << "found " << TAG_MODULE_TRANSLATE;
    element->set(TAG_X, _translation.x);
    element->set(TAG_Y, _translation.y);
    element->set(TAG_Z, _translation.z);
    VLOG(100) << "  found " << _translation;
  }

  VLOG(100) << "checking for " << TAG_MODULE_COPY;
  if(element->opening(TAG_MODULE_COPY))
  {
    VLOG(100) << "found " << TAG_MODULE_COPY;
    element->set(TAG_NAME, _ref);
    VLOG(100) << "  found " << _ref;
  }

}

void DataModule::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_MODULE_DEFINITION);
  root->add(NA(TAG_NAME,        TAG_XSD_STRING,             true));
  spec->add(root);

  XsdChoice *options = new XsdChoice(NO_NAME, 1, 1);
  root->add(options);

  XsdSequence *optionA = new XsdSequence(OPTION_A);
  optionA->add(NE(TAG_MODULE_NODE, TAG_MODULE_NODE_DEFINITION, 1, TAG_XSD_UNBOUNDED));
  optionA->add(NE(TAG_MODULE_EDGE, TAG_MODULE_EDGE_DEFINITION, 0, TAG_XSD_UNBOUNDED));
  options->add(optionA);

  XsdSequence *optionB = new XsdSequence(OPTION_B);
  optionB->add(NE(TAG_MODULE_COPY,      TAG_MODULE_COPY_DEFINITION, 1,1));
  optionB->add(NE(TAG_MODULE_MIRROR,    TAG_MODULE_B3D_DEFINITION,  0,1));
  optionB->add(NE(TAG_MODULE_ROTATE,    TAG_MODULE_P3D_DEFINITION,  0,1));
  optionB->add(NE(TAG_MODULE_TRANSLATE, TAG_MODULE_P3D_DEFINITION,  0,1));
  options->add(optionB);

  XsdSequence *p3d = new XsdSequence(TAG_MODULE_P3D_DEFINITION);
  p3d->add(NA(TAG_X, TAG_XSD_DECIMAL, false));
  p3d->add(NA(TAG_Y, TAG_XSD_DECIMAL, false));
  p3d->add(NA(TAG_Z, TAG_XSD_DECIMAL, false));
  spec->add(p3d);

  XsdSequence *b3d = new XsdSequence(TAG_MODULE_B3D_DEFINITION);
  b3d->add(NA(TAG_X, TAG_TRUE_FALSE_DEFINITION, false));
  b3d->add(NA(TAG_Y, TAG_TRUE_FALSE_DEFINITION, false));
  b3d->add(NA(TAG_Z, TAG_TRUE_FALSE_DEFINITION, false));
  spec->add(b3d);

  DataModuleNode::createXsd(spec);
}

string DataModule::name()
{
  return _name;
}

DataModuleNodes::iterator DataModule::n_begin()
{
  return _nodes.begin();
}

DataModuleNodes::iterator DataModule::n_end()
{
  return _nodes.end();
}

int DataModule::n_size()
{
  return _nodes.size();
}


DataModuleNodes DataModule::nodes()
{
  return _nodes;
}

DataModuleEdges::iterator DataModule::e_begin()
{
  return _edges.begin();
}

DataModuleEdges::iterator DataModule::e_end()
{
  return _edges.end();
}

int DataModule::e_size()
{
  return _edges.size();
}

DataModuleEdges DataModule::edges()
{
  return _edges;
}

string DataModule::ref()
{
  return _ref;
}
