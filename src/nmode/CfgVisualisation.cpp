#include <nmode/CfgVisualisation.h>

#include <nmode/macros.h>

#include <iostream>
#include <glog/logging.h>

using namespace std;

# define TAG_VALUE             (char*)"value"
# define TAG_OFFSET            (char*)"offset"
# define TAG_OFFSET_DEFINITION (char*)"vis_offset_definition"

CfgVisualisation::CfgVisualisation(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _offset = 0;
}

CfgVisualisation::~CfgVisualisation()
{ }


void CfgVisualisation::add(ParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();

  if(element->closing(TAG_VISUALISATION))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_VISUALISATION))
  { }

  if(element->opening(TAG_OFFSET))
  {
    element->set(TAG_VALUE, _offset);
  }
}

void CfgVisualisation::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_VISUALISATION_DEFINITION);
  root->add(NE(TAG_OFFSET, TAG_OFFSET_DEFINITION, 0, 1));
  spec->add(root);

  XsdSequence *offset = new XsdSequence(TAG_OFFSET_DEFINITION);
  offset->add(NA(TAG_VALUE, TAG_POSITIVE_INTEGER, true));
  spec->add(offset);
}

int CfgVisualisation::offset()
{
  return _offset;
}

