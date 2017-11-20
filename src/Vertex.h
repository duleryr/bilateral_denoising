#ifndef VERTEX
#define VERTEX

#include <vector>
#include "Point.h"

class Vertex
{
public:
    Point coords; // Coordonnées du sommet
    std::vector<int> related_faces; // Liste des indices des faces dont l'objet est un des sommets
    Vect normal; // Coordonnées de la normale
    bool operator == (const Vertex &V) const;
};

#endif
