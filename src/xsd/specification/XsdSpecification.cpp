/*************************************************************************
 *                                                                       *
 * This file is part of Yet Another Robot Simulator (YARS).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/YARS                                  *
 *                                                                       *
 * For a list of contributors see the file AUTHORS.                      *
 *                                                                       *
 * YARS is free software; you can redistribute it and/or modify it under *
 * the terms of the GNU General Public License as published by the Free  *
 * Software Foundation; either version 2 of the License, or (at your     *
 * option) any later version.                                            *
 *                                                                       *
 * YARS is distributed in the hope that it will be useful, but WITHOUT   *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
 * FITNESS FOR A PARTICULAR PURPOSE.                                     *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with YARS in the file COPYING; if not, write to the Free        *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor,               *
 * Boston, MA 02110-1301, USA                                            *
 *                                                                       *
 *************************************************************************/


#include "XsdSpecification.h"
#include "base/macros.h"

#include <sstream>

# define DIVIDER "_"

# define YARS_STRING_POSE_DEFINITION               (char*)"pose"            DIVIDER DEFINITION
# define YARS_STRING_P                             (char*)"p"
# define YARS_STRING_I                             (char*)"i"
# define YARS_STRING_D                             (char*)"d"
# define YARS_STRING_SIZE                          (char*)"size"
# define YARS_STRING_X                             (char*)"x"
# define YARS_STRING_Y                             (char*)"y"
# define YARS_STRING_Z                             (char*)"z"
# define YARS_STRING_GLOBAL                        (char*)"global"
# define YARS_STRING_ALPHA                         (char*)"alpha"
# define YARS_STRING_BETA                          (char*)"beta"
# define YARS_STRING_GAMMA                         (char*)"gamma"
# define YARS_STRING_TYPE                          (char*)"type"
# define YARS_STRING_RAD_DEG_DEFINITION            (char*)"radOrDeg"         DIVIDER DEFINITION
# define YARS_STRING_RAD                           (char*)"rad"
# define YARS_STRING_DEG                           (char*)"deg"
# define YARS_STRING_XYZ_DEFINITION                (char*)"xyz"              DIVIDER DEFINITION
# define YARS_STRING_XYZG_DEFINITION               (char*)"xyzg"             DIVIDER DEFINITION
# define YARS_STRING_XY_DEFINITION                 (char*)"xy"               DIVIDER DEFINITION
# define YARS_STRING_FALSE                         (char*)"false"
# define YARS_STRING_TRUE                          (char*)"true"
# define YARS_STRING_NAME                          (char*)"name"
# define YARS_STRING_MIN                           (char*)"min"
# define YARS_STRING_MAX                           (char*)"max"
# define YARS_STRING_MIN_MAX_DEFINITION            (char*)"min"              DIVIDER "max"       DIVIDER DEFINITION
# define YARS_STRING_POSITIVE_MIN_MAX_DEFINITION   (char*)"positive" DIVIDER "min"              DIVIDER "max"       DIVIDER DEFINITION
# define YARS_STRING_NAME_DEFINITION               (char*)"name"             DIVIDER DEFINITION
# define WIDTH                                     "width"
# define RADIUS                                    "radius"
# define HEIGHT                                    "height"
# define DEPTH                                     "depth"
# define WIDTH_HEIGHT                              WIDTH                     DIVIDER HEIGHT
# define WIDTH_HEIGHT_DEPTH                        WIDTH                     DIVIDER HEIGHT      DIVIDER DEPTH
# define YARS_STRING_DEPTH                         (char*)DEPTH
# define YARS_STRING_HEIGHT                        (char*)HEIGHT
# define YARS_STRING_RADIUS                        (char*)RADIUS
# define YARS_STRING_RADIUS_HEIGHT_DEFINITION      (char*)RADIUS             DIVIDER HEIGHT      DIVIDER DEFINITION
# define YARS_STRING_WIDTH                         (char*)WIDTH
# define YARS_STRING_WIDTH_HEIGHT_DEFINITION       (char*)WIDTH_HEIGHT       DIVIDER DEFINITION
# define YARS_STRING_WIDTH_HEIGHT_DEPTH_DEFINITION (char*)WIDTH_HEIGHT_DEPTH DIVIDER DEFINITION
# define YARS_STRING_XSD_POSITIVE_NON_ZERO_INTEGER (char*)"[1-9][0-9]*"
# define YARS_STRING_XSD_POSITIVE_INTEGER          (char*)"[0-9]*"
# define YARS_STRING_XSD_POSITIVE_NON_ZERO_DECIMAL (char*)"([0-9]*.?[0-9]*[1-9]+[0-9]*|[1-9][0-9]*.?[0-9]*)"
# define YARS_STRING_XSD_POSITIVE_DECIMAL          (char*)"[0-9]*.?[0-9]*"

XsdSpecification::XsdSpecification()
{
  // here, only data types
  XsdSequence *poseDefinition = new XsdSequence(YARS_STRING_POSE_DEFINITION);
  poseDefinition->add(NA(YARS_STRING_X,     YARS_STRING_XSD_DECIMAL,        false));
  poseDefinition->add(NA(YARS_STRING_Y,     YARS_STRING_XSD_DECIMAL,        false));
  poseDefinition->add(NA(YARS_STRING_Z,     YARS_STRING_XSD_DECIMAL,        false));
  poseDefinition->add(NA(YARS_STRING_ALPHA, YARS_STRING_XSD_DECIMAL,        false));
  poseDefinition->add(NA(YARS_STRING_BETA,  YARS_STRING_XSD_DECIMAL,        false));
  poseDefinition->add(NA(YARS_STRING_GAMMA, YARS_STRING_XSD_DECIMAL,        false));
  poseDefinition->add(NA(YARS_STRING_TYPE,  YARS_STRING_RAD_DEG_DEFINITION, false));
  add(poseDefinition);

  XsdSequence *pidDefinition = new XsdSequence(YARS_STRING_PID_DEFINITION);
  pidDefinition->add(NA(YARS_STRING_P,      YARS_STRING_XSD_DECIMAL,        false));
  pidDefinition->add(NA(YARS_STRING_I,      YARS_STRING_XSD_DECIMAL,        false));
  pidDefinition->add(NA(YARS_STRING_D,      YARS_STRING_XSD_DECIMAL,        false));
  pidDefinition->add(NA(YARS_STRING_SIZE,   YARS_STRING_XSD_DECIMAL,        false));
  add(pidDefinition);

  XsdEnumeration *radOrDegDefinition = new XsdEnumeration(YARS_STRING_RAD_DEG_DEFINITION, YARS_STRING_XSD_STRING);
  radOrDegDefinition->add(YARS_STRING_RAD);
  radOrDegDefinition->add(YARS_STRING_DEG);
  add(radOrDegDefinition);

  XsdSequence *xyDefinition = new XsdSequence(YARS_STRING_XY_DEFINITION);
  xyDefinition->add(NA(YARS_STRING_X, YARS_STRING_XSD_DECIMAL, true));
  xyDefinition->add(NA(YARS_STRING_Y, YARS_STRING_XSD_DECIMAL, true));
  add(xyDefinition);

  XsdSequence *minMaxDefinition = new XsdSequence(YARS_STRING_MIN_MAX_DEFINITION);
  minMaxDefinition->add(NA(YARS_STRING_MIN, YARS_STRING_XSD_DECIMAL, true));
  minMaxDefinition->add(NA(YARS_STRING_MAX, YARS_STRING_XSD_DECIMAL, true));
  add(minMaxDefinition);

  XsdSequence *xyzDefinition = new XsdSequence(YARS_STRING_XYZ_DEFINITION);
  xyzDefinition->add(NA(YARS_STRING_X, YARS_STRING_XSD_DECIMAL, true));
  xyzDefinition->add(NA(YARS_STRING_Y, YARS_STRING_XSD_DECIMAL, true));
  xyzDefinition->add(NA(YARS_STRING_Z, YARS_STRING_XSD_DECIMAL, true));
  add(xyzDefinition);

  XsdSequence *xyzgDefinition = new XsdSequence(YARS_STRING_XYZG_DEFINITION);
  xyzgDefinition->add(NA(YARS_STRING_X,      YARS_STRING_XSD_DECIMAL, true));
  xyzgDefinition->add(NA(YARS_STRING_Y,      YARS_STRING_XSD_DECIMAL, true));
  xyzgDefinition->add(NA(YARS_STRING_Z,      YARS_STRING_XSD_DECIMAL, true));
  xyzgDefinition->add(NA(YARS_STRING_GLOBAL, YARS_STRING_TRUE_FALSE_DEFINITION, false));
  add(xyzgDefinition);

  XsdSequence *nameDefintion = new XsdSequence(YARS_STRING_NAME_DEFINITION);
  nameDefintion->add(NA(YARS_STRING_NAME, YARS_STRING_XSD_STRING, true));
  add(nameDefintion);

  XsdEnumeration *trueFalseDefinition = new XsdEnumeration(YARS_STRING_TRUE_FALSE_DEFINITION, YARS_STRING_XSD_STRING);
  trueFalseDefinition->add(YARS_STRING_TRUE);
  trueFalseDefinition->add(YARS_STRING_FALSE);
  add(trueFalseDefinition);

  XsdSequence *whdDefinition = new XsdSequence(YARS_STRING_WIDTH_HEIGHT_DEPTH_DEFINITION);
  whdDefinition->add(NA(YARS_STRING_WIDTH,  YARS_STRING_XSD_DECIMAL, true));
  whdDefinition->add(NA(YARS_STRING_HEIGHT, YARS_STRING_XSD_DECIMAL, true));
  whdDefinition->add(NA(YARS_STRING_DEPTH,  YARS_STRING_XSD_DECIMAL, true));
  add(whdDefinition);

  XsdRegularExpression *nonZeroPositiveInteger = new XsdRegularExpression(YARS_STRING_POSITIVE_NON_ZERO_INTEGER,
                                                            YARS_STRING_XSD_INTEGER,
                                                            YARS_STRING_XSD_POSITIVE_NON_ZERO_INTEGER);
  add(nonZeroPositiveInteger);

  XsdRegularExpression *positiveInteger = new XsdRegularExpression(YARS_STRING_POSITIVE_INTEGER,
                                                            YARS_STRING_XSD_INTEGER,
                                                            YARS_STRING_XSD_POSITIVE_INTEGER);
  add(positiveInteger);

  XsdInterval *unitInverval = new XsdInterval(YARS_STRING_UNIT_INTERVAL, YARS_STRING_XSD_DECIMAL, 0.0, 1.0);
  add(unitInverval);

  XsdRegularExpression *nonZeroPositiveDecimal =
    new XsdRegularExpression(YARS_STRING_POSITIVE_NON_ZERO_DECIMAL,
        YARS_STRING_XSD_DECIMAL,
        YARS_STRING_XSD_POSITIVE_NON_ZERO_DECIMAL);
  add(nonZeroPositiveDecimal);

  XsdRegularExpression *positiveDecimal =
    new XsdRegularExpression(YARS_STRING_POSITIVE_DECIMAL,
        YARS_STRING_XSD_DECIMAL,
        YARS_STRING_XSD_POSITIVE_DECIMAL);
  add(positiveDecimal);

  XsdSequence *nameDefinition = new XsdSequence(YARS_STRING_NAME_DEFINITION);
  nameDefinition->add(NA(YARS_STRING_NAME, YARS_STRING_XSD_STRING, true));
  add(nameDefinition);
}

XsdSpecification::~XsdSpecification()
{
  FORC(vector<XsdSequence*>, s, _sequences)
    if(*s != NULL) delete (*s);
  FORC(vector<XsdEnumeration*>, e, _enumerations)
    if(*e != NULL) delete (*e);
  FORC(vector<XsdChoice*>, c, _choices)
    if(*c != NULL) delete (*c);
  FORC(vector<XsdInterval*>, i, _intervals)
    if(*i != NULL) delete (*i);
  FORC(vector<XsdRegularExpression*>, r, _regExps)
    if(*r != NULL) delete (*r);
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


