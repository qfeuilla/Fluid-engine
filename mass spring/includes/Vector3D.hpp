//
//  **************************************************************************
//
//  vector3d.h 
//  (C) 2003 Bosco K. Ho 
//  
//  This is my 3d vector library. I have tried to make it as straightforward
//  as possible, and provided many helpful functions. The transformation
//  matrices now work as expected, and hopefully you can do all 
//  transformations without worrying about the underlying implementation.
//  Chain together transforms together, displacements, rotations etc.
//  I've provided more helper transform routines than other libraries 
//  (match_2_points, match_3_points) but most of all, I've implemented
//  an optimal transformation object (Superpose in superpose.cpp, 
//  superpose.h) that also gives the RMSD. Some code adapted from 
//  Reduce (C) 1999 J. Michael Word
//
//  Two words of warning (1) I assume that all values are double, and 
//  (2) I have used DEGREES, which is a mistake I think, but will require
//  a bit of re-write to fix.
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

#ifndef _vector3d_h_
#define _vector3d_h_

#include <iostream>
#include <cmath>


/////////////////////////////////////////////
//////                               ////////
//////   ALL ANGLES ARE IN DEGREES   //////// 
//////                               ////////
/////////////////////////////////////////////


const double PI = 3.14159265358979323846;

// Conversion factors  
const double DEG2RAD = PI / 180.0; 
const double RAD2DEG = 180.0 / PI; 

class Matrix3d;



// General 3-d vector

class Vector3d 
{ 
  public:
    // constructors
    Vector3d(): mX(0.0), mY(0.0), mZ(0.0) {} 
    Vector3d(double x, double y, double z): mX(x),mY(y),mZ(z) {}
    Vector3d(const Vector3d& p): mX(p.mX), mY(p.mY), mZ(p.mZ) {}
  
    ~Vector3d() {}
  
    Vector3d operator - (const Vector3d& p) const;
    Vector3d operator + (const Vector3d& p) const;
    Vector3d operator * (double s) const;
    Vector3d operator / (double s) const;
  
    Vector3d operator - () const;
  
    Vector3d& operator =  (const Vector3d& p);
    Vector3d& operator -= (const Vector3d&); 
    Vector3d& operator += (const Vector3d&);
    Vector3d& operator *= (double);
    Vector3d& operator /= (double);
  
    double x() const { return mX; }
    double y() const { return mY; }
    double z() const { return mZ; }

    void x(double x0) { mX = x0; } 
    void y(double y0) { mY = y0; }
    void z(double z0) { mZ = z0; }
  
    double lengthSquared() const;
    double length() const;
    Vector3d& normalize();     // set length to unity
    Vector3d normal() const;
    Vector3d& scaleTo(double); // set length to a new value
    Vector3d scaled(double) const;

    Vector3d& transform(const Matrix3d& matrix);

    Vector3d parallel(const Vector3d&) const;
    double parallelComponent(const Vector3d&) const;
    Vector3d perpendicular(const Vector3d&) const;
    Vector3d outPlane(const Vector3d&, const Vector3d&, const Vector3d&) const;
    Vector3d inPlane(const Vector3d&, const Vector3d&, const Vector3d&) const;
    double planeAngle(const Vector3d&, const Vector3d&, const Vector3d&) const; 

    friend std::ostream& operator << (std::ostream&, const Vector3d&);

  private:
    double mX, mY, mZ;
};


void normalize_angle(double& out);


// vector multiplaction
double dot(const Vector3d& a, const Vector3d& b);
Vector3d cross(const Vector3d&, const Vector3d&);


// linear interpolation from lo (when a=0) to hi (when a=1)
double interpolate(double lo, double hi, double a);
Vector3d interpolate(const Vector3d&, const Vector3d&, double);


// distance between two points
double pos_distance(const Vector3d&, const Vector3d&);
double pos_dist_squared(const Vector3d&, const Vector3d&);


// angles and dihedrals 
double pos_angle(const Vector3d&, const Vector3d&, const Vector3d&);
double vec_angle(const Vector3d&, const Vector3d&);
double pos_dihedral(const Vector3d&, 
                    const Vector3d&,
                    const Vector3d&, 
                    const Vector3d&);
double vec_dihedral(const Vector3d&, const Vector3d&, const Vector3d&);


// projection
Vector3d plane_normal(const Vector3d& p1, 
                      const Vector3d& p2, 
                      const Vector3d& p3);



// Homongenous Coordiantes Tranform Matrix

class Matrix3d 
{ 
  public:
    Matrix3d() { makeIdentity(); }                  // identity matrix
    ~Matrix3d() {}
  
    // matrix multiplication
    Matrix3d operator * (const Matrix3d&) const;      

    // to transform, post-multiply vectors (mat*vec)
    Vector3d operator * (const Vector3d&) const;

    void setElem(int i, int j, double val) { mElement[i][j] = val; };

    friend std::ostream& operator << (std::ostream&, const Matrix3d&);

    Matrix3d&  makeIdentity();

    // basic transform matrices
    friend Matrix3d rotate(const Vector3d& axis, double theta, const Vector3d& center);
    friend Matrix3d rotate_at_origin(const Vector3d& axis, double theta);
    friend Matrix3d translate(const Vector3d& p);    
    friend Matrix3d scale(double factor);
  
  private:
    double mElement[4][4];      
};



// simple superposition
Matrix3d match_3_points(Vector3d ref1, Vector3d ref2, Vector3d ref3, 
                        Vector3d mov1, Vector3d mov2, Vector3d mov3);
Matrix3d match_2_points(Vector3d ref1, Vector3d ref2, 
                        Vector3d mov1, Vector3d mov2);

                        

#endif 

