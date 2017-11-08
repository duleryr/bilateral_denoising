#ifndef VERTEX
#define VERTEX

#include <vector>

class Vertex
{
public:
    double Coords[3]; // Coordonnées du sommet
    std::vector<int> Faces; // Liste des indices des faces dont l'objet est un des sommets
};

#endif
