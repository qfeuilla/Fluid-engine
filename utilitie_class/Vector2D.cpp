
#include "Vector2D.hpp"

Vector2D::Vector2D() : x(0.0), y(0.0) { }

Vector2D::Vector2D(float x) : x(x), y(x) { }

Vector2D::Vector2D(float x, float y) : x(x), y(y) { }


Vector2D::~Vector2D() {}


Vector2D::Vector2D(const Vector2D &vec) : x(vec.getX()), y(vec.getY()) {
    *this = vec;
}

Vector2D    &Vector2D::operator=(const Vector2D &vec) {

    if (this != &vec) {
        x = vec.getX();
        y = vec.getY();
    }
    return(*this);
}


float       Vector2D::getX() const {
    return (x);
}

float       Vector2D::getY() const {
    return (y);
}

void        Vector2D::setX(float x) {
    x = x;
}

void        Vector2D::setY(float y) {
    y = y;
}


Vector2D	Vector2D::operator-(const Vector2D &vec) {
    return (Vector2D(x - vec.getX(), y - vec.getY()));
}

Vector2D	Vector2D::operator+(const Vector2D &vec) {
    return (Vector2D(x + vec.getX(), y + vec.getY()));
}

Vector2D	Vector2D::operator/(const Vector2D &vec) {
    return (Vector2D(x / vec.getX(), y / vec.getY()));
}

Vector2D	Vector2D::operator*(const Vector2D &vec) {
    return (Vector2D(x * vec.getX(), y * vec.getY()));
}

Vector2D	Vector2D::operator-(const float n) {
    return (Vector2D(x - n, y - n));
}

Vector2D	Vector2D::operator+(const float n) {
    return (Vector2D(x + n, y + n));
}

Vector2D	Vector2D::operator/(const float n) {
    return (Vector2D(x / n, y / n));
}

Vector2D	Vector2D::operator*(const float n) {
    return (Vector2D(x * n, y * n));
}

void		Vector2D::operator+=(const Vector2D &vec) {
    x += vec.getX();
    y += vec.getY();
}

void		Vector2D::operator*=(const Vector2D &vec) {
    x *= vec.getX();
    y *= vec.getY();
}

void		Vector2D::operator/=(const Vector2D &vec) {
    x /= vec.getX();
    y /= vec.getY();
}

void		Vector2D::operator-=(const Vector2D &vec) {
    x -= vec.getX();
    y -= vec.getY();
}

void		Vector2D::operator+=(const float n) {
    x += n;
    y += n;
}

void		Vector2D::operator*=(const float n) {
    x *= n;
    y *= n;
}

void		Vector2D::operator/=(const float n) {
    x /= n;
    y /= n;
}

void		Vector2D::operator-=(const float n) {
    x -= n;
    y -= n;
}

void		Vector2D::operator++() {
    *this += 1.0;
}

void		Vector2D::operator--() {
    *this -= 1.0;
}

bool		Vector2D::operator==(const Vector2D &vec) {
    return (x == vec.getX() && y == vec.getY());
}

bool		Vector2D::operator!=(const Vector2D &vec) {
    return (x != vec.getX() || y != vec.getY());
}

bool		Vector2D::operator>=(const Vector2D &vec) {
    return ((powf(x, 2) + powf(y, 2)) >= (powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

bool		Vector2D::operator<=(const Vector2D &vec) {
    return ((powf(x, 2) + powf(y, 2)) <= (powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

bool		Vector2D::operator<(const Vector2D &vec) {
    return ((powf(x, 2) + powf(y, 2)) < (powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

bool		Vector2D::operator>(const Vector2D &vec) {
    return ((powf(x, 2) + powf(y, 2)) > (powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

static float Dot(const Vector2D &a, const Vector2D &b) {
    return ((a.getX() * b.getX()) + (a.getY() * b.getY()));
}

static float Cross(const Vector2D &a, const Vector2D &b) {
    return ((a.getX() * b.getY()) - (a.getY() * b.getX()));
}

// Returns the length of the vector from the origin.
static float Magnitude(const Vector2D &vec) {
    return sqrt((vec.getX() * vec.getX()) + (vec.getY() * vec.getY()));
}

// Return the unit vector of the input
static Vector2D Normal(const Vector2D &vec) {
    float magnitude = Magnitude(vec);
    return Vector2D(vec.getX() / magnitude, vec.getY() / magnitude);
}

// Return a vector perpendicular to the left.
static Vector2D Perpendicular(const Vector2D &vec) {
    return Vector2D(vec.getY(), -vec.getX());
}

// Return true if two line segments intersect.
static bool Intersect(const Vector2D &aa, const Vector2D &ab, const Vector2D &ba, const Vector2D &bb) {
    Vector2D p = aa;
    Vector2D r = ab - aa;
    Vector2D q = ba;
    Vector2D s = bb - ba;

    float t = Cross((q - p), s) / Cross(r, s);
    float u = Cross((q - p), r) / Cross(r, s);

    return (0.0 <= t && t <= 1.0) &&
           (0.0 <= u && u <= 1.0);
}

// Return the point where two lines intersect.
static Vector2D GetIntersect(const Vector2D &a, const Vector2D &b, const Vector2D &c, const Vector2D &d) {

}