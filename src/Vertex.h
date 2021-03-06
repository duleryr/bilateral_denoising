#ifndef VERTEX
#define VERTEX

#include <vector>
#include <unordered_set>
#include "Point.h"

class Vertex
{
public:
    Point coords; // Coordonnées du sommet
    std::vector<int> related_faces; // Liste des indices des faces dont l'objet est un des sommets
    Vect normal; // Coordonnées de la normale
    std::unordered_set<int> neighbours; // Liste des indices des sommets voisins

    bool operator == (const Vertex &V) const;
    double compute_sigma_c(std::string);
};

#endif
