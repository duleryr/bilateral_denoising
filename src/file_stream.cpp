#include "file_stream.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include "Vertex.h"
#include "Face.h"

DataStructure File_stream::parse_file_ngb(std::string filename) {
    std::ifstream fichier(filename.c_str(), std::ios::in);
    if(!fichier) {
        std::cout<<"problème lors de l'ouverture du fichier"<<std::endl;
        exit(1);
    }
    std::string type_fichier;
    fichier >> type_fichier;
    int nb_sommets;
    fichier >> nb_sommets;
    int nb_faces;
    fichier >> nb_faces;

    std::vector<Vertex> tableau_sommets;
    //on remplit le tableau de sommets avec les coordonnées des sommets et des normales au sommets
    for (int i = 0; i < nb_sommets; i++) {
        Vertex S;
        fichier >> S.coords.x;
        fichier >> S.coords.y;
        fichier >> S.coords.z;
        fichier >> S.normal.x;
        fichier >> S.normal.y;
        fichier >> S.normal.z;
        tableau_sommets.push_back(S);           
    }

    //On remplit le tableau de faces avec les indices des sommets la constituant et les indices des faces adjacentes
    std::vector<Face> tableau_faces;
    for (int i = 0; i < nb_faces; i++) {
        Face F;
        fichier >> F.verticesId[0];
        fichier >> F.verticesId[1];
        fichier >> F.verticesId[2];
        fichier >> F.neighbourFaces[0];
        fichier >> F.neighbourFaces[1];
        fichier >> F.neighbourFaces[2];
        tableau_faces.push_back(F);
    }

    return DataStructure(tableau_sommets, tableau_faces);
}

void File_stream::write_file_off(std::string filename, DataStructure data) {
    std::ofstream fichier(filename.c_str(), std::ios::out | std::ios::trunc);
    if(!fichier) {
        std::cout<<"problème lors de l'ouverture du fichier"<<std::endl;
        return;
    }
    fichier << "OFF" << std::endl;
    fichier << data.vertices.size() << " " << data.faces.size() << " 0"<< std::endl;
    for (uint i = 0; i < data.vertices.size(); i++) {
        fichier << data.vertices[i].coords.x << " " << data.vertices[i].coords.y << " " << data.vertices[i].coords.z << std::endl;
    }
    for (uint i = 0; i < data.faces.size(); i++) {
        fichier << "3" << data.faces[i].verticesId[0] << data.faces[i].verticesId[1] << data.faces[i].verticesId[2] << std::endl;
    }
}
