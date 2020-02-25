//
//  **************************************************************************
//
//  vector3d.cpp 
//
//  (C) 2003 Bosco K. Ho 
//
//  This is a 3 dimensional vector library intended to be used for analysing
//  protein molecules. As there are special operations in 3D that do not
//  generalise to n dimensional vectors, I decided to construct a special
//  class called Vector3d instead of using an off-the-shelf n-dimensional
//  library. A large number of functions are included, many of
//  which are trivial, which should aid the writing of clear code.
//
//  Angle functions return in DEGREES. This was chosen instead of radians as 
//  I found that I always converted the answer to degrees in the
//  output, so this saves one step in thinking. Anyway, conversion
//  constants are provided
//
//  Some code taken from Reduce (C) 1999 J. Michael Word
//  I eliminated the difference between position vectors and vectors,
//  which is a somewhat artificial distinction as a position vector is always
//  better to be thought of in terms of a displacement vector relative to 
//  an origin. Fixed the translation matrix bug, fixed the matrix 
//  multiplication (grrrr).
//
//  **************************************************************************
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 2.1 of the License, or (at
//  your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,  but
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details. 
//  
//  You should have received a copy of the GNU Lesser General Public License 
//  along with this program; if not, write to the Free Software Foundation, 
//  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//  **************************************************************************
//

#include <cmath>
#include <iostream>
#include <iomanip>
#include "Vector3D.hpp"

using namespace std;

#define SMALL 1E-6


void normalize_angle(double& out)
{
  while (out < -180) out += 360;
  while (out >  180) out -= 360;
}



Vector3d Vector3d::operator-(const Vector3d& p) const 
{
  return Vector3d(mX - p.mX, mY - p.mY, mZ - p.mZ);
}



Vector3d Vector3d::operator+(const Vector3d& p) const 
{
  return Vector3d(mX + p.mX, mY + p.mY, mZ + p.mZ);
}



Vector3d Vector3d::operator*(double s) const 
{
  return Vector3d(mX*s, mY*s, mZ*s);
}



Vector3d Vector3d::operator/(double s) const 
{
  return (s != 0.0) ? Vector3d(mX/s, mY/s, mZ/s) : Vector3d(*this);
}



Vector3d Vector3d::operator-() const 
{
  return Vector3d(-mX, -mY, -mZ);
}



Vector3d& Vector3d::operator=(const Vector3d& p) 
{ 
  mX = p.mX; 
  mY = p.mY; 
  mZ = p.mZ;
  return *this;
}



double Vector3d::lengthSquared() const 
{ 
  return (mX*mX) + (mY*mY) + (mZ*mZ);
}



double Vector3d::length() const 
{
  return sqrt(lengthSquared());
}



// scale a vector to unit length
Vector3d& Vector3d::normalize() 
{
   return Vector3d::operator/=(length());
}



// generate a vector from a prev one scaled to unit length
Vector3d Vector3d::normal() const 
{
   return Vector3d::operator/(length());
}



// scale a vector to a given length
Vector3d& Vector3d::scaleTo(double newlen) 
{
  return normalize() *= newlen;
}



// generate a vector from a prev one scaled to a given length
Vector3d Vector3d::scaled(double newlen) const 
{
  return normal() * newlen;
}



Vector3d& Vector3d::operator-=(const Vector3d& p) 
{
  mX -= p.mX;
  mY -= p.mY;
  mZ -= p.mZ;
  return *this;
}



Vector3d& Vector3d::operator+=(const Vector3d& p) 
{
  mX += p.mX;
  mY += p.mY;
  mZ += p.mZ;
  return *this;
}



Vector3d& Vector3d::operator*=(double s) 
{
  mX *= s;
  mY *= s;
  mZ *= s;
  return *this;
}



Vector3d& Vector3d::operator/=(double s) 
{
  if (s != 0.0) 
  {
     mX /= s;
     mY /= s;
     mZ /= s;
  }
  return *this;
}



// --------- distances and vectors

inline double dot(const Vector3d& a, const Vector3d& b) 
{
  return (a.x()*b.x()) + (a.y()*b.y()) + (a.z()*b.z());
}



inline double interpolate(double lo, double hi, double a) 
{
  return lo + a*(hi-lo);
}



Vector3d cross(const Vector3d& a, const Vector3d& b) 
{
  return Vector3d( (a.y()*b.z()) - (a.z()*b.y()),
                   (a.z()*b.x()) - (a.x()*b.z()),
                   (a.x()*b.y()) - (a.y()*b.x()) );
}



Vector3d interpolate(const Vector3d& lo, const Vector3d& hi, double alpha) 
{
  return Vector3d(interpolate(lo.x(), hi.x(), alpha),
                  interpolate(lo.y(), hi.y(), alpha),
                  interpolate(lo.z(), hi.z(), alpha));
}



double pos_dist_squared(const Vector3d& a, const Vector3d& b) 
{
  Vector3d c = a - b;
  return c.lengthSquared();
}



double pos_distance(const Vector3d& a, const Vector3d& b) 
{
  return sqrt(pos_dist_squared(a, b));
}



// ---------- components of vectors



Vector3d Vector3d::parallel(const Vector3d& axis) const 
{
  return axis * (dot(*this, axis) / axis.lengthSquared());
}


        
double Vector3d::parallelComponent(const Vector3d& axis) const 
{
  return (dot(*this, axis) / axis.length());
}


        
Vector3d Vector3d::perpendicular(const Vector3d& axis) const 
{
  return *this - parallel(axis);
}



Vector3d Vector3d::outPlane(const Vector3d& p1, const Vector3d& p2, 
                            const Vector3d& p3) const 
{
  Vector3d d = cross (p2 - p1, p3 - p2);

  if ( (d.length() == 0) || (length() == 0) ) 
    return Vector3d(0,0,0);

  return parallel(d);
}


 
Vector3d Vector3d::inPlane(const Vector3d& p1, const Vector3d& p2, 
                           const Vector3d& p3) const 
{
  return *this - outPlane(p1, p2, p3);
}



// ---------- angles and dihedrals


double Vector3d::planeAngle (const Vector3d& p1, const Vector3d& p2, 
                             const Vector3d& p3) const 
{
  Vector3d d = outPlane(p1, p2, p3);
  double ang = RAD2DEG * asin( dot(normal(), d.normal()) );
  if (parallelComponent (d) > 0) 
    return ang; 
  else 
    return -ang;
}


Vector3d& Vector3d::transform(const Matrix3d& matrix) 
{
  *this = matrix * (*this);
  return *this;
}


// calculate the angle (degrees) between 2 vectors
double vec_angle(const Vector3d& a, const Vector3d& b)
{
  double amag = a.length();
  double bmag = b.length();

  if (amag * bmag < SMALL) return 0.0;

  double c = dot(a, b) / amag / bmag;

  if (c >=  1.0) return   0.0;
  if (c <= -1.0) return 180.0;

  return (RAD2DEG * acos(c));
}



// calculate the angle (degrees) between 3 points

double pos_angle(const Vector3d& p1, const Vector3d& p2, const Vector3d& p3) 
{
  return vec_angle(p1-p2, p3-p2);
}



// dihedral angle between a and c through axis
double vec_dihedral(const Vector3d& a, const Vector3d& axis, const Vector3d& c) 
{
  Vector3d ap = a.perpendicular(axis);
  Vector3d cp = c.perpendicular(axis);

  double ang = vec_angle(ap, cp);

  if ( dot( cross(ap, cp), axis ) > 0 ) 
    return ( -ang );
  else 
    return ( ang );
}



// calculate the dihedral angle (degrees) given 4 points
double pos_dihedral(const Vector3d& p1, const Vector3d& p2,
                  const Vector3d& p3, const Vector3d& p4) 
{
  return vec_dihedral(p1-p2, p2-p3, p4-p3);      
}


inline Vector3d plane_normal(const Vector3d& p1, 
                             const Vector3d& p2, 
                             const Vector3d& p3) 
{ 
  return cross(p2-p1, p3-p2); 
}


                              
std::ostream& operator<<(std::ostream& os, const Vector3d& p) 
{
   os << setiosflags(ios::fixed) 
      << setprecision(2) << "{" 
      << setw(5) << p.x() << ", " 
      << setw(5) << p.y() << ", " 
      << setw(5) << p.z() << "}";
   return os;
}




// ---- matrix related

Matrix3d& Matrix3d::makeIdentity() 
{ 
  mElement[0][0] = 1.0;
  mElement[0][1] = 0.0;
  mElement[0][2] = 0.0;
  mElement[0][3] = 0.0;

  mElement[1][0] = 0.0;
  mElement[1][1] = 1.0;
  mElement[1][2] = 0.0;
  mElement[1][3] = 0.0;

  mElement[2][0] = 0.0;
  mElement[2][1] = 0.0;
  mElement[2][2] = 1.0;
  mElement[2][3] = 0.0;

  mElement[3][0] = 0.0;
  mElement[3][1] = 0.0;
  mElement[3][2] = 0.0;
  mElement[3][3] = 1.0;

  return *this;
}



Vector3d Matrix3d::operator * (const Vector3d& v) const 
{
  double x, y, z;
  // v'[i] = sum(over j) M[j][i] v[j]
  x = (mElement[0][0] * v.x()) +
      (mElement[1][0] * v.y()) +
      (mElement[2][0] * v.z()) +
       mElement[3][0]; 
  y = (mElement[0][1] * v.x()) +
      (mElement[1][1] * v.y()) +
      (mElement[2][1] * v.z()) +
       mElement[3][1]; 
  z = (mElement[0][2] * v.x()) +
      (mElement[1][2] * v.y()) +
      (mElement[2][2] * v.z()) +
       mElement[3][2]; 
                   
  return Vector3d(x, y, z);
}



Matrix3d Matrix3d::operator * (const Matrix3d& m) const 
{
  Matrix3d c;
  int i, j, k;

  // TODO: change indexing so that ij follows book convention
  //   v''[i] = sum(over k) m2[k][i] v'[k]
  //          = sum(over k) m2[k][i] sum(over j) m1[j][k] v[j]
  //          = sum(over j) { sum(over k) m2[k][i] m1[j][k] } v[k]
  //          = sum(over j) m3[j][i] v[j]
  //
  //  therefore, for m3 = m2 * m1
  //    m3[j][i] = sum(over k) m2[k][i] m1[j][k]
            
  for (i = 0; i < 3; i++) 
  {
    for (j = 0; j < 3; j++) 
    {
      c.mElement[j][i] = 0.0;
      for (k = 0; k < 3; k++) 
         c.mElement[j][i] += mElement[k][i] * m.mElement[j][k];
    }
    
    // c[3][i] is the translation vector 
    c.mElement[3][i] = mElement[3][i];
    for (k = 0; k < 3; k++) 
      c.mElement[3][i] += mElement[k][i] * m.mElement[3][k];
  }

  return c;
}



std::ostream& operator << (std::ostream& os, const Matrix3d& m) 
{
   os << setiosflags(ios::fixed) 
      << setprecision(2)
      << "{{" << setw(5) << m.mElement[0][0] << ", " 
              << setw(5) << m.mElement[0][1] << ", "
              << setw(5) << m.mElement[0][2] << ", " 
              << setw(5) << m.mElement[0][3] << "}," << endl
      << " {" << setw(5) << m.mElement[1][0] << ", " 
              << setw(5) << m.mElement[1][1] << ", "
              << setw(5) << m.mElement[1][2] << ", " 
              << setw(5) << m.mElement[1][3] << "}," << endl
      << " {" << setw(5) << m.mElement[2][0] << ", " 
              << setw(5) << m.mElement[2][1] << ", "
              << setw(5) << m.mElement[2][2] << ", " 
              << setw(5) << m.mElement[2][3] << "}," << endl
      << " {" << setw(5) << m.mElement[3][0] << ", " 
              << setw(5) << m.mElement[3][1] << ", "
              << setw(5) << m.mElement[3][2] << ", " 
              << setw(5) << m.mElement[3][3] << "}}" << endl;
   return os;
}


Matrix3d scale(double s) 
{ 
  Matrix3d m;
  m.mElement[0][0] = s;
  m.mElement[1][1] = s;
  m.mElement[2][2] = s;
  return m;
}



Matrix3d translate(const Vector3d& p) 
{ 
  Matrix3d m;
  m.mElement[3][0] = p.x();
  m.mElement[3][1] = p.y();
  m.mElement[3][2] = p.z();
  return m;
}



Matrix3d rotate_at_origin(const Vector3d& axis, double theta)  
{
  Vector3d v = axis.normal();
  const double x = v.x();
  const double y = v.y();
  const double z = v.z();

  const double c = cos(theta*DEG2RAD);
  const double s = sin(theta*DEG2RAD);
  const double t = 1.0 - c;

  Matrix3d m;

  m.mElement[0][0] = t * x * x    +        c;
  m.mElement[0][1] = t * x * y    +    z * s;
  m.mElement[0][2] = t * x * z    -    y * s;

  m.mElement[1][0] = t * y * x    -    z * s;
  m.mElement[1][1] = t * y * y    +        c;
  m.mElement[1][2] = t * y * z    +    x * s;

  m.mElement[2][0] = t * z * x    +    y * s;
  m.mElement[2][1] = t * z * y    -    x * s;
  m.mElement[2][2] = t * z * z    +        c;

  return m;
}