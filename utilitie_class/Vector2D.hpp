#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <iostream>
#include <cmath>

class Vector2D 
{
private :
    float       x;
    float       y;

public :

	// initialisation operators
    Vector2D();
    Vector2D(float x);
    Vector2D(float x, float y);
	Vector2D(float startX, float startY, float endX, float endY);

	// delete funcion
    ~Vector2D();

	// copy and assignation functions
    Vector2D(const Vector2D &);
    Vector2D    &operator=(const Vector2D &);

	// basic get / set functions
    float       getX() const;
    float       getY() const;

    void        setX(float x);
    void        setY(float y);

	// overwrite all the operators
    Vector2D	operator-(const Vector2D &);
    Vector2D	operator+(const Vector2D &);
	Vector2D	operator/(const Vector2D &);
	Vector2D	operator*(const Vector2D &);

    Vector2D	operator-(const float n);
    Vector2D	operator+(const float n);
	Vector2D	operator/(const float n);
	Vector2D	operator*(const float n);

	void		operator+=(const Vector2D &);
	void		operator*=(const Vector2D &);
	void		operator/=(const Vector2D &);
	void		operator-=(const Vector2D &);
	
	void		operator+=(const float n);
	void		operator*=(const float n);
	void		operator/=(const float n);
	void		operator-=(const float n);

	void		operator++();
	void		operator--();

	bool		operator==(const Vector2D &);
	bool		operator!=(const Vector2D &);
	bool		operator>=(const Vector2D &);
	bool		operator<=(const Vector2D &);
	bool		operator<(const Vector2D &);
	bool		operator>(const Vector2D &);

	// Product functions
    static float Dot(const Vector2D&, const Vector2D&);
    static float Cross(const Vector2D&, const Vector2D&);

    // Returns the length of the vector from the origin.
    static float Magnitude(const Vector2D&);

    // Return the unit vector of the input
    static Vector2D Normal(const Vector2D&);

    // Return a vector perpendicular to the left.
    static Vector2D Perpendicular(const Vector2D&);

    // Return true if two line segments intersect.
    static bool Intersect(const Vector2D&, const Vector2D&, const Vector2D&, const Vector2D&);

    // Return the point where two lines intersect.
    static Vector2D GetIntersect(const Vector2D&, const Vector2D&, const Vector2D&, const Vector2D&);
};

#endif