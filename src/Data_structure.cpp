#include "Data_structure.h"
#include <vector>
#include <iostream>
#include <unordered_set>
#include "Vertex.h"
#include "Face.h"
#include "Tools.h"
#include "Point.h"

DataStructure::DataStructure(std::vector<Vertex> list_vertices, std::vector<Face> list_faces) {
    vertices = list_vertices;
    faces = list_faces;
}

// Calcul de la normale d'une face
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

// Met à jour les normales des sommets (en recalculant les normales des faces)
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

// Mise à jour des normales des sommets 
// (originellement prévu pour mettre à jour les normales des faces et des sommets)
void DataStructure::update_normals() {
    update_vertices_normals();
}

// Calcul le k-voisinage topologique de chaque sommet
void DataStructure::compute_topology_neighbours(int k) {
    std::vector<std::unordered_set<int>> listNeighbours_cpy;
    for (uint i = 0; i < vertices.size(); i++) {
        listNeighbours_cpy.push_back(vertices[i].neighbours);
    }

    for (int n = 0; n < k; n++) {
        for (uint i = 0; i < faces.size(); i++) {
            for (auto itr = listNeighbours_cpy[faces[i].verticesId[0]].begin(); itr != listNeighbours_cpy[faces[i].verticesId[0]].end(); ++itr) {
                vertices[faces[i].verticesId[1]].neighbours.insert(*itr);
                vertices[faces[i].verticesId[2]].neighbours.insert(*itr);
            }
            for (auto itr = listNeighbours_cpy[faces[i].verticesId[1]].begin(); itr != listNeighbours_cpy[faces[i].verticesId[1]].end(); ++itr) {
                vertices[faces[i].verticesId[0]].neighbours.insert(*itr);
                vertices[faces[i].verticesId[2]].neighbours.insert(*itr);
            }
            for (auto itr = listNeighbours_cpy[faces[i].verticesId[2]].begin(); itr != listNeighbours_cpy[faces[i].verticesId[2]].end(); ++itr) {
                vertices[faces[i].verticesId[0]].neighbours.insert(*itr);
                vertices[faces[i].verticesId[1]].neighbours.insert(*itr);
            }
        }
        for (uint i = 0; i < vertices.size(); i++) {
            listNeighbours_cpy[i] = vertices[i].neighbours;
        }
    }
}

// Pour le débug
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
