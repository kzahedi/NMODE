#include <nmode/Fitness.h>
#include <nmode/NMODEErrorHandler.h>

# define TAG_MODULE    (char*)"module"
# define TAG_NAME      (char*)"name"

Fitness::Fitness(XsdParseNode *parent)
  : XsdParseNode(parent)
{
}

void Fitness::add(ParseElement *element)
{
  if(element->closing(TAG_FITNESS))
  {
    current = parent;
  }

  if(element->opening(TAG_FITNESS))
  {
    element->set(TAG_MODULE, _module);
    element->set(TAG_NAME,   _name);
  }

  if(element->opening(TAG_FITNESS_PARAMETER))
  {
    FitnessParameter *parameter = new FitnessParameter(this);
    parameter->add(element);
    current = parameter;
    push_back(parameter);
  }
}

void Fitness::createXsd(XsdSpecification *spec)
{
  XsdSequence *controller = new XsdSequence(TAG_FITNESS_DEFINITION);
  controller->add(NA(TAG_MODULE, TAG_XSD_STRING, true));
  controller->add(NA(TAG_NAME,   TAG_XSD_STRING, true));
  controller->add(NE(TAG_FITNESS_PARAMETER, TAG_FITNESS_PARAMETER_DEFINITION, 0));
  spec->add(controller);

  XsdSequence *parameterDefinition = new XsdSequence(TAG_FITNESS_PARAMETER_DEFINITION);
  parameterDefinition->add(NA(TAG_NAME,  TAG_XSD_STRING, true));
  parameterDefinition->add(NA(TAG_VALUE, TAG_XSD_STRING, true));
  spec->add(parameterDefinition);

}

string Fitness::module()
{
  return _module;
}

void Fitness::setModule(string module)
{
  _module = module;
}

string Fitness::name()
{
  return _name;
}
