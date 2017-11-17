#include "Vertex.hpp"

bool Vertex::operator == (const Vertex &V) const {
  for (int i = 0; i < 3; i++) {
    if (Coords[i] != V.Coords[i]) {
      return false;
    }
  }
  return true;
}
