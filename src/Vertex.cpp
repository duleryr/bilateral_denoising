#include "Vertex.h"

bool Vertex::operator == (const Vertex &V) const {
    return coords == V.coords;
}
