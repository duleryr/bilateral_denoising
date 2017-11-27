#ifndef POINT
#define POINT

#include <math.h>
#include <iostream>

class Point;
typedef Point Vect;
class Point
{
    public:
        double x;
        double y;
        double z;
        Point() : x(0), y(0), z(0) {}
        Point(double nx, double ny, double nz) {
            x = nx;
            y = ny;
            z = nz;
        }
        Point(const Point & p) : x(p.x), y(p.y), z(p.z) { }
        void operator+=(Point p) {
            this->x += p.x;
            this->y += p.y;
            this->z += p.z;
        }
        void operator-=(Point p) {
            this->x -= p.x;
            this->y -= p.y;
            this->z -= p.z;
        }
        void operator*=(double d) {
            this->x *= d;
            this->y *= d;
            this->z *= d;
        }
        void operator/=(double d) {
            this->x /= d;
            this->y /= d;
            this->z /= d;
        }
        Point operator*(double d) const {
            Point tmp = Point(*this);
            tmp *= d;
            return tmp;
        }
        Point operator/(double d) const {
            Point tmp = Point(*this);
            tmp /= d;
            return tmp;
        }
        Point operator-(const Point & p) const {
            Point tmp = Point(*this);
            tmp -= p;
            return tmp;
        }
        Point operator+(const Point & p) const {
            Point tmp = Point(*this);
            tmp += p;
            return tmp;
        }
        bool operator == (const Point & V) const {
            return (x == V.x) && (y == V.y) && (z == V.z);
        }
        void print() const {
            std::cout << x << " " << y << " " << z << std::endl;
        }
};

#endif
