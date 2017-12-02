#include "Data_structure.h"
#include <vector>
#include <iostream>
#include "Vertex.h"
#include "Face.h"
#include "Tools.h"
#include "Point.h"

DataStructure::DataStructure(std::vector<Vertex> list_vertices, std::vector<Face> list_faces) {
    vertices = list_vertices;
    faces = list_faces;
}

Vect DataStructure::compute_face_normal(int face_id) {
    Face F = faces[face_id];
    Vertex V0 = vertices[F.verticesId[0]];
    Vertex V1 = vertices[F.verticesId[1]];
    Vertex V2 = vertices[F.verticesId[2]];
    Vect dist1 = V1.coords - V0.coords;
    Vect dist2 = V2.coords - V0.coords;
    Vect crossProduct = Tools::cross(dist2, dist1);
    return Tools::normalize(crossProduct);
}

void DataStructure::update_vertices_normals() {
    int nb_sommets = vertices.size();
    int nb_faces = faces.size();
    std::vector<Vect> normales_faces;
    for (int i = 0; i < nb_faces; i++) {
        Vect normal = compute_face_normal(i);
        normales_faces.push_back(normal);
    }
    for (int i = 0; i < nb_sommets; i++) {
        Vertex V = vertices[i];
        V.normal = Point();
        for (int j = 0; j < nb_faces; j++) {
            Face F = faces[j];
            Vertex V0 = vertices[F.verticesId[0]];
            Vertex V1 = vertices[F.verticesId[1]];
            Vertex V2 = vertices[F.verticesId[2]];
            if ((V == V0) || (V == V1) || (V == V2)) {
                V.normal += normales_faces[j];
            } 
        }
        vertices[i].normal = Tools::normalize(V.normal);
    }
}

void DataStructure::update_normals() {
    update_vertices_normals();
}

void DataStructure::compute_topology_neighbours(int k) {
    for (int n = 0; n < k; n++) {
        for (uint i = 0; i < faces.size(); i++) {
            Vertex v0 = vertices[faces[i].verticesId[0]];
            Vertex v1 = vertices[faces[i].verticesId[1]];
            Vertex v2 = vertices[faces[i].verticesId[2]];
            v0.neighbours.insert(v1.neighbours.begin(), v1.neighbours.end());
            v0.neighbours.insert(v2.neighbours.begin(), v2.neighbours.end());

            v1.neighbours.insert(v0.neighbours.begin(), v0.neighbours.end());
            v1.neighbours.insert(v2.neighbours.begin(), v2.neighbours.end());

            v2.neighbours.insert(v0.neighbours.begin(), v0.neighbours.end());
            v2.neighbours.insert(v1.neighbours.begin(), v1.neighbours.end());
        }
    }
}

void DataStructure::display_vertices() {
    int nb_vertices = vertices.size();
    for (int i = 0; i < nb_vertices; i++) {
        std::cout << "Vertices n°" << i << std::endl;
        std::cout << vertices[i].coords.x<<" " <<vertices[i].coords.y<<" "<<vertices[i].coords.z<<std::endl;
        for (auto itr = vertices[i].neighbours.begin(); itr != vertices[i].neighbours.end(); ++itr) {
            std::cout << *itr;
        }
        std::cout << std::endl;
    }
}
