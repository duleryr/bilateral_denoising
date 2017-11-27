#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE

#include <vector>
#include "Vertex.h"
#include "Face.h"

class DataStructure
{
public:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    DataStructure(std::vector<Vertex> list_vertices, std::vector<Face> list_faces);
    void update_normals();
    void display_vertices();
    void compute_topology_neighbours(int k);
private:
    Vect compute_face_normal(int face_id);
    void update_vertices_normals();
    void update_faces_normals();
};

#endif
