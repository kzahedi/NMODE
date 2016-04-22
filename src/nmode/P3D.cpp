#include <nmode/P3D.h>

P3D::P3D()
{
  x = 0;
  y = 0;
  z = 0;
}

P3D::P3D(const double* p)
{
  x = p[0];
  y = p[1];
  z = p[2];
}

P3D::P3D(const double _x, const double _y, const double _z)
{
  x = _x;
  y = _y;
  z = _z;
}

P3D::P3D(const P3D &p)
{
  x = p.x;
  y = p.y;
  z = p.z;
}

P3D & P3D::operator=(const P3D &b)
{
  x = b.x;
  y = b.y;
  z = b.z;
  return *this;
}

P3D & P3D::operator=(const double value)
{
  x = value;
  y = value;
  z = value;
  return *this;
}

P3D & P3D::operator=(const int value)
{
  *this = (double)value;
  return *this;
}

P3D & P3D::operator=(const double* values)
{
  x = values[0];
  y = values[1];
  z = values[2];
  return *this;
}


P3D & P3D::operator*=(const double value)
{
  x *= value;
  y *= value;
  z *= value;
  return *this;
}

P3D & P3D::operator/=(const double value)
{
  x /= value;
  y /= value;
  z /= value;
  return *this;
}

P3D & P3D::operator+=(const P3D &a)
{
  x += a.x;
  y += a.y;
  z += a.z;
  return *this;
}

P3D & P3D::operator+=(double value)
{
  x += value;
  y += value;
  z += value;
  return *this;
}

P3D & P3D::operator-=(const P3D &b)
{
  x = x - b.x;
  y = y - b.y;
  z = z - b.z;
  return *this;
}

const P3D P3D::operator+(const P3D &b) const
{
  P3D r = *this;
  r += b;
  return r;
}

const P3D P3D::operator-(const P3D &b) const
{
  P3D r = *this;
  r -= b;
  return r;
}

/* cross product */
const P3D P3D::operator*(const P3D &b) const
{
  P3D r;
  r.x = y * b.z - z * b.y;
  r.y = z * b.x - x * b.z;
  r.z = x * b.y - y * b.x;
  return r;
}

double P3D::dot(const P3D &b) const
{
  return x * b.x + y * b.y + z * b.z;
}

const P3D P3D::operator*(const double value) const
{
  P3D r = *this;
  r *= value;
  return r;
}

const P3D P3D::operator/(const double value) const
{
  P3D r = *this;
  r /= value;
  return r;
}

void P3D::normalise()
{
  double l = sqrt(x * x + y * y + z * z);
  x /= l;
  y /= l;
  z /= l;
}

double P3D::length()
{
  return sqrt(x * x + y * y + z * z);
}

bool P3D::operator==(const P3D a)
{
  //return (x == a.x) && (y == a.y) && (z == a.z);
  return fabs(x - a.x) < 0.000001 && fabs(y - a.y) < 0.000001 && fabs(z - a.z) < 0.000001;
}

bool P3D::operator!=(const P3D a)
{
  //return (x == a.x) && (y == a.y) && (z == a.z);
  return fabs(x - a.x) > 0.000001 || fabs(y - a.y) > 0.000001 || fabs(z - a.z) > 0.000001;
}

void P3D::invert()
{
  x *= -1;
  y *= -1;
  z *= -1;
}

void P3D::rotate(P3D p)
{
  double sx = sin(p.x); double cx = cos(p.x);
  double sy = sin(p.y); double cy = cos(p.y);
  double sz = sin(p.z); double cz = cos(p.z);

  double n_x = x * cy * cz + z * sy - y * cy * sz;
  double n_y = -z * cy * sx + x * (cz * sx * sy + cx * sz) + y * (cx * cz - sx * sy * sz);
  double n_z = z * cx * cy + x * (-cx * cz * sy + sx * sz) + y * (cz * sx + cx * sy * sz);

  x = n_x;
  y = n_y;
  z = n_z;
}

void P3D::rotateInv(P3D p)
{
  double sx = sin(p.x); double cx = cos(p.x);
  double sy = sin(p.y); double cy = cos(p.y);
  double sz = sin(p.z); double cz = cos(p.z);

  double n_x = x * cy * cz + y * (cz * sx * sy - cx * sz) + z * (cx * cz * sy + sx * sz);
  double n_y = x * cy * sz + z * (-cz * sx + cx * sy * sz) + y * (cx * cz + sx * sy * sz);
  double n_z = z * cx * cy + y * cy * sx - x * sy;

  x = n_x;
  y = n_y;
  z = n_z;
}
