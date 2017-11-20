#ifndef FACE
#define FACE

class Face
{
public:
    int verticesId[3]; // indices des 3 sommets de la face, ordre trigo
    int neighbourFaces[3]; // indices des 3 faces voisines, ordre trigo
};

#endif
