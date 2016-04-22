#include <nmode/EvaluationParameter.h>

#include <stdio.h>
#include <stdlib.h>

# define TAG_VALUE (char*)"value"
# define TAG_NAME  (char*)"name"

EvaluationParameter::EvaluationParameter(XsdParseNode *parent)
  : XsdParseNode(parent)
{ }

EvaluationParameter::~EvaluationParameter()
{ }

void EvaluationParameter::add(ParseElement *element)
{
  if(element->closing(TAG_EVALUATION_PARAMETER))
  {
    current = parent;
  }

  if(element->opening(TAG_EVALUATION_PARAMETER))
  {
    element->set(TAG_NAME,  _name);
    element->set(TAG_VALUE, _value);
  }
}

string EvaluationParameter::name()
{
  return _name;
}

string EvaluationParameter::value()
{
  return _value;
}

int EvaluationParameter::intValue()
{
  return atoi(_value.c_str());
}

bool EvaluationParameter::boolValue()
{
  return _value == "true";
}

double EvaluationParameter::realValue()
{
  return (double)atof(_value.c_str());
}

void EvaluationParameter::createXsd(XsdSpecification *spec)
{
  XsdSequence *ep = new XsdSequence(TAG_EVALUATION_PARAMETER_DEFINITION);
  ep->add(NA(TAG_NAME,  TAG_XSD_STRING, true));
  ep->add(NA(TAG_VALUE, TAG_XSD_STRING, true));
  spec->add(ep);

}

EvaluationParameter *EvaluationParameter::copy()
{
  EvaluationParameter *copy = new EvaluationParameter(NULL);
  copy->_name = _name;
  copy->_value = _value;
  return copy;
}

void EvaluationParameter::resetTo(const EvaluationParameter *other)
{
  _name  = other->_name;
  _value = other->_value;
}
