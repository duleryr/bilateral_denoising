#ifndef TOOLS
#define TOOLS

#include "Point.h"
#include <math.h>

class Tools
{
public:
    static Point cross(const Point V1, const Point V2) {
        Point res = Point();
        res.x = V1.y*V2.z - V1.z*V2.y;
        res.y = V1.z*V2.x - V2.z*V1.x;
        res.z = V1.x*V2.y - V1.y*V2.x;
        return res;
    }

    static Vect normalize(const Vect V) {
        return V / calcNorm(V);
    }

    static double calcNorm(Point V) {
        return sqrt(V.x*V.x + V.y*V.y + V.z*V.z);
    }

    static double dot(Point V1, Point V2) {
        return V1.x*V2.x + V1.y*V2.y + V1.z*V2.z;
    }
};

#endif
