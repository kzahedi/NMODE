#include <nmode/CfgMutationEdge.h>

#include <iostream>
#include <glog/logging.h>


#define TAG_MODIFY            (char*)"modify"
#define TAG_MODIFY_DEFINITION (char*)"edge_modify_definition"

#define TAG_ADD               (char*)"add"
#define TAG_ADD_DEFINITION    (char*)"edge_add_definition"

#define TAG_DEL               (char*)"delete"
#define TAG_DEL_DEFINITION    (char*)"edge_delete_definition"

#define TAG_MODE              (char*)"mode"
#define TAG_MODE_ENUM         (char*)"edge_add_mode_enum"
#define TAG_UNIFORM           (char*)"uniform"
#define TAG_DISTANCE          (char*)"distance"

#define TAG_PROBABILITY       (char*)"probability"
#define TAG_MAX               (char*)"maximum"
#define TAG_DELTA             (char*)"delta"
#define TAG_SELF              (char*)"self"
#define TAG_SELF_DEFINITION   (char*)"self_coupling_definition"

using namespace std;

CfgMutationEdge::CfgMutationEdge(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _modifyProbability = 0.1;
  _modifyMaxValue    = 4.0;
  _modifyDelta       = 0.5;

  _addProbability    = 0.01;
  _addMaxValue       = 1.0;

  _addSelfcoupling   = 0.0;
  _maxSelfcoupling   = 0.0;

  _delProbability    = 0.1;
  _mode              = EDGE_ADD_MODE_DISTANCE;
}

CfgMutationEdge::~CfgMutationEdge()
{
  // nothing to be done
}

void CfgMutationEdge::add(ParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->closing(TAG_MUTATION_EDGE))
  {
    current = parent;
  }

  if(element->opening(TAG_MUTATION_EDGE))
  {
  }

  if(element->opening(TAG_MODIFY))
  {
    element->set(TAG_PROBABILITY, _modifyProbability);
    element->set(TAG_MAX,         _modifyMaxValue);
    element->set(TAG_DELTA,       _modifyDelta);
    VLOG(100) << "set modify probability to: " << _modifyProbability;
    VLOG(100) << "set modify max to:         " << _modifyMaxValue;
    VLOG(100) << "set modify delta to:       " << _modifyDelta;
  }

  if(element->opening(TAG_ADD))
  {
    string mode;
    element->set(TAG_PROBABILITY, _addProbability);
    element->set(TAG_MAX,         _addMaxValue);
    element->set(TAG_MODE,         mode);
    if(mode == TAG_UNIFORM)  _mode = EDGE_ADD_MODE_UNIFORM;
    if(mode == TAG_DISTANCE) _mode = EDGE_ADD_MODE_DISTANCE;
    VLOG(100) << "set add probability to: " << _addProbability;
    VLOG(100) << "set add max to:         " << _addMaxValue;
  }
  if(element->opening(TAG_SELF))
  {
    element->set(TAG_PROBABILITY,  _addSelfcoupling);
    element->set(TAG_MAX,          _maxSelfcoupling);
    VLOG(100) << "set add self coupling:  " << _addSelfcoupling;
    VLOG(100) << "set max self coupling:  " << _maxSelfcoupling;
  }

  if(element->opening(TAG_DEL))
  {
    element->set(TAG_PROBABILITY, _delProbability);
    VLOG(100) << "set del probability to: " << _delProbability;
  }

}

void CfgMutationEdge::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_MUTATION_EDGE_DEFINITION);
  root->add(NE(TAG_MODIFY, TAG_MODIFY_DEFINITION, 1, 1));
  root->add(NE(TAG_ADD,    TAG_ADD_DEFINITION,    1, 1));
  root->add(NE(TAG_SELF,   TAG_SELF_DEFINITION,   1, 1));
  root->add(NE(TAG_DEL,    TAG_DEL_DEFINITION,    1, 1));
  spec->add(root);

  XsdSequence *modify = new XsdSequence(TAG_MODIFY_DEFINITION);
  modify->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL,    true));
  modify->add(NA(TAG_MAX,         TAG_POSITIVE_DECIMAL, true));
  modify->add(NA(TAG_DELTA,       TAG_POSITIVE_DECIMAL, true));
  spec->add(modify);
  
  XsdSequence *add = new XsdSequence(TAG_ADD_DEFINITION);
  add->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL,    true));
  add->add(NA(TAG_MAX,         TAG_POSITIVE_DECIMAL, true));
  add->add(NA(TAG_MODE,        TAG_MODE_ENUM,        true));
  spec->add(add);

  XsdSequence *self = new XsdSequence(TAG_SELF_DEFINITION);
  self->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL,    true));
  self->add(NA(TAG_MAX,         TAG_POSITIVE_DECIMAL, true));
  spec->add(self);

  XsdSequence *del = new XsdSequence(TAG_DEL_DEFINITION);
  del->add(NA(TAG_PROBABILITY, TAG_UNIT_INTERVAL, true));
  spec->add(del);

  XsdEnumeration *tfuncenum = new XsdEnumeration(TAG_MODE_ENUM,
                                                 TAG_XSD_STRING);
  tfuncenum->add(TAG_UNIFORM);
  tfuncenum->add(TAG_DISTANCE);
  spec->add(tfuncenum);

}

double CfgMutationEdge::modifyProbability()
{
  return _modifyProbability;
}

double CfgMutationEdge::modifyMaxValue()
{
  return _modifyMaxValue;
}

double CfgMutationEdge::modifyDelta()
{
  return _modifyDelta;
}

double CfgMutationEdge::addProbability()
{
  return _addProbability;
}

double CfgMutationEdge::selfProbability()
{
  return _addSelfcoupling;
}

double CfgMutationEdge::selfMaxValue()
{
  return _maxSelfcoupling;
}

double CfgMutationEdge::addMaxValue()
{
  return _addMaxValue;
}

double CfgMutationEdge::delProbability()
{
  return _delProbability;
}

CfgMutationEdge* CfgMutationEdge::copy()
{
  CfgMutationEdge *copy = new CfgMutationEdge(NULL);

  copy->_modifyProbability = _modifyProbability;
  copy->_modifyMaxValue    = _modifyMaxValue;
  copy->_modifyDelta       = _modifyDelta;
  copy->_addProbability    = _addProbability;
  copy->_addMaxValue       = _addMaxValue;
  copy->_delProbability    = _delProbability;

  return copy;
}

int CfgMutationEdge::mode()
{
  return _mode;
}
