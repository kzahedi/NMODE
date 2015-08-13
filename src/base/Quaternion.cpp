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



#include "Quaternion.h"

Quaternion::Quaternion(double _w, double _x, double _y, double _z)
{
  w = _w;
  x = _x;
  y = _y;
  z = _z;
}

#ifndef _MSC_VER
Quaternion::Quaternion(Quaternion &q)
{
  *this = q;
}
#endif // _MSC_VER

Quaternion::Quaternion(const Quaternion &q)
{
  *this = q;
}

Quaternion::Quaternion(P3D p)
{
  *this << p;
}

Quaternion& Quaternion::operator=(const Quaternion &q)
{
  w = q.w;
  x = q.x;
  y = q.y;
  z = q.z;
  return *this;
}

Quaternion Quaternion::operator*(const Quaternion &q)
{
  Quaternion n(w, x, y, z);
  n *= q;
  return n;
}

Quaternion& Quaternion::operator*=(const Quaternion &q)
{
  // CHECKED 11.07.07

  double nw = w * q.w - x * q.x - y * q.y - z * q.z;
  double nx = w * q.x + x * q.w + y * q.z - z * q.y;
  double ny = w * q.y - x * q.z + y * q.w + z * q.x;
  double nz = w * q.z + x * q.y - y * q.x + z * q.w;

  w = nw;
  x = nx;
  y = ny;
  z = nz;

  return *this;
}

// euler to quaternion
Quaternion& Quaternion::operator<<(const P3D &p)
{
  // double c1   = cos(p.y*0.5);
  // double s1   = sin(p.y*0.5);
  // double c2   = cos(p.z*0.5);
  // double s2   = sin(p.z*0.5);
  // double c3   = cos(p.x*0.5);
  // double s3   = sin(p.x*0.5);
  // double c1c2 = c1*c2;
  // double s1s2 = s1*s2;
  // w = c1c2*c3  - s1s2*s3;
  // x = c1c2*s3  + s1s2*c3;
  // y = s1*c2*c3 + c1*s2*s3;
  // z = c1*s2*c3 - s1*c2*s3;

  double sx = sin(p.x/2); 
  double sy = sin(p.y/2);
  double sz = sin(p.z/2);
  double cx = cos(p.x/2);
  double cy = cos(p.y/2);
  double cz = cos(p.z/2);
  w = cx*cy*cz + sx*sy*sz;
  x = sx*cy*cz - cx*sy*sz;
  y = cx*sy*cz + sx*cy*sz;
  z = cx*cy*sz - sx*sy*cz;
  return *this;
}


Quaternion Quaternion::operator-() const
{
  Quaternion q(-w, -x, -y, -z);
  return q;
}

void Quaternion::conjugate()
{
  x *= -1;
  y *= -1;
  z *= -1;
}

void Quaternion::invert()
{
  double d = w*w + x*x + y*y + z*z;
  w =  w/d;
  x = -x/d;
  y = -y/d;
  z = -z/d;
}
