#include "CfgEvaluation.h"

#include <nmode/macros.h>

#include <iostream>
#include <glog/logging.h>

using namespace std;

# define TAG_MODULE                 (char*)"module"

# define TAG_LIFE_TIME              (char*)"lifetime"
# define TAG_LIFE_TIME_DEFINITION   (char*)"lifetime_evaluation_definition"
# define TAG_ITERATIONS             (char*)"iterations"

# define TAG_COST                   (char*)"cost"
# define TAG_COST_DEFINITION        (char*)"cost_evaluation_definition"

# define TAG_GENERATIONS            (char*)"generations"
# define TAG_GENERATIONS_DEFINITION (char*)"generations_evaluation_definition"

# define TAG_EDGE                   (char*)"edge"
# define TAG_NODE                   (char*)"node"

CfgEvaluation::CfgEvaluation(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _lifeTime    = -1;
  _nodeCost    = 0.0;
  _edgeCost    = 0.0;
  _generations = -1;
  _module      = "unknown";
}

CfgEvaluation::~CfgEvaluation()
{
  FORC(EvaluationParameters, p, _parameters) delete (*p);
  _parameters.clear();
}


void CfgEvaluation::add(ParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();

  if(element->closing(TAG_EVALUATION))
  {
    FORC(EvaluationParameters, p, _parameters)
    {
      EvaluationParameterMap::add((*p)->name(), (*p)->value());
    }
    current = parent;
    return;
  }

  if(element->opening(TAG_EVALUATION))
  {
    element->set(TAG_MODULE, _module);
  }

  if(element->opening(TAG_LIFE_TIME))
  {
    element->set(TAG_ITERATIONS, _lifeTime);
    FORC(EvaluationParameters, p, _parameters)
    {
      delete *p;
    }
    _parameters.clear();
    EvaluationParameterMap::clear();
  }

  if(element->opening(TAG_GENERATIONS))
  {
    element->set(TAG_ITERATIONS, _generations);
  }

  if(element->opening(TAG_COST))
  {
    element->set(TAG_NODE, _nodeCost);
    element->set(TAG_EDGE, _edgeCost);
  }

  if(element->opening(TAG_EVALUATION_PARAMETER))
  {
    EvaluationParameter *parameter = new EvaluationParameter(this);
    parameter->add(element);
    current = parameter;
    _parameters.push_back(parameter);
  }
}

void CfgEvaluation::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_EVALUATION_DEFINITION);
  root->add(NA(TAG_MODULE,               TAG_XSD_STRING,                      true));
  root->add(NE(TAG_LIFE_TIME,            TAG_LIFE_TIME_DEFINITION,            1, 1));
  root->add(NE(TAG_GENERATIONS,          TAG_GENERATIONS_DEFINITION,          0, 1));
  root->add(NE(TAG_COST,                 TAG_COST_DEFINITION,                 1, 1));
  root->add(NE(TAG_EVALUATION_PARAMETER, TAG_EVALUATION_PARAMETER_DEFINITION, 0));
  spec->add(root);

  XsdSequence *lifeTime = new XsdSequence(TAG_LIFE_TIME_DEFINITION);
  lifeTime->add(NA(TAG_ITERATIONS, TAG_POSITIVE_INTEGER, true));
  spec->add(lifeTime);

  XsdSequence *generations = new XsdSequence(TAG_GENERATIONS_DEFINITION);
  generations->add(NA(TAG_ITERATIONS, TAG_POSITIVE_INTEGER, true));
  spec->add(generations);

  XsdSequence *cost = new XsdSequence(TAG_COST_DEFINITION);
  cost->add(NA(TAG_NODE, TAG_POSITIVE_DECIMAL, false));
  cost->add(NA(TAG_EDGE, TAG_POSITIVE_DECIMAL, false));
  spec->add(cost);
}

int CfgEvaluation::lifeTime()
{
  return _lifeTime;
}

int CfgEvaluation::generations()
{
  return _generations;
}

double CfgEvaluation::nodeCost()
{
  return _nodeCost;
}

double CfgEvaluation::edgeCost()
{
  return _edgeCost;
}

string CfgEvaluation::module()
{
  return _module;
}

