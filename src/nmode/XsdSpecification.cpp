#include <nmode/XsdSpecification.h>
#include <nmode/macros.h>

#include <sstream>

# define TAG_POSE_DEFINITION               (char*)"pose_definition"
# define TAG_P                             (char*)"p"
# define TAG_I                             (char*)"i"
# define TAG_D                             (char*)"d"
# define TAG_SIZE                          (char*)"size"
# define TAG_X                             (char*)"x"
# define TAG_Y                             (char*)"y"
# define TAG_Z                             (char*)"z"
# define TAG_GLOBAL                        (char*)"global"
# define TAG_ALPHA                         (char*)"alpha"
# define TAG_BETA                          (char*)"beta"
# define TAG_GAMMA                         (char*)"gamma"
# define TAG_TYPE                          (char*)"type"
# define TAG_RAD_DEG_DEFINITION            (char*)"radOrDeg_definition"
# define TAG_RAD                           (char*)"rad"
# define TAG_DEG                           (char*)"deg"
# define TAG_XYZ_DEFINITION                (char*)"xyz_definition"
# define TAG_XYZG_DEFINITION               (char*)"xyzg_definition"
# define TAG_XY_DEFINITION                 (char*)"xy_definition"
# define TAG_FALSE                         (char*)"false"
# define TAG_TRUE                          (char*)"true"
# define TAG_NAME                          (char*)"name"
# define TAG_MIN                           (char*)"min"
# define TAG_MAX                           (char*)"max"
# define TAG_MIN_MAX_DEFINITION            (char*)"min_max_definition"
# define TAG_POSITIVE_MIN_MAX_DEFINITION   (char*)"positive_min_max_definition"
# define TAG_NAME_DEFINITION               (char*)"name_definition"
# define WIDTH                             (char*)"width"
# define RADIUS                            (char*)"radius"
# define HEIGHT                            (char*)"height"
# define DEPTH                             (char*)"depth"
# define WIDTH_HEIGHT                      (char*)"width_height"
# define WIDTH_HEIGHT_DEPTH                (char*)"width_height_depth"
# define TAG_DEPTH                         (char*)"depth"
# define TAG_HEIGHT                        (char*)"height"
# define TAG_RADIUS                        (char*)"radius"
# define TAG_RADIUS_HEIGHT_DEFINITION      (char*)"radius_height_definition"
# define TAG_WIDTH                         (char*)"width"
# define TAG_WIDTH_HEIGHT_DEFINITION       (char*)"width_height_definition"
# define TAG_WIDTH_HEIGHT_DEPTH_DEFINITION (char*)"width_height_depth_definition"
# define TAG_XSD_POSITIVE_NON_ZERO_INTEGER (char*)"[1-9][0-9]*"
# define TAG_XSD_POSITIVE_INTEGER          (char*)"[0-9]*"
# define TAG_XSD_POSITIVE_NON_ZERO_DECIMAL (char*)"([0-9]*.?[0-9]*[1-9]+[0-9]*|[1-9][0-9]*.?[0-9]*)"
# define TAG_XSD_POSITIVE_DECIMAL          (char*)"[0-9]*.?[0-9]*"

XsdSpecification::XsdSpecification()
{
  // here, only data types
  XsdSequence *poseDefinition = new XsdSequence(TAG_POSE_DEFINITION);
  poseDefinition->add(NA(TAG_X,     TAG_XSD_DECIMAL,        false));
  poseDefinition->add(NA(TAG_Y,     TAG_XSD_DECIMAL,        false));
  poseDefinition->add(NA(TAG_Z,     TAG_XSD_DECIMAL,        false));
  poseDefinition->add(NA(TAG_ALPHA, TAG_XSD_DECIMAL,        false));
  poseDefinition->add(NA(TAG_BETA,  TAG_XSD_DECIMAL,        false));
  poseDefinition->add(NA(TAG_GAMMA, TAG_XSD_DECIMAL,        false));
  poseDefinition->add(NA(TAG_TYPE,  TAG_RAD_DEG_DEFINITION, false));
  add(poseDefinition);

  XsdSequence *pidDefinition = new XsdSequence(TAG_PID_DEFINITION);
  pidDefinition->add(NA(TAG_P,      TAG_XSD_DECIMAL,        false));
  pidDefinition->add(NA(TAG_I,      TAG_XSD_DECIMAL,        false));
  pidDefinition->add(NA(TAG_D,      TAG_XSD_DECIMAL,        false));
  pidDefinition->add(NA(TAG_SIZE,   TAG_XSD_DECIMAL,        false));
  add(pidDefinition);

  XsdEnumeration *radOrDegDefinition = new XsdEnumeration(TAG_RAD_DEG_DEFINITION, TAG_XSD_STRING);
  radOrDegDefinition->add(TAG_RAD);
  radOrDegDefinition->add(TAG_DEG);
  add(radOrDegDefinition);

  XsdSequence *xyDefinition = new XsdSequence(TAG_XY_DEFINITION);
  xyDefinition->add(NA(TAG_X, TAG_XSD_DECIMAL, true));
  xyDefinition->add(NA(TAG_Y, TAG_XSD_DECIMAL, true));
  add(xyDefinition);

  XsdSequence *minMaxDefinition = new XsdSequence(TAG_MIN_MAX_DEFINITION);
  minMaxDefinition->add(NA(TAG_MIN, TAG_XSD_DECIMAL, true));
  minMaxDefinition->add(NA(TAG_MAX, TAG_XSD_DECIMAL, true));
  add(minMaxDefinition);

  XsdSequence *xyzDefinition = new XsdSequence(TAG_XYZ_DEFINITION);
  xyzDefinition->add(NA(TAG_X, TAG_XSD_DECIMAL, true));
  xyzDefinition->add(NA(TAG_Y, TAG_XSD_DECIMAL, true));
  xyzDefinition->add(NA(TAG_Z, TAG_XSD_DECIMAL, true));
  add(xyzDefinition);

  XsdSequence *xyzgDefinition = new XsdSequence(TAG_XYZG_DEFINITION);
  xyzgDefinition->add(NA(TAG_X,      TAG_XSD_DECIMAL, true));
  xyzgDefinition->add(NA(TAG_Y,      TAG_XSD_DECIMAL, true));
  xyzgDefinition->add(NA(TAG_Z,      TAG_XSD_DECIMAL, true));
  xyzgDefinition->add(NA(TAG_GLOBAL, TAG_TRUE_FALSE_DEFINITION, false));
  add(xyzgDefinition);

  XsdSequence *nameDefintion = new XsdSequence(TAG_NAME_DEFINITION);
  nameDefintion->add(NA(TAG_NAME, TAG_XSD_STRING, true));
  add(nameDefintion);

  XsdEnumeration *trueFalseDefinition = new XsdEnumeration(TAG_TRUE_FALSE_DEFINITION, TAG_XSD_STRING);
  trueFalseDefinition->add(TAG_TRUE);
  trueFalseDefinition->add(TAG_FALSE);
  add(trueFalseDefinition);

  XsdSequence *whdDefinition = new XsdSequence(TAG_WIDTH_HEIGHT_DEPTH_DEFINITION);
  whdDefinition->add(NA(TAG_WIDTH,  TAG_XSD_DECIMAL, true));
  whdDefinition->add(NA(TAG_HEIGHT, TAG_XSD_DECIMAL, true));
  whdDefinition->add(NA(TAG_DEPTH,  TAG_XSD_DECIMAL, true));
  add(whdDefinition);

  XsdRegularExpression *nonZeroPositiveInteger = new XsdRegularExpression(TAG_POSITIVE_NON_ZERO_INTEGER,
                                                            TAG_XSD_INTEGER,
                                                            TAG_XSD_POSITIVE_NON_ZERO_INTEGER);
  add(nonZeroPositiveInteger);

  XsdRegularExpression *positiveInteger = new XsdRegularExpression(TAG_POSITIVE_INTEGER,
                                                            TAG_XSD_INTEGER,
                                                            TAG_XSD_POSITIVE_INTEGER);
  add(positiveInteger);

  XsdInterval *unitInverval = new XsdInterval(TAG_UNIT_INTERVAL, TAG_XSD_DECIMAL, 0.0, 1.0);
  add(unitInverval);

  XsdRegularExpression *nonZeroPositiveDecimal =
    new XsdRegularExpression(TAG_POSITIVE_NON_ZERO_DECIMAL,
        TAG_XSD_DECIMAL,
        TAG_XSD_POSITIVE_NON_ZERO_DECIMAL);
  add(nonZeroPositiveDecimal);

  XsdRegularExpression *positiveDecimal =
    new XsdRegularExpression(TAG_POSITIVE_DECIMAL,
        TAG_XSD_DECIMAL,
        TAG_XSD_POSITIVE_DECIMAL);
  add(positiveDecimal);

  XsdSequence *nameDefinition = new XsdSequence(TAG_NAME_DEFINITION);
  nameDefinition->add(NA(TAG_NAME, TAG_XSD_STRING, true));
  add(nameDefinition);
}

XsdSpecification::~XsdSpecification()
{
  // FORC(vector<XsdSequence*>,          s, _sequences)    if(*s != NULL) delete (*s);
  // FORC(vector<XsdEnumeration*>,       e, _enumerations) if(*e != NULL) delete (*e);
  // FORC(vector<XsdChoice*>,            c, _choices)      if(*c != NULL) delete (*c);
  // FORC(vector<XsdInterval*>,          i, _intervals)    if(*i != NULL) delete (*i);
  // FORC(vector<XsdRegularExpression*>, r, _regExps)      if(*r != NULL) delete (*r);
  // FOREACH(XsdNode*,              n, _nodes)        if(*n != NULL) delete (*n);

  _sequences.clear();
  _enumerations.clear();
  _choices.clear();
  _intervals.clear();
  _regExps.clear();
  _nodes.clear();

}


void XsdSpecification::add(XsdSequence* sequence)
{
  for(std::vector<XsdSequence*>::iterator i = _sequences.begin(); i != _sequences.end(); i++)
  {
    if((*i)->name() == sequence->name())
    {
      _sequences.erase(i); // if the same element was found, it must be the last in the vector
      break;
    }
  }
  _sequences.push_back(sequence);
  _nodes.push_back(sequence);
}

void XsdSpecification::add(XsdRegularExpression* regExp)
{
  for(std::vector<XsdRegularExpression*>::iterator i = _regExps.begin(); i != _regExps.end(); i++)
  {
    if((*i)->name() == regExp->name())
    {
      _regExps.erase(i); // if the same element was found, it must be the last in the vector
      break;
    }
  }
  _regExps.push_back(regExp);
  _nodes.push_back(regExp);
}

void XsdSpecification::add(XsdChoice* choice)
{
  for(std::vector<XsdChoice*>::iterator i = _choices.begin(); i != _choices.end(); i++)
  {
    if((*i)->name() == choice->name())
    {
      _choices.erase(i); // if the same element was found, it must be the last in the vector
      break;
    }
  }
  _choices.push_back(choice);
  _nodes.push_back(choice);
}

void XsdSpecification::add(XsdInterval* interval)
{
  for(std::vector<XsdInterval*>::iterator i = _intervals.begin(); i != _intervals.end(); i++)
  {
    if((*i)->name() == interval->name())
    {
      _intervals.erase(i); // if the same element was found, it must be the last in the vector
      break;
    }
  }
  _intervals.push_back(interval);
  _nodes.push_back(interval);
}

void XsdSpecification::add(XsdEnumeration *enumeration)
{
  for(std::vector<XsdEnumeration*>::iterator i = _enumerations.begin(); i != _enumerations.end(); i++)
  {
    if((*i)->name() == enumeration->name())
    {
      _enumerations.erase(i); // if the same element was found, it must be the last in the vector
      break;
    }
  }
  _enumerations.push_back(enumeration);
  _nodes.push_back(enumeration);
}

std::vector<XsdNode*>::iterator XsdSpecification::n_begin()
{
  return _nodes.begin();
}

std::vector<XsdNode*>::iterator XsdSpecification::n_end()
{
  return _nodes.end();
}

std::vector<XsdSequence*>::iterator XsdSpecification::s_begin()
{
  return _sequences.begin();
}

std::vector<XsdSequence*>::iterator XsdSpecification::s_end()
{
  return _sequences.end();
}

int XsdSpecification::s_size()
{
  return _sequences.size();
}

std::vector<XsdEnumeration*>::iterator XsdSpecification::e_begin()
{
  return _enumerations.begin();
}

std::vector<XsdEnumeration*>::iterator XsdSpecification::e_end()
{
  return _enumerations.end();
}

int XsdSpecification::e_size()
{
  return _enumerations.size();
}

std::vector<XsdChoice*>::iterator XsdSpecification::c_begin()
{
  return _choices.begin();
}

std::vector<XsdChoice*>::iterator XsdSpecification::c_end()
{
  return _choices.end();
}

int XsdSpecification::c_size()
{
  return _choices.size();
}


std::vector<XsdInterval*>::iterator XsdSpecification::i_begin()
{
  return _intervals.begin();
}

std::vector<XsdInterval*>::iterator XsdSpecification::i_end()
{
  return _intervals.end();
}

int XsdSpecification::i_size()
{
  return _intervals.size();
}

std::vector<XsdRegularExpression*>::iterator XsdSpecification::r_begin()
{
  return _regExps.begin();
}

std::vector<XsdRegularExpression*>::iterator XsdSpecification::r_end()
{
  return _regExps.end();
}

int XsdSpecification::r_size()
{
  return _regExps.size();
}

XsdSequence* XsdSpecification::root()
{
  return _root;
}

void XsdSpecification::setRoot(XsdSequence *root)
{
  _root = root;
}


