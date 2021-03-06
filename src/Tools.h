#ifndef TOOLS
#define TOOLS

#include "Point.h"
#include <math.h>

class Tools
{
public:
    //calcule le produit vectoriel de V1 et V2
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

    //calcule le produit scalaire de V1 et V2
    static double dot(Point V1, Point V2) {
        return V1.x*V2.x + V1.y*V2.y + V1.z*V2.z;
    }
    
    //calcule la moyenne de la table vect
    static double average(std::vector<double> vect) {
        double result = 0.0;
        for (uint i = 0; i < vect.size(); i++) {
            result += vect[i];
        }
        result /= vect.size();
        return result;
    }

    //calcule l'écart type de la table vect
    static double standard_deviation(std::vector<double> vect) {
	double moy_carre = 0.0;
        for (uint i = 0; i < vect.size(); i++) {
	    moy_carre += vect[i]*vect[i];
        }
        moy_carre /= vect.size();
	double moy = average(vect);
        double var = moy_carre - moy*moy;
	return sqrt(var);
    }
};

#endif
