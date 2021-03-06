#include <nmode/CfgEvaluation.h>

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

# define TAG_LOG                    (char*)"log"
# define TAG_LOG_DEFINITION         (char*)"log_definition"
# define TAG_CONSOLE                (char*)"console"
# define TAG_CONSOLE_DEFINITION     (char*)"console_definition"
# define TAG_LOG_ITERATIONS         (char*)"iterations"
# define TAG_LOG_KEEP               (char*)"keep"
# define TAG_FILE_TYPE              (char*)"filetype"
# define TAG_FILE_TYPE_DEFINITION   (char*)"log_filetype_definition"
# define TAG_FILE_TYPE_PDF          (char*)"pdf"
# define TAG_FILE_TYPE_SVG          (char*)"svg"
# define TAG_FILE_TYPE_PS           (char*)"ps"

#define TAG_TRUE_FALSE_DEFINITION  (char*)"true_definition"

CfgEvaluation::CfgEvaluation(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _lifeTime       = -1;
  _nodeCost       = 0.0;
  _edgeCost       = 0.0;
  _generations    = -1;
  _logFileType    = "pdf";
  _module         = "unknown";
  _keepLogs       = false;
  _iterations     = 1;
  _logIterations  = false;
  _changed        = false;
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
    _changed = false;
    element->set(TAG_MODULE, _module);
  }

  if(element->opening(TAG_LIFE_TIME))
  {
    _changed |= element->set(TAG_ITERATIONS, _lifeTime);
    _parameters.clear();
    FORC(EvaluationParameters, p, _parameters) delete *p;
    _parameters.clear();
    EvaluationParameterMap::clear();
  }

  if(element->opening(TAG_GENERATIONS))
  {
    element->set(TAG_ITERATIONS, _generations);
  }

  if(element->opening(TAG_LOG))
  {
    element->set(TAG_FILE_TYPE, _logFileType);
    element->set(TAG_LOG_KEEP,  _keepLogs);
  }

  if(element->opening(TAG_CONSOLE))
  {
    element->set(TAG_LOG_ITERATIONS, _logIterations);
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
  root->add(NA(TAG_ITERATIONS,           TAG_POSITIVE_INTEGER,                false));
  root->add(NE(TAG_LIFE_TIME,            TAG_LIFE_TIME_DEFINITION,            1, 1));
  root->add(NE(TAG_GENERATIONS,          TAG_GENERATIONS_DEFINITION,          0, 1));
  root->add(NE(TAG_LOG,                  TAG_LOG_DEFINITION,                  0, 1));
  root->add(NE(TAG_CONSOLE,              TAG_CONSOLE_DEFINITION,              0, 1));
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

  XsdSequence *log = new XsdSequence(TAG_LOG_DEFINITION);
  log->add(NA(TAG_FILE_TYPE, TAG_FILE_TYPE_DEFINITION,  true));
  log->add(NA(TAG_LOG_KEEP,  TAG_TRUE_FALSE_DEFINITION, false));
  spec->add(log);

  XsdSequence *console = new XsdSequence(TAG_CONSOLE_DEFINITION);
  log->add(NA(TAG_LOG_ITERATIONS, TAG_TRUE_FALSE_DEFINITION, false));
  spec->add(log);

  XsdEnumeration *filetypes = new XsdEnumeration(TAG_FILE_TYPE_DEFINITION, TAG_XSD_STRING);
  filetypes->add(TAG_FILE_TYPE_PDF);
  filetypes->add(TAG_FILE_TYPE_SVG);
  filetypes->add(TAG_FILE_TYPE_PS);
  spec->add(filetypes);

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

void CfgEvaluation::setLifeTime(int lf)
{
  _lifeTime = lf;
}

string CfgEvaluation::logFileType()
{
  return _logFileType;
}

bool CfgEvaluation::keepLogs()
{
  return _keepLogs;
}

int CfgEvaluation::iterations()
{
  return _iterations;
}

bool CfgEvaluation::logIterations()
{
  return _logIterations;
}

bool CfgEvaluation::changed()
{
  return _changed;
}
